
// Matthew Penner

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <crypt.h>
#include <pthread.h>

#include "thread_crypt.h"

#define BUF_SIZE 1000

static int is_verbose = 0;
// ... 
// a plethora of global variables
static int hash_algo = 0;
FILE *op_file;
FILE *ip_file;
static int salt_len = 0;

static char *read_input_file(char *);
static void *hash_pass(void *);
static char *buffer;
static int check;
static int hash_counter[20] = {0};
static char yescrypt_param[4] = {'\0'};
//static char yescrypt_param = YESCRIPT_PARMS_DEFAULT;
static int crypt_rounds = SHA_ROUNDS_DEFAULT;
unsigned int seed = 3;
char *crypt_rounds_str;
// a couple more functions
// see below

char *ip_str = NULL;
static char * get_next_word(void);
static void gen_salt(char *);
//everything past colon is salt settings
//wait until you are done with getopt
//rounds of -10, NOT viable
//slow on purpose, better security

//be exceedingly patient



int
main(int argc, char *argv[])
{
    char *ip_filename = NULL;
    char *op_filename = NULL;
    int num_threads = 1;
    int result = 0;
    
    pthread_t *threads;
    strcpy(yescrypt_param, YESCRIPT_PARMS_DEFAULT);
    {
        int opt = 0;
        
        while((opt = getopt(argc, argv, OPTIONS)) != -1) {
            switch(opt) {
            case 'i':
                if(is_verbose) {
                    fprintf(stderr, "input file: %s\n", optarg);
                }
                ip_filename = optarg;
                
                break;
            case 'o':
                if(is_verbose) {
                    fprintf(stderr, "output file: %s\n", optarg);
                }
                op_filename = optarg;
                break;
            case 't':
                num_threads = atoi(optarg);
                if ((num_threads < 1) || (num_threads > 20)) {
                    printf("invalid thread count %d\n", num_threads);
                    exit(1);
                }
                if(is_verbose) {
                    fprintf(stderr, "thread count: %d\n", num_threads);
                }
                break;
            case 'R':
                // store the seed
                
                seed = (unsigned int)atoi(optarg);
                result = seed;
                if (result < 0) {
                    fprintf(stderr, "incorrect seed %s\n", optarg);
                    exit(1);
                }
                break;
            case 'a':
                // i stored the first letter so i could use in switch statements
                
        
                // validate the hash algorithm
                hash_algo = optarg[0];
                if (is_verbose) {
                    fprintf(stderr, "hash_algo is %c\n", hash_algo);
                }
                switch (hash_algo) {
                case '0': // DES
                    break;
                case '1': // MD5
                    break;
                case '3': // MD5
                    break;
                case '5': // SHA-256
                    break;
                case '6': // SHA-512
                    break;
                case 'b': // bcrypt
                    break;
                case 'y': // yescrypt
                    break;
                case 'g': // gost-yescrypt
                    break; // Valid algorithm, proceed
                default:
                    fprintf(stderr, "invalid hashing algorithm: %s\n", optarg);
                    exit(1);
                    break;
                }
                
                break;
            case 'p':
                // the params for yescrypt and gost-yescrypt
                strncpy(yescrypt_param, optarg, sizeof(yescrypt_param) - 1);
                if (is_verbose) {
                    fprintf(stderr, "yescript/gost-yescript params: %s\n"
                            , yescrypt_param);
                }
                break;
            case 'r':
                // rounds for sha* and bcrypt
                crypt_rounds = atoi(optarg);
                break;
            case 'l':
                // the length of the salt. i validate elsewhere
                salt_len = atoi(optarg);
                break;
            case 'v':
                is_verbose++;
                break;
            case 'h':
                fprintf(stderr, "%s ...\n\tOptions: %s\n"
                        , argv[0], OPTIONS);
                fprintf(stderr, "\t-i file\t\tinput file name (required)\n");
                fprintf(stderr, "\t-o file\t\toutput file name (default stdout)\n");
                fprintf(stderr, "\t-a %s\talgorithm to use for hashing\n"
                        , ALGORITHMS);
                fprintf(stderr, "\t\t\tsee \'man 5 crypt\' for more information\n");
                fprintf(stderr, "\t\t\t0: DES - the default\n");
                fprintf(stderr, "\t\t\t1: md5\n");
                fprintf(stderr, "\t\t\t3: NT\n");
                fprintf(stderr, "\t\t\t5: SHA-256\n");
                fprintf(stderr, "\t\t\t6: SHA-512\n");
                fprintf(stderr, "\t\t\tb: bcrypt\n");
                fprintf(stderr, "\t\t\ty: yescrypt\n");
                fprintf(stderr, "\t\t\tg: gost-yescrypt\n");
                fprintf(stderr, "\t-l #\t\tlength of salt\n");
                fprintf(stderr, "\t\t\tvalid length depends on algorithm\n");
                fprintf(stderr, "\t-r #\t\trounds (SHA-256, SHA-512, bcrypt)\n");
                fprintf(stderr, "\t\t\tvalid rounds depends on algorithm\n");
                fprintf(stderr, "\t-p str\t\tparameters to use for"
                        " yescript or gost-yescript\n\t\t\t(default is \"%s\")\n"
                        , YESCRIPT_PARMS_DEFAULT);
                fprintf(stderr, "\t-R #\t\tseed for rand_r() (default %d)\n"
                        , DEFAULT_SEED);
                fprintf(stderr, "\t-t #\t\tnumber of threads to create (default 1)\n");
                fprintf(stderr, "\t-v\t\tenable verbose mode\n");
                fprintf(stderr, "\t-h\t\thelpful text\n");
                exit(EXIT_SUCCESS);
                break;
            default:
                fprintf(stderr, "oopsie - unrecognized command line option \"%s\"\n"
                        , argv[optind]);
                break;
            }
        }
    }
    if(op_filename != NULL) {
        op_file = fopen(op_filename, "w"); 
        if (!op_file) {
            fprintf(stderr, "failed to open output file: %s\n", op_filename);
            exit(1);
        }
    }
    else {
        // WHAT!!!??? A global variable!!!??? These are hard to init
        op_file = stdout;
    }
    if(ip_filename == NULL) {
        fprintf(stderr, "must provide input file name\n");
        exit(EXIT_FAILURE);
    }
     
    
    // validate salt length
    switch (hash_algo) {
    case '0':
        salt_len = DES_SALT_LEN;
        if(is_verbose) {
          fprintf(stderr, "algorithm is DES\n");
        }
        break;
    case '1':
        // think about MAX_MD5_SALT_LEN
        salt_len = MAX_MD5_SALT_LEN;
        if(is_verbose) {
          fprintf(stderr, "algorithm is md5\n");
        }
        break;
    case '5':
        salt_len = MAX_SHA_SALT_LEN;
        if(is_verbose) {
          fprintf(stderr, "algorithm is sha256\n");
        }
        break;
    case '6':
        // look at *_SHA_SALT_LEN
        salt_len = MAX_SHA_SALT_LEN;
        if(is_verbose) {
          fprintf(stderr, "algorithm is sha512\n");
        }
        break;
    case 'y':
        salt_len = MAX_YES_SALT_LEN;
        if(is_verbose) {
          fprintf(stderr, "algorithm is yescrypt\n");
        }
        break;
    case 'g':
        // look at *_YES_SALT_LEN
        salt_len = MAX_YES_SALT_LEN;
        if(is_verbose) {
          fprintf(stderr, "algorithm is gost-yescrypt\n");
        }
        break;
    case 'b':
        // alwats MAX_BCRYPT_SALT_LEN
        salt_len = MAX_BCRYPT_SALT_LEN;
        if(is_verbose) {
          fprintf(stderr, "algorithm is bcrypt\n");
        }
        break;
    case '3':
        salt_len = 0;
        if(is_verbose) {
          fprintf(stderr, "algorithm is NT\n");
        }
        break;
    default:
        break;
    }
     
    
    // take care of the rounds
    if ((hash_algo == '5') || (hash_algo == '6')) {
        // look at SHA_ROUNDS_*
        if(crypt_rounds < SHA_ROUNDS_MIN) {
            crypt_rounds = SHA_ROUNDS_MIN;
        }
        else if(crypt_rounds > SHA_ROUNDS_MAX) 
        {
            crypt_rounds = SHA_ROUNDS_MAX;
        }
    }
    if (hash_algo == 'b') {
        // always 
        // look at BCRYPT_ROUNDS_*
        if(crypt_rounds < BCRYPT_ROUNDS_MIN) {
            crypt_rounds = BCRYPT_ROUNDS_MIN;
        }
        else if(crypt_rounds == SHA_ROUNDS_DEFAULT) {
            crypt_rounds = BCRYPT_ROUNDS_DEFAULT;
        }
        
        else if(crypt_rounds > BCRYPT_ROUNDS_MAX) {
            crypt_rounds = BCRYPT_ROUNDS_MAX;
        }
        
        
    }
    
    
    // take care of the rounds string
    // i have a string that represnts the string used for rounds.
    // i want to generate it ONCE
    switch (hash_algo) {
    case '5':
        crypt_rounds_str = malloc(crypt_rounds);
        sprintf(crypt_rounds_str, "rounds=%d$", crypt_rounds);
    
        if (is_verbose) {
            fprintf(stderr, "Rounds = %d Rounds string %s\n", crypt_rounds
                    , (crypt_rounds_str ? crypt_rounds_str : "none"));
        }
        break;
    case '6':
        crypt_rounds_str = malloc(crypt_rounds);
        sprintf(crypt_rounds_str, "$6$rounds=%d$", crypt_rounds);
    
        if (is_verbose) {
            fprintf(stderr, "Rounds = %d Rounds string %s\n", crypt_rounds
                    , (crypt_rounds_str ? crypt_rounds_str : "none"));
        }
        break;
    case 'y':
       
    case 'g':
        crypt_rounds_str = malloc(100); 
        memset(crypt_rounds_str, 0, 100);
        if(strlen(yescrypt_param) > 0) {
            sprintf(crypt_rounds_str, "$%s$", yescrypt_param);
            
        }
        else {
            sprintf(crypt_rounds_str, "$%s$", YESCRIPT_PARMS_DEFAULT);
                    
        }
        
        if (is_verbose) {
            fprintf(stderr, "y/g = Params string %s\n"
                    , (crypt_rounds_str ? crypt_rounds_str : "none"));
            
        }
        break;
    case 'b':
        crypt_rounds_str = malloc(100); 
        memset(crypt_rounds_str, 0, 100);
        
        sprintf(crypt_rounds_str, "$%02d$", crypt_rounds);

       
        if (is_verbose) {
            fprintf(stderr, "bcrypt rounds %s\n", crypt_rounds_str);
        }
        break;
    default:
        break;
    }
    if (is_verbose) {
        fprintf(stderr, "Length of salt = %d\n", salt_len);
    }

    // read the input file as a big gulp
    
    buffer = read_input_file(ip_filename);
    // allocate thread stuff
    threads = malloc(num_threads * sizeof(pthread_t));        
    
    // spin up the threads
        
    if (is_verbose) {
        fprintf(stderr, "Threads spun up\n");
    }

    
    for (long i = 0; i < num_threads; ++i) {
        if(pthread_create(&(threads[i]), NULL, hash_pass, (void *)i) != 0) {
          perror("Error: could not create threads\n");
          exit(EXIT_FAILURE);
          
        }
    }
    

    // spin down the threads
    for(int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        
    }
    if (is_verbose) {
        fprintf(stderr, "Threads joined\n");
    }    
    // show per thread hash count
    
    for(int i = 0; i < num_threads; i++) {
        fprintf(stdout, "\tthread %d: hashes %d\n", i, hash_counter[i]);
    }
    // free allocated memory
    free(threads);
    if (op_filename != NULL) {
        
        fclose(op_file);
    }
    
    pthread_exit(EXIT_SUCCESS);
    //return EXIT_SUCCESS;
}

