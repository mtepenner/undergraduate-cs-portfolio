/*


This is the .h file where I have initialized each of the structs and
the table class.  I am also reusing my animal struct from the previous
programs for data entries into the ADT being used for this assignment.

*/

#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

struct animal
{
    animal();
    ~animal();
    int copy_entry(const animal & copy_from); //Copies an animal over
    int display(); //displays an animal
    int fill(char BREED[], char CATEGORY[], char PERSONALITY[], char PURPOSE[], char SIZE[], char KEYWORDS[], int AGE); //Fills an animal with data parameters...
    char * breed;
    char * category;
    char * personality;
    char * purpose;
    char * size;
    char * keywords;
    int age;
};

struct vertex
{
      
  animal * entry;        //nullptr, if the vertex isn't set
  struct node * head;    //edge list
};

struct node
{
  vertex * adjacent;	  //Additional data would be needed for a weighted graph
  node * next;
};



class table
{
  public:        
    table(int size=5); //Constructor                                
    int insert_vertex(const animal & to_add); //Inserts a vertex with a new animal into the graph
    int find_location(char * key_value); //Used with the edge function to figure out which index is being attached               
    int insert_edge(char * first_key_value, char * second_key_value); //Connection established between two vertices, multiple edges can create a path
    int display_adjacent(); /*Displays  the  adjacency  list,  
    traversing  through  the  edge  list  for each vertex*/
        
    ~table(void); /*Destructor; deallocates all dynamic memory (e.g., destructor)    */  
  private:
    int remove_all(int i);
    vertex * adjacency_list;
    int list_size;

};
