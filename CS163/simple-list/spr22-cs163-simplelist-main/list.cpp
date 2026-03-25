//Matthew Penner
//Professor Fant
//CS163 Data Structures
//4/15/2022
/*This file will have the implemented functions for the listclass.  I will write out the functions, 
and use at least one of them recursively.  The overall purpose of this file is that 
this is where the overall programming will go for the required functions
defined in the ADT class.

*/
#include "list.h"
#include <iostream>
using namespace std;

list::list()
{
   head = NULL; //Data members set here
}

list::~list()
{
  //deallocate all dynamic memory; loop through all and delete everything
  node * temp = NULL;
  while(head->next != NULL)
  {
    temp = head->next; //temporary variable to store the next node
    delete head; //bye bye head
    head = temp; //head is reborn...as temp
  }

}

int list::add_amenity(char NAME[100], char AMENITYNAME[25], char DETAILS[100], int RATING) //Adds an amenity to a dog park
{
  char * dynamicname = new char[strlen(NAME) + 1]; //Fits a standard char into a dynamically allocated one
  strcpy(dynamicname, NAME); //copies it over
  node * current = head; //iterates through list
  if(head == NULL || RATING > 10)
    return 0;
  else
  {
    while(current && strcmp(current->name, dynamicname)) //while current is not null and the strcmp does not equal zero
      current = current->next; //iterates through
    if (current == NULL) //Nothing in current
      return 0;  
    amenity * acurrent = current->head; //iterator for the LLL of amenities
    if(!acurrent) //Nothing in head
    {
        acurrent = new amenity; //New amenity node created
        
        acurrent->name = new char[strlen(AMENITYNAME) + 1]; //Fits a standard char into a dynamically allocated one
        strcpy(acurrent->name, AMENITYNAME); //copies it over
        
        acurrent->details = new char[strlen(DETAILS) + 1]; //Fits a standard char into a dynamically allocated one
        strcpy(acurrent->details, DETAILS); //copies it over
        
        acurrent->rating = RATING; //rating is set to number passed in
        
        acurrent->next = NULL; //The next node is set to null
	      current->head = acurrent; //The head is set to acurrent   
    }
    else //There is already something in head
    {
      amenity * previous = NULL; //A previous pointer is initialized
      bool flag = false; //A flag variable is created and set to false
      while(acurrent && !flag) //While acurrent is not null and while flag is false
      {
      	if(acurrent->rating <= RATING) /*This part of the code is where I had trouble. I tried to get the code
        to sort the LLL of amenities with the lowest rating going last, but could not resolve it*/
      	  flag=true; //Is true if the rating is bigger
      	else
      	{
      	  previous = acurrent; //Previous node set to acurrent
          acurrent=acurrent->next; //acurrent becomes next node
        }
      }
      amenity * newamenity = new amenity;
      
      newamenity->name = new char[strlen(AMENITYNAME) + 1]; //Fits a standard char into a dynamically allocated one
      strcpy(newamenity->name, AMENITYNAME); //copies it over
            
      newamenity->details = new char[strlen(DETAILS) + 1]; //Fits a standard char into a dynamically allocated one
      strcpy(newamenity->details, DETAILS); //copies it over
              
      newamenity->rating = RATING; //Rating set
              
      newamenity->next = acurrent; //Acurrent now comes next
      if(previous)
      	previous->next = newamenity; //The previous node is now newamenity.
      else
      {
	amenity * hold = current->head;
	current->head = newamenity;
	current->head->next = hold;
      }
    }
  }

  return 1;
  
}
int list::add(char NAME[100]) //Adds a dog park
{
  if(!head) //Nothing there
  {
    head = new node;
    head->next = NULL;
    head->name = new char[strlen(NAME) + 1]; //Fits a standard char into a dynamically allocated one
    strcpy(head->name, NAME); //copies it over
  }
  else //Park in head
  {
    node * current = head; //Traversal node
    while(current->next != NULL) 
      current = current->next;
    current->next = new node; //Creates a new node if there are none existing
    current = current->next;
    current->name = new char[strlen(NAME) + 1];
    strcpy(current->name, NAME); //copies NAME over
    current->next = NULL;
  }

  return 1;
}

int list::remove(char NAME[100])
{
  char * dynamicname = new char[strlen(NAME) + 1]; //Fits a standard char into a dynamically allocated one
  strcpy(dynamicname, NAME); //copies it over
  node * current = head;
  node * previous = current;
  
  if(!head) //Nothing there, nothing to remove
    return 0;
  else
  {
    while(current && strcmp(current->name, dynamicname)) //While not null and not the same
    {
      previous = current;
      current = current->next;
    }
    if(!current) //Base case
      return 0;
    if(current == head) //If only one park
    {
      head = current->next;
      delete current;
      return 1;
    }
    else //Multiple parks
    {
      node * temp = current-> next;
      delete current;
      previous->next = temp;
    }
  }
  return 1;
}
int list::display_all() //Wrapper function
{

  return display_all(head); //Accesses head, a private data member
}
int list::display_all(node * & head)
{
  int count = 1;
  if(!head)
    return count;
  else
  {
     cout << head->name << endl; 
     return count + display_all(head->next); //Moves onto next node recursively
  }
  
}

int list::display_all_amenities(char NAME[100]) //Displays all amenities
{
  node * current = head; //traversal node
  amenity * acurrent = NULL; //traversal amenity node
  char * dynamicname = new char[strlen(NAME) + 1]; //To fit client parameter
  strcpy(dynamicname, NAME); //copies it over
  
  if(!head) //Nothing there
    return 0;
  else
  {
    while(current && strcmp(current->name, dynamicname)) //While not null and not equal to 0
      current = current->next; //traverses
    if(!current) //nothing there
      return 0;
    amenity * acurrent = current->head; //acurrent set to head once in the correct dog park
    if(!current->head)
      return 0;
    else
    {
      while(acurrent)
      {
        cout << "Amenity Name: " << acurrent->name << endl << "Amenity Details: " << acurrent->details << endl << "Amenity Rating: " << acurrent->rating << endl;
        acurrent = acurrent->next; //iterates through and prints out the amenity details
      }
    }
  }
    
  
  
  return 1;
}

int list::display_with_amenity(char amenityname[25]) //Displays parks with specific amenities
{
  char * dynamicname = new char[strlen(amenityname) + 1]; //holds client parameter
  strcpy(dynamicname, amenityname);
  
  node * current = head; //traversal node
  amenity * acurrent = NULL; //traversal amenity node
  if(!head) //nothing there
    return 0;
  else
  {
    while(current) //While not null
    {
      if(!current->head) //No amenities
        current = current->next; //Moves on to another park
      acurrent = current->head;
      bool ismatch = false;
      while(acurrent)
      {
      	if(strcmp(acurrent->name, amenityname) == 0) //If the same amenity
      	   ismatch = true; 
        acurrent= acurrent->next;
      }
      if(ismatch)
        cout << current->name << endl; //Name of park possessing amenity is printed, then cycle repeats until current is NULL
      
      current=current->next; //Next park
    

    }
  
  }
  return 1;
  
}



























