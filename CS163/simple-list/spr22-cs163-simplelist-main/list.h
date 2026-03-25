//Matthew Penner
//Karla Fant, CS163
/*This file will initialize the list class alongside the respective nodes.  The node struct will hold 
the name of the dog park, a pointer to a list of amenities, and a next node.*/
#include <cctype>
#include <cstring>
#include <iostream>
using namespace std;

struct node;
struct amenity;

class list
{
  public:
    list(); //default constructor
    ~list(); //destructor
    int add(char NAME[100]); //Adds a dog park to the LLL
    int add_amenity(char NAME[100], char AMENITYNAME[25], char DETAILS[100], int RATING); //Adds an amenity
    int remove(char NAME[100]);
    int display_all(); //Wrapper function 
    int display_all(node * & head); //Displays all of the parks by name
    int display_all_amenities(char NAME[100]); //displays all amenities in a given park
    int display_with_amenity(char amenityname[25]); //Displays parks with specific amenities
  private:
    node * head;
};

struct amenity //One of two structs that allows for a LLL of amenities in each node
{
  amenity * next;
  char * name; //Name of the amenity
  char * details; //Description of it
  int rating; //Rating of it
};

struct node //A dog park
{
  char * name; //Name of dog park
  node * next; //A pointer to the next dog park
  amenity * head; //An amenity head pointer
  
};


