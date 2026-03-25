

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

static unsigned short is_verbose = 0; //verbose flag
static unsigned sleep_flag = 0; //sleep flag

static char ip_addr[50] = "131.252.208.23"; //default ip address
static short ip_port = DEFAULT_SERV_PORT; //default server port address

int get_socket(char *, int); //retrieve the socket
void get_file(char *); //retrieve the file from the server
void put_file(char *); 
void *thread_get(void *);
void *thread_put(void *);
void list_dir(void);

int
main(int argc, char *argv[])
{
    
    cmd_t cmd;
    int opt;
    int i;
    
    memset(&cmd, 0, sizeof(cmd_t));
    


    while ((opt = getopt(argc, argv, CLIENT_OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            // copy optarg into the ip_addr
            strcpy(ip_addr, optarg);
            break;
        case 'p':
            // CONVERT and assign optarg to ip_port
            sscanf(optarg, "%hd", &ip_port);
            break;
        case 'c':
            // copy optarg into data member cmd.cmd
            strcpy(cmd.cmd, optarg);
            break;
        case 'v':
            is_verbose++;
            break;
        case 'u':
            // add 1000 to sleep_flag
            sleep_flag += 1000;
            break;
        case 'h':
            fprintf(stderr, "%s ...\n\tOptions: %s\n"
                    , argv[0], CLIENT_OPTIONS);
            fprintf(stderr, "\t-i str\t\tIPv4 address of the server (default %s)\n"
                    , ip_addr);
            fprintf(stderr, "\t-p #\t\tport on which the server will listen (default %hd)\n"
                    , DEFAULT_SERV_PORT);
            fprintf(stderr, "\t-c str\t\tcommand to run (one of %s, %s, or %s)\n"
                    , CMD_GET, CMD_PUT, CMD_DIR);
            fprintf(stderr, "\t-u\t\tnumber of thousands of microseconds the client will sleep between read/write calls (default %d)\n"
                    , 0);
            fprintf(stderr, "\t-v\t\tenable verbose output. Can occur more than once to increase output\n");
            fprintf(stderr, "\t-h\t\tshow this rather lame help message\n");
            exit(EXIT_SUCCESS);
            break;
        default:
            fprintf(stderr, "*** Oops, something strange happened <%s> ***\n", argv[0]);
            break;
        }
    }

    if (is_verbose) {
        fprintf(stderr, "Command to server: <%s> %d\n"
                , cmd.cmd, __LINE__);
    }
    if (strcmp(cmd.cmd, CMD_GET) == 0) {
        // process the files left on the command line, creating a threas for
        // each file to connect to the server
        for (i = optind; i < argc; i++) {
            pthread_t tid;
            // create threads
            // pass the file name as the ONE parameter to the thread function
            if(pthread_create(&tid, NULL, thread_get, (void *)argv[i]) != 0) {
              perror("Error: could not create threads\n");
              exit(EXIT_FAILURE);
              
            }
            
        }
    }
    else if (strcmp(cmd.cmd, CMD_PUT) == 0) {
        // process the files left on the command line, creating a threas for
        // each file to connect to the server
        for (i = optind; i < argc; i++) {
            pthread_t tid;
            // create threads
            // pass the file name as the ONE parameter to the thread function
            if(pthread_create(&tid, NULL, thread_put, (void *)argv[i]) != 0) {
              perror("Error: could not create threads\n");
              exit(EXIT_FAILURE);
              
            }
            
        }
    }
    else if (strcmp(cmd.cmd, CMD_DIR) == 0) {
        list_dir();
    }
    else {
        fprintf(stderr, "ERROR: unknown command >%s< %d\n", cmd.cmd, __LINE__);
        exit(EXIT_FAILURE);
    }

    pthread_exit(NULL);
}

int
get_socket(char * addr, int port)
{
    // configure and create a new socket for the connection to the server
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));

    // more stuff in here
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);

    if(inet_pton(AF_INET, addr, &servaddr.sin_addr.s_addr) <= 0) 
    {
      perror("Error converting from text to binary\n");
      exit(1);
    
    }
    
    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
    {
      perror("Failed to establish connection\n");
      
      exit(EXIT_FAILURE);
    }



    return(sockfd);
}