// big gulp
static char *
read_input_file(char *ip_filename)
{
    struct stat file_stat; // what would a stat structure do here?
    ssize_t bytes_read = 0;
    // swallow the whole file in one swell foop
    if(stat(ip_filename, &file_stat) < 0) {
      perror("Attempt to get stats for file failed");
      return NULL;
    
    }
    ip_file = fopen(ip_filename, "r");
    if(!ip_file) {
      perror("Failed to open input file");
      free(buffer);
      return NULL;
    }
    buffer = (char *)malloc(file_stat.st_size + 1); 
    if (!buffer) {
        perror("Failed to allocate memory for input string");
        exit(EXIT_FAILURE);
    }
    bytes_read = fread(buffer, 1, file_stat.st_size, ip_file);
    if(bytes_read < 0) {
      perror("Failed to read contents of file");
      fclose(ip_file);
      free(buffer);
      return NULL;
    
    }
    
    buffer[bytes_read] = '\0';
    
    fclose(ip_file);
    return buffer;
}

// step through the words
static char *
get_next_word(void)
{
    // teenage mutant ninja Texans
    // strtok() is a cool thing, with the right locks
    const char *delimiters = " \n\t\r";
    static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;    
    char *word = NULL;
    pthread_mutex_lock(&lock);
      if(check < 1) {
        if(buffer) {
          word = strtok(buffer, delimiters);
          check += 1;
        }
      }
      else {
        word = strtok(NULL, delimiters);
      }
      
    
    pthread_mutex_unlock(&lock);
    
    return word;
}

