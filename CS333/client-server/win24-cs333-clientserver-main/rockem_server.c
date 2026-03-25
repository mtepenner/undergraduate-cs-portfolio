

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/uio.h>
#include <unistd.h>
#include <pthread.h>

#include "rockem_hdr.h"

#define LISTENQ 100
#define NO_OP(x) (void)(x)

void process_connection(int sockfd, void *buf, int n);
void *thread_get(void *p);
void *thread_put(void *p);
void *thread_dir(void *p);
void *server_commands(void *p);
void current_connections_inc(void);
void current_connections_dec(void);
unsigned int current_connections_get(void);
void server_help(void);

static short is_verbose = 0;
static unsigned sleep_flag = 0;
static unsigned long tcount = 0;
static unsigned int current_connections = 0;
static pthread_mutex_t connections_mutex = PTHREAD_MUTEX_INITIALIZER;

int
main(int argc, char *argv[]) 
{
    int listenfd;
    int sockfd;
    int n;
    char buf[MAXLINE];
    socklen_t clilen;
    struct sockaddr_in cliaddr;
    struct sockaddr_in servaddr;
    short ip_port = DEFAULT_SERV_PORT;
    int opt;
    pthread_t cmd_thread;

    while ((opt = getopt(argc, argv, SERVER_OPTIONS)) != -1) {
        switch (opt) {
        case 'p':
            // CONVERT and assign optarg to ip_port
            sscanf(optarg, "%hd", &ip_port);
            break;
        case 'u':
            // add 1000 to sleep_flag
            sleep_flag += 1000;
            break;
        case 'v':
            is_verbose++;
            break;
        case 'h':
            fprintf(stderr, "%s ...\n\tOptions: %s\n"
                    , argv[0], SERVER_OPTIONS);
            fprintf(stderr, "\t-p #\t\tport on which the server will listen (default %hd)\n"
                    , DEFAULT_SERV_PORT);
            fprintf(stderr, "\t-u\t\tnumber of thousands of microseconds the server will sleep between "
                    "read/write calls (default %d)\n"
                    , sleep_flag);
            fprintf(stderr, "\t-v\t\tenable verbose output. Can occur more than once to increase output\n");
            fprintf(stderr, "\t-h\t\tshow this rather lame help message\n");
            exit(EXIT_SUCCESS);
            break;
        default:
            fprintf(stderr, "*** Oops, something strange happened <%s> ***\n", argv[0]);
            break;
        }
    }

    // Create a socket from the AF_INET family, that is a stream socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // Performing a memset() on servaddr is quite important when doing 
    //   socket communication.
    memset(&servaddr, 0, sizeof(servaddr));
    // An IPv4 address
    servaddr.sin_family = AF_INET;
    // Host-TO-Network-Long. Listen on any interface/IP of the system.
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // Host-TO-Network-Short, the default port from above.
    servaddr.sin_port = htons(ip_port);
    
    // bind the listenfd
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) != 0) {
      perror("Binding error");
      close(listenfd);
      exit(2);
    }
    // listen on the listenfd
    listen(listenfd, LISTENQ);

    {
        char hostname[256];
        struct hostent *host_entry;
        char *IPbuffer;

        // gethostname()
        if (gethostname(hostname, sizeof(hostname)) < 0) {
            perror("gethostname error\n");
            exit(EXIT_FAILURE);
        }
        // gethostbyname()
        host_entry = gethostbyname(hostname);
        if (host_entry == NULL) {
            perror("gethostbyname error\n");
            exit(EXIT_FAILURE);
        }
        // inet_ntoa()
        IPbuffer = inet_ntoa(*(struct in_addr *)host_entry->h_addr_list[0]);
        if (IPbuffer == NULL) {
            perror("inet_ntoa error\n");
            exit(EXIT_FAILURE);
        }
        fprintf(stdout, "Hostname: %s\n", hostname);
        fprintf(stdout, "IP:       %s\n", IPbuffer);
        fprintf(stdout, "Port:     %d\n", ip_port);
    }

    // create the input handler thread
    if(pthread_create(&cmd_thread, NULL, server_commands, NULL) != 0) {
        perror("Failed to create command thread");
        exit(EXIT_FAILURE);
    }
    // client length
    clilen = sizeof(cliaddr);
    // Accept connections on the listenfd.
    for ( ; ; ) {
      fprintf(stderr, "%d \n", __LINE__);
        // loop forever accepting connections
        sockfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
        if (sockfd < 0) {
            perror("Accept error\n");
            continue; // Important to not exit; instead, try to accept another connection
        }
        // You REALLY want to memset to all zeroes before you get bytes from
        // the socket.
        memset(buf, 0, sizeof(buf));

        // read a cmd_t structure from the socket.
        // if zro bytes are read, close the scoket
        if ((n = read(sockfd, buf, sizeof(buf))) == 0) {
            fprintf(stdout, "EOF found on client connection socket, "
                    "closing connection.\n");
            // nothing was read, EOF
            // close the scoket
            close(sockfd);

            break;
        }
        else {
            if (is_verbose) {
                fprintf(stdout, "message from client: <%s>\n", buf);
                //write(sockfd, buf, n);
            }
            // process the command from the client
            // in the process_connection() is where I divy out the put/get/dir
            // threads
            process_connection(sockfd, buf, n);

        }
    }
  
    printf("Closing listen socket\n");
    close(listenfd);

    // this could be pthread_exit, I guess...
    return(EXIT_SUCCESS);
}