// get one file
void
get_file(char *file_name)
{
    cmd_t cmd;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int fd;
    ssize_t bytes_read;
    char buffer[MAXLINE];


    strcpy(cmd.cmd, CMD_GET);
    if (is_verbose) {
        fprintf(stderr, "next file: <%s> %d\n", file_name, __LINE__);
    }
    strcpy(cmd.name, file_name);
    if (is_verbose) {
        fprintf(stderr, "get from server: %s %s %d\n", cmd.cmd, cmd.name, __LINE__);
    }

    // get the new socket to the server (get_socket(...)
    sockfd = get_socket(ip_addr, ip_port);
    // write the command to the socket
    if(write(sockfd, (void *) &cmd, sizeof(cmd_t)) != sizeof(cmd_t))
    {
      perror("write the command to the socket");
      exit(1);
    } 
    // open the file to write
    fd = open(cmd.name, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(fd < 0) {
        exit(1);

    }
    // loop reading from the socket, writing to the file
    //   until the socket read is zero
    while((bytes_read = read(sockfd, buffer, MAXLINE)) > 0) {
            
	    // put usleep delay
	      usleep(sleep_flag);
        write(fd, buffer, bytes_read);
        }
    // close the file
    close(fd);
    // close the socket
    close(sockfd);
    
}

void
put_file(char *file_name)
{
    cmd_t cmd;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int fd;
    ssize_t bytes_read;
    char buffer[MAXLINE];
   

    
    strcpy(cmd.cmd, CMD_PUT);
    if (is_verbose) {
        fprintf(stderr, "next file: <%s> %d\n", file_name, __LINE__);
    }
    strcpy(cmd.name, file_name);
    if (is_verbose) {
        fprintf(stderr, "put to server: %s %s %d\n", cmd.cmd, cmd.name, __LINE__);
    }

    // get the new socket to the server (get_socket(...)
    sockfd = get_socket(ip_addr, ip_port);
    // write the command to the socket
    if(write(sockfd, (void *) &cmd, sizeof(cmd_t)) != sizeof(cmd_t))
    {
      perror("write the command to the socket");
      exit(1);
    } 
 
    // open the file for read
    fd = open(cmd.name, O_RDONLY);
    // loop reading from the file, writing to the socket
    //   until file read is zero
    while((bytes_read = read(fd, buffer, MAXLINE)) > 0) { //was !=0
            
            usleep(sleep_flag);
            write(sockfd, buffer, bytes_read);
        }
    // close the file
    close(fd);
    // close the socket
    close(sockfd);
}

void
list_dir(void)
{
    cmd_t cmd;
    int sockfd;
    ssize_t bytes_read;
    char buffer[MAXLINE];
     
    
    memset(&cmd, 0, sizeof(cmd_t));    
    printf("dir from server: %s \n", ip_addr);

    // get the new socket to the server (get_socket(...)
    sockfd = get_socket(ip_addr, ip_port);

    strcpy(cmd.cmd, CMD_DIR);
    // write the command to the socket
    if(write(sockfd, (void *) &cmd, sizeof(cmd_t)) != sizeof(cmd_t))
    {
      perror("write the command to the socket");
      exit(1);
    } 
 
 
  
    // loop reading from the socket, writing to the file
    //   until the socket read is zero
    while((bytes_read = read(sockfd, buffer, sizeof(buffer) -1 )) > 0) {
            write(STDOUT_FILENO, buffer, bytes_read);
        
        }
    // close the socket
    close(sockfd);
}

void *
thread_get(void *info)
{
    char *file_name = (char *) info;

    // detach this thread 'man pthread_detach' Look at the EXMAPLES
    pthread_detach(pthread_self());
    // process one file
    get_file(file_name);

    pthread_exit(NULL);
}

void *
thread_put(void *info)
{
    char *file_name = (char *) info;

    // detach this thread 'man pthread_detach' Look at the EXMAPLES
    pthread_detach(pthread_self());
    // process one file
    put_file(file_name);

    pthread_exit(NULL);
}