// done some actual work
static void *
hash_pass(void *arg)
{
    struct crypt_data crypt_stuff;
    char *hash;
    char *word;
    long tid = (long) arg;
    char salt[1000];
    
    memset(&crypt_stuff, 0, sizeof(crypt_stuff));
    crypt_stuff.initialized = 0;
    // loop through all the words, using get_next_word()
    
    
    for(word = get_next_word(); word != NULL; word = get_next_word()) {

      gen_salt(salt);
      
      hash = crypt_r(word, salt, &crypt_stuff);
      
      if(op_file) {
        fprintf(op_file, "%s:%s\n", word, hash);
      }
      
      else {
        fprintf(stdout, "%s:%s\n", word, hash);
      }
      if (is_verbose > 2) {
        fprintf(stderr, "\t\t%s : %s  %s\n", word, hash, salt);
    }
      hash_counter[tid] += 1;
    }
    pthread_exit(EXIT_SUCCESS);
}

// generate the salt/settings for each word
static void
gen_salt(char *settings)
{
    static const char salt_chars[] = {SALT_CHARS};
    static const size_t len = sizeof(salt_chars) - 1;
    char salt[CRYPT_OUTPUT_SIZE] = {'\0'};
    int rand_value = 0;
    switch(hash_algo)
    {
    case '1':
        for(int i = 0; i < salt_len; ++i) {
            rand_value = rand_r(&seed) % len;
            salt[i] = salt_chars[rand_value];
        }
        sprintf(settings, "$1$%s$", salt);
        break;
    case '5':
        memset(salt, 0, CRYPT_OUTPUT_SIZE);
        for(int i = 0; i < salt_len; ++i) {
            rand_value = rand_r(&seed) % len;
            salt[i] = salt_chars[rand_value];
        }
        sprintf(settings, "$5$rounds=%d$%s$", crypt_rounds, salt);
        break;
    case '6':
        memset(salt, 0, CRYPT_OUTPUT_SIZE);
        for(int i = 0; i < salt_len; ++i) {
            rand_value = rand_r(&seed) % len;
            salt[i] = salt_chars[rand_value];
        }
        sprintf(settings, "$6$rounds=%d$%s$", crypt_rounds, salt);

        break;
    case 'y':
        memset(salt, 0, CRYPT_OUTPUT_SIZE);
        for(int i = 0; i < salt_len; ++i) {
            rand_value = rand_r(&seed) % len;
            salt[i] = salt_chars[rand_value];
        }
        sprintf(settings, "$y$%s$%s$", yescrypt_param, salt);
        break;
    case 'g':
        memset(salt, 0, CRYPT_OUTPUT_SIZE);
        for(int i = 0; i < salt_len; ++i) {
            rand_value = rand_r(&seed) % len;
            salt[i] = salt_chars[rand_value];
        }
        sprintf(settings, "$gy$%s$%s$", yescrypt_param, salt);
        break;
    case 'b':
        memset(salt, 0, CRYPT_OUTPUT_SIZE);
        for(int i = 0; i < salt_len; ++i) {
            rand_value = rand_r(&seed) % len;
            salt[i] = salt_chars[rand_value];
        }
        sprintf(settings, "$2b$%d$%s$", crypt_rounds, salt);
        break;
    case '3':
        // NT ALGORITHM
        // NO SALT
        sprintf(settings, "$3$$");
        break;
    default:
        salt[0] = salt_chars[rand_r(&seed) % len];
        salt[1] = salt_chars[rand_r(&seed) % len];
	    sprintf(settings, "%s$", salt);
        break;
    }
    if (is_verbose > 1) {
        fprintf(stderr, "salt %s\n", salt);
    }    
}