void
process_connection(int sockfd, void *buf, int n)
{
    // I have to allocate one of these for each thread that is created.
    // The thread is responsible for calling free on it.
    cmd_t *cmd = (cmd_t *) malloc(sizeof(cmd_t));
    int ret;
    pthread_t tid;
    pthread_attr_t attr;

    memcpy(cmd, buf, sizeof(cmd_t));
    if (n != sizeof(cmd_t)) {
        fprintf(stderr, "received command size (%d) does not match expected (%lu).\n", n, sizeof(cmd_t));
        close(sockfd);
        free(cmd); 
        return;
    }
    cmd->sock = sockfd;
    //cmd->tcount = tcount++;
    if (is_verbose) {
        fprintf(stderr, "Request from client: <%s> <%s>\n"
                , cmd->cmd, cmd->name);
    }

    // lock
    pthread_mutex_lock(&connections_mutex);
    // increment the totaol conections vrariable
    tcount += 1;
    pthread_mutex_unlock(&connections_mutex);
    
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    
    if (strcmp(cmd->cmd, CMD_GET) == 0) {
        // create thread to handle get file
        ret = pthread_create(&tid, &attr, thread_get, (void *)cmd);
        if (ret < 0) {
            fprintf(stderr, "ERROR: %d\n", __LINE__);
        }
    }
    else if (strcmp(cmd->cmd, CMD_PUT) == 0) {
        // create thread to handle put file
        ret = pthread_create(&tid, &attr, thread_put, (void *)cmd);
        if (ret > 0) {
            fprintf(stderr, "ERROR: %d\n", __LINE__);
        }
	fprintf(stderr, "%d \n", __LINE__);
    }
    else if (strcmp(cmd->cmd, CMD_DIR) == 0) {
        // create thread to handle dir
        ret = pthread_create(&tid, &attr, thread_dir, (void *)cmd);
        if (ret > 0) {
            fprintf(stderr, "ERROR: %d\n", __LINE__);
        }
    }
    else {
        // This should never happen since the checks are made on 
        // the client side.
        fprintf(stderr, "ERROR: unknown command >%s< %d\n", cmd->cmd, __LINE__);
        // close the socket
        close(sockfd);
    }

}

void * server_commands(void * p)
{

    char cmd[80];
    char *ret_val;
    size_t len;
    // detach the thread
    pthread_detach(pthread_self());
    NO_OP(p);
    server_help();
    for ( ; ; ) {
        fputs(">> ", stdout);
        ret_val = fgets(cmd, sizeof(cmd), stdin); //This line causes segmentation faults
        len = strlen(cmd);
        if (len > 0 && cmd[len - 1] == '\n') {
         // STOMP on the pesky new line
            cmd[len - 1] = '\0';
        }
        if (ret_val == NULL) {
            // end of input, a control-D was pressed.
            break;
        }
       

        if (strlen(cmd) == 0) {
            continue;
        }
        else if (strcmp(cmd, SERVER_CMD_EXIT) == 0) {
            // I really should do something better than this.
            exit(1);
            break;
        }
        else if (strcmp(cmd, SERVER_CMD_COUNT) == 0) {
            printf("total connections   %lu\n", tcount);
            printf("current connections %u\n", current_connections_get());
            printf("verbose             %d\n", is_verbose);
        }
        else if (strcmp(cmd, SERVER_CMD_VPLUS) == 0) {
            is_verbose++;
            printf("verbose set to %d\n", is_verbose);
        }
        else if (strcmp(cmd, SERVER_CMD_VMINUS) == 0) {
            is_verbose--;
            if (is_verbose < 0) {
                is_verbose = 0;
            }
            printf("verbose set to %d\n", is_verbose);
        }
        else if (strcmp(cmd, SERVER_CMD_HELP) == 0) {
            server_help();
        }
        else {
            printf("command not recognized >>%s<<\n", cmd);
        }
    }

    // This is really harsh. It terminates on all existing threads.
    // This would probably be better with a good exit handler
    exit(EXIT_SUCCESS);
}

