//Matthew Penner
//Lab #1
//Part Two: mywc.c
//CS333

/*
SOURCES CITED:
https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
https://www.geeksforgeeks.org/c-program-print-contents-file/
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#ifndef FALSE
# define FALSE 0
#endif // FALSE
#ifndef TRUE
# define TRUE 1
#endif // TRUE

#define DELIMITERS " ()\n"
#define BUF_SIZE 50000
#define MAX_LINE_LENGTH 1024
#define MAX_NAME 99
static int is_verbose = FALSE;

int
main (int argc, char *argv[])
{
  
  int opt;
  
  //Initialize the flags for each of what we are keeping track of
  int charflag;
  int wordflag;
  int lineflag;
  char *file_name = NULL;
  opterr = 0;
  
  FILE *ifile = stdin;
  
  
  while ((opt = getopt (argc, argv, "clwf:hv")) != -1)
  {
    switch (opt)
    {
      // The char flag is enabled
      case 'c':
        // Turn this on!
        charflag = 1;
        break;
      case 'l':
        // Turn this on!
        lineflag = 1;
        break;
      case 'w':
        // Turn this on!
        wordflag = 1;
        break;
      case 'f':
        // Set the variable "file_name" equal to the name of the file
        file_name = optarg;
        //Uh oh, file name is null
        if(file_name == NULL) {
          fprintf(stderr, "Cannot open file");
          return 2;
        }
        else {
          //Open the file up
          ifile = fopen(file_name, "r");
          //Error check
          if (ifile == NULL) {
            perror("Cannot open file");
            return 2;
          }
        }
        break;
      case 'v': //Turn on verbose mode
        is_verbose = !is_verbose;
        break;
      case 'h': //List the options with correct indentations
        printf("\toptions: clwf:hv\n");
        printf("\t-c\t: display the number of characters in the input\n");
        printf("\t-l\t: display the number of lines in the input\n");
        printf("\t-w\t: display the number of words in the input\n");
        printf("\t-f file : use file as input, defaults to stdin\n");
        printf("\t-h\t: display a command options and exit\n");
        printf("\t-v\t: give LOTS of gross verbose trace output to stderr.\n");
        return 0;
      
      default: //Uh oh, something went wrong
        fprintf(stderr, "Unknown option: -%c\n", optopt);
        return 1;
     
    }
  }
  char buffer[BUF_SIZE] = {0};

  // Set the counts outside the while loop and then increment them inside it
  size_t char_count = 0;
  size_t line_count = 0;
  size_t word_count = 0;
  while(fgets(buffer, BUF_SIZE, ifile)) {
    if(!charflag && !lineflag && !wordflag)
    {
      charflag = TRUE;
      lineflag = TRUE;
      wordflag = TRUE;
    }
    if(charflag) 
    { 
      char_count += strlen(buffer);  
    }
    if(wordflag) 
    { 
      char *token = strtok(buffer, DELIMITERS);
      while(token)
      {
        word_count++;
        token = strtok(NULL, DELIMITERS);
      }     
    }
    if(lineflag) 
    { 
      line_count++;      
    }
  }

  if(lineflag)
  {
    printf("%ld ", line_count);
  }

  if(wordflag)
  {
    printf("%ld ", word_count);
  }

  if(charflag)
  {
    printf("%ld ", char_count);
  }

  if(file_name)
  {
    printf("%s\n", file_name);
  }
  if(ifile != stdin)
    fclose(ifile);
  
  return 0;
}
