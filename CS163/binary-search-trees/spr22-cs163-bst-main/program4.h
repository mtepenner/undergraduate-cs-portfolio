#include <iostream>
#include <cstring>
/*



This is the .h file that contains all of the structs and classes used for this program.  I have several wrapper functions and private access functions that are all mostly 
recursive.  These functions are crucial as being part of my BST data structure.  I additionally have my animal struct with its respective functions, many of which are the exact same 
as previously used for program 3, such as fill, display, and the copy function.

*/
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
    animal object;
    node * left;
    node * right;;
};

class table
{
  public: //Here I have my constructor, destructor, and public wrapper functions
    table();
    ~table();
    int display_all();
    int display_all_breed(char * breed);
    int retrieve(int count, char * breed, char * personality, animal animal_array[]);
    int remove_all();
    int add_pet(animal & to_add);
    int remove_by_breed(char * breed);
    int display_with_size(char * size);
  private: //I have my root, and all of my private data functions
    node * root;
    int display_all_breed(node * & root, char * breed);
    int add_pet(node * & root, animal & to_add);
    int display_all(node * & root);
    int remove_all(node * & root);
    int display_with_size(node * & root, char * size);
    int remove_by_breed(node * & root, char * breed);
    int retrieve(int count, char * breed, char * personality, animal animal_array[], node * & root);

};
