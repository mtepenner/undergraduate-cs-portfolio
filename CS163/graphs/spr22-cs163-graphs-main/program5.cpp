/*

Here is the main cpp file for Program5 where I have written the main
functions for the program below.  These functions include a recursive
remove function for the destructor, the constructor, the function to 
create a new vertex in the graph, a function to establish a connection
between two nodes, a function that helps with inserting an edge by 
locating the animals with the respective keys, and a display function.

*/

#include "program5.h"

table::table(int size) //Allocates the adjacency list and set each head pointer to nullptr
{
    adjacency_list = new vertex [size]; //New adjacency list created
    for (int i = 0; i < size; ++i) //Every vertex is set to NULL
    { 
      adjacency_list[i].head = NULL; 
      adjacency_list[i].entry = NULL; 
    } 
    list_size = size; //The size passed in is set to the list_size private data member
}

table::~table() //Destructor
{
  int i = 0; //Iterator variable
  remove_all(i); //Function to remove every vertex is called
  delete [] adjacency_list;
  adjacency_list = NULL; //Adjacency list deleted
}

int table::remove_all(int i)
{
  if(!adjacency_list[i].entry) //Nothing to delete
    return 0; 
  node * temp = adjacency_list[i].head;
  while(temp)
  {
    temp = adjacency_list[i].head->next;
    delete adjacency_list[i].head; //Head is deleted for each index
    adjacency_list[i].head = temp;
    
  }
  delete adjacency_list[i].entry; //The same happens to the animal
  adjacency_list[i].entry = NULL; 
  
  ++i;
  return remove_all(i); //function called until completely emptied out list
  

}

int table::insert_edge(char * first_key_value, char * second_key_value) //Attaches an edge to a vertex
{
  int connection1 = find_location(first_key_value); //Index retrieved for the first animal
  cout << "First connection index: " << connection1 << endl;
  if(connection1 == -1)
    return 0;
  int connection2 = find_location(second_key_value); //and the second one
  cout << "Second connection index: " << connection2 << endl;
  if(connection2 == -1)
    return 0;
    
  node * temp = new node; //Temporary node created
  temp->adjacent = &adjacency_list[connection2]; //Adjacent vertex set to the second key
  temp->next = adjacency_list[connection1].head; //next node to temp set to head pointer of the first connection
  adjacency_list[connection1].head = temp; //First connection then set to temp
  return 1;      
}

int table::find_location(char * key_value) //Locates animal with provided index
{
  int found_location{0}; //Initially set to 0
  for (int i = 0; i < list_size; ++i) //Loops through the list to find the location
  { 
    if(adjacency_list[i].entry) //If an entry exists
    {
      if(strcmp(adjacency_list[i].entry->breed, key_value)==0) //Then it compares the passed in char with the animal key already provided
      {
        found_location = i; //Found is set to the index
        return found_location; //The loop is terminated
      }
    }
  } 
  
  return -1;
}

int table::insert_vertex(const animal & to_add) //Store the vertex at this location.
{
  int i = 0;
  
  while(i < list_size) //Loops until code finds a place to store the new animal
  {
    if(!adjacency_list[i].entry) //No animal exists
    {
      adjacency_list[i].entry = new animal; //New animal inserted
      adjacency_list[i].entry->copy_entry(to_add); //Animal's copy entry function is called
      i = list_size; //Loop is terminated
    }
    else
      ++i; //Otherwise increments


  }

  return 1;

}

int table::display_adjacent() //Displays  the  adjacency  list,  traversing  through  the  edge  list  for each vertex
{
  if(!adjacency_list[0].entry) //Nothing to return
    return 0;
  for (int i = 0; i < list_size; ++i) //Loops through the adjacency list
  {
    if(adjacency_list[i].entry) //If there is an entry
    {
      adjacency_list[i].entry->display(); //Entry displayed
	    node * current = adjacency_list[i].head; //Current initialized to the head pointer
	    while (current) 
	    { 
      	//display the animal by calling the display function 
      	if (current->adjacent) //If this node has an existing adjacent pointer...
	      {
  		    cout << "Adjacent node: ";
  		    current->adjacent->entry->display(); //Adjacent vertex is displayed
   		    cout << endl;
	      }
     		current = current->next; //Goes onto the next node
      }
  
    }
  }  
  
  return 1;   
}
