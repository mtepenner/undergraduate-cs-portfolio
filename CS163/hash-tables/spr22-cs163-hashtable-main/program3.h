/*
Matthew Penner
05/3/2022
Professor Fant

This is my main .h file, where I have initialized my Animal class which holds the parameters of the Animal, 
including the breed, category, personality, purpose, size, keywords, and the age of the animal.  Additionally,
I have a struct node for iterating through each part of the table of Animals, and the hash table class created,
which has all the functions specified by the assignment.

*/

#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cctype>
#include <fstream>
using namespace std;


struct animal
{
    animal();
    ~animal();
    int copy_entry(const animal & copy_from); //Copies an animal over
    int display(); //displays an animal
    int fill(char BREED[], char CATEGORY[], char PERSONALITY[], char PURPOSE[], char SIZE[], char KEYWORDS[], int AGE); //Fills an animal with data parameters
    char * breed;
    char * category;
    char * personality;
    char * purpose;
    char * size;
    char * keywords;
    int age;
};

struct node
{
       animal entity; //just one animal entry
       node * next;
};


class table
{
      public:
             table(int size=5); //Constructor 
             int add_animal(char * key, animal & to_add); //Add an animal   
             bool retrieve(char * keyword_to_find, animal animal_array[]); //Retrieve information for a match by keyword
             int remove_by_keywords(char * keyword_to_find); //Remove animals based on keyword
             ~table(void); //Destructor
             int display_all(); //Display function for testing 
             int display_all(int i); //Display function for testing 
             int display_with_personality_type(char * personality_to_find); /*Look for
             specific animals based on their personality*/
             int display_with_keyword_type(char * keyword_to_find); /*Look for
             specific animals based on inputted keyword*/
             int load(); //Read in data from file
      private:
            node ** hash_table;  //a dynamically allocated array of head pointers
            int hash_function(char * key); //Private hash function
	          int hash_table_size;
            
            
              
};
