#include "stack.h"
/*This file has all of the functions part of the stack class.  They include the constructor, destructor, and the other functions.
Those functions include push, pop, peek, and display.  I used a wrapper function for displaying so that recursion is included in the assignment overall.*/
stack::stack()
{
  head = NULL; //Data members set here
}

stack::~stack()
{
 //deallocate all dynamic memory; loop through all and delete everything
  s_node * temp = NULL;
  if(head)
  {
    while(head->next != NULL)
    {
      temp = head->next; //temporary variable to store the next node
      delete head; //bye bye head
      head = temp; //head is reborn...as temp
    }
  }
  

}

int stack::copy_stack(const stack & data) //Copies a stack into an assignment
{
  s_node * dcurrent = data.head; //accesses the head of the passed in stack
  s_node * current = head; //the head of this stack
  while(dcurrent)
  {
    current = new s_node;
    current->next = NULL;
    for(int i = 0; i <= dcurrent->top_index-1; ++i){
      int show = push(dcurrent->object[i]);} //Uses the copy_entry function to make this possible
    dcurrent = dcurrent->next;
    current = current->next;
    
  }
  
  return 1;
}

//Add a new item to the top of stack
int stack::push(book & data)
{
  s_node * temp;
  int MAX = 2;
  if(!head) //Nothing in head, better make a head
  {
    head = new s_node;  
    head->object = new book[MAX]; 
    head->next = NULL; 
    head->top_index = 0; 
  }
  
  if(head->top_index == MAX) //Head is full, time for a new node
  {
    temp = head;
    head = new s_node;
    head->object = new book[MAX]; 
    head->next = temp; 
    head->top_index = 0; 
  }
  
  if (head->object[head->top_index].copy_entry(data)) 
     ++head->top_index; 
  return 1;
}

//Remove the top of stack
int stack::pop()
{
  s_node * hold = head->next; 
  if (!head->top_index) 
  { 
    if (head->object) 
      delete [] head->object; 
    delete head; 
    head = hold; 
    head->top_index = 2; 
  }
  --head->top_index; //Instead of trying to delete an array element, the top_index is decremented so that it won't be displayed
  return 1;
}


int stack::peek() //Displays the book at the top of the stack
{
  if(!head)
    return 0;
  else{
    for(int i = head->top_index-1; i > head->top_index-2; --i){
      int show = head->object[i].display();}

  return 1;}
}

int stack::display() //Wrapper function
{

  return display(head); //Accesses the private display function as well as head, a private data member
}
int stack::display(s_node * & head)
{
  if(!head)
    return 0;
  else
  {
    for(int i = head->top_index-1; i > -1; --i){
       int show = head->object[i].display();} //Iterates through each node and the array elements, and displays them
  }
  return 1 + display(head->next); //Moves onto next node recursively
  
}