void
server_help(void)
{
    printf("available commands are:\n");
    printf("\t%s : show the total connection count "
           "and number current connection\n"
           , SERVER_CMD_COUNT);
    printf("\t%s    : increment the is_verbose flag (current %d)\n"
           , SERVER_CMD_VPLUS, is_verbose);
    printf("\t%s    : decrement the is_verbose flag (current %d)\n"
           , SERVER_CMD_VMINUS, is_verbose);
    printf("\t%s  : exit the server process\n"
           , SERVER_CMD_EXIT);
    printf("\t%s  : show this help\n"
           , SERVER_CMD_HELP);
}

// get from server, so I need to send data to the client.
void *
thread_get(void *p)
{
    cmd_t *cmd = (cmd_t *) p;
    int fd;
    int sockfd;
    ssize_t bytes_read;
    char buffer[MAXLINE];

  
    current_connections_inc();
    //sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sockfd = cmd->sock;
    if (is_verbose) {
        fprintf(stderr, "Sending %s to client\n", cmd->name);
    }
  
    // ope the file in cmd->name, read-only
    fd = open(cmd->name, O_RDONLY);
    if (fd < 0) {
        // barf
        // close things up, free() things up and leave
        free(cmd);
        close(fd);
        close(sockfd);
	 
        pthread_exit((void *) EXIT_FAILURE);
    }
    // in a while loop, read from the file and write to the socket
    // within the while loop, if sleep_flap > 0, usleep()

    while((bytes_read = read(fd, buffer, MAXLINE)) > 0) {
            
            if(sleep_flag > 0) {
              usleep(sleep_flag);
            }
	   
            write(sockfd, buffer, bytes_read);
	    
    }
   
    // close file descriptor
    close(fd);
    // close socket
    close(sockfd);
    // free
    free(cmd);
    current_connections_dec();

    pthread_exit((void *) EXIT_SUCCESS);
}

void *
thread_put(void *p)
{
    cmd_t *cmd = (cmd_t *) p;
    int fd;
    ssize_t bytes_read;
    char buffer[MAXLINE];
    int sockfd;
    current_connections_inc();


    sockfd = cmd->sock;
    if (is_verbose) {
        fprintf(stderr, "VERBOSE: Receiving %s from client\n"
                , cmd->name);
    }
    // open the file in cmd->name as write-only
    fd = open(cmd->name, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    // truncate it is it aready exists
    if (fd < 0) {
        // barf
        // close things up, free() things up and leave
        free(cmd);
        close(fd);
        close(sockfd);
        pthread_exit((void *) EXIT_FAILURE);
    }
    // in a while loop, read from the scoket and write to the file
    // within the while loop, if sleep_flap > 0, usleep()
    while((bytes_read = read(sockfd, buffer, MAXLINE)) > 0) {
            
            if(sleep_flag > 0) {
              usleep(sleep_flag);
            }
            write(fd, buffer, bytes_read);
        }

    // close file descriptor
    close(fd);
    // close socket
    close(sockfd);
    // free
    free(cmd);

    current_connections_dec();

    pthread_exit((void *) EXIT_SUCCESS);
}

void *
thread_dir(void *p)
{
    cmd_t *cmd = (cmd_t *) p;
    FILE *fp;
    char buffer[MAXLINE];
    int sockfd;

    current_connections_inc();
    
    //sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sockfd = cmd->sock;    
    fp = popen(CMD_DIR_POPEN, "r");
    if (fp == NULL) {
        // barf
        // close, free, skedaddle
        free(cmd);
        close(sockfd); 
        
        pthread_exit((void *) EXIT_FAILURE);
    }
    memset(buffer, 0, sizeof(buffer));
    // in a while loop, read from fp, write to the socket
    while(fgets(buffer, sizeof(buffer), fp) != NULL) {
            write(sockfd, buffer, strlen(buffer));
        }
    // pclose
    pclose(fp);
    // close the socket
    close(sockfd);
    // free
    free(cmd);

    current_connections_dec();

    pthread_exit((void *) EXIT_SUCCESS);
}

// I should REALLY put these fucntions and their related variables
// in a seperate source file.
void
current_connections_inc(void)
{

    // lock
    pthread_mutex_lock(&connections_mutex);
    // increment
    current_connections++;
    // unlock
    pthread_mutex_unlock(&connections_mutex);
}

void
current_connections_dec(void)
{

    // lock
    pthread_mutex_lock(&connections_mutex);
    // decrement
    current_connections--;
    // unlock
    pthread_mutex_unlock(&connections_mutex);
}

unsigned int
current_connections_get(void)
{
    return current_connections;
}
