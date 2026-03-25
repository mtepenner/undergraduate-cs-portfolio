#include "queue.h"
/*This file has functions that are part of the queue class.  This includes the constructor and destructor.  Additionally, there is the enqueue which adds an assignment to a queue 
of assignments, dequeue which removes the next assignment due, peeking at the next assignment due, and displaying all assignments.*/
queue::queue()
{
  rear = NULL; //Data members set here
}

queue::~queue()
{
 //deallocate all dynamic memory; loop through all and delete everything
  q_node * temp = NULL;
  if(rear)
  {
    while(rear->next != NULL)
    {
      temp = rear->next; //temporary variable to store the next node
      delete rear; //bye bye rear
      rear = temp; //rear is reborn...as temp
    }
  }

}


int queue::enqueue(stack & collection, assignment & project) //Adds an assignment
{
  q_node * data = new q_node;
  data->data = project;
  int copied = data->object.copy_stack(collection); //Stack is copied over
  if(!rear) //No data in rear, node is copied into rear
  {
    rear = data;
    rear->next = rear;
  }
  
  else //There is data in rear
  {
    q_node * temp = rear->next; //New node set
    rear->next = data; //Data put in next node
    rear = rear->next; //Iterates to next rear
    rear->next = temp; //Next rear set to temp
  }
  return 1;
}

//Remove the node at the front
int queue::dequeue(void)
{
  if(!rear)
    return 0;
  else if(rear->next == rear)
  {
    if(rear->data.classname){ //This code looks for any data inside the assignment struct
    delete [] rear->data.classname;}
    if(rear->data.assignmentname){
    delete [] rear->data.assignmentname;}
    if(rear->data.duedate){
    delete [] rear->data.duedate;}
    delete rear;
    rear = NULL;
    return 1;
  }
  q_node * temp = rear->next;
  
  rear->next = temp->next;
  if(temp->data.classname){ //This code looks for any data inside the assignment struct
  delete [] temp->data.classname;}
  if(temp->data.assignmentname){
  delete [] temp->data.assignmentname;}
  if(temp->data.duedate){
  delete [] temp->data.duedate;}
  delete temp;
  return 1;

}

int queue::display() //Wrapper function
{
  if(!rear) //rear is empty
    return 0;
  return display(rear->next); //Accesses the private display function as well as head, a private data member
}
int queue::display(q_node * temp) //displays all assignments
{
  
  if(temp == rear) //only one assignment
  {
    cout << "Assignment Data: " << endl; //label to differentiate assignment from books
    cout << temp->data.classname << endl; 
    cout << temp->data.assignmentname << endl; 
    cout << temp->data.duedate << endl;
    cout << "Books used for this assignment: " << endl; //label to differentiate books from assignments
    int show = temp->object.display();
      
    
    return 1; 
  }
  else //if there are multiple assignments
  {
    cout << "Assignment Data: " << endl; //label to differentiate assignments from books
    cout << temp->data.classname << endl; 
    cout << temp->data.assignmentname << endl; 
    cout << temp->data.duedate << endl;
    cout << "Books used for this assignment: " << endl; //label to differentiate books from assignments
    int show = temp->object.display();
    return 1 + display(temp->next); //Moves onto next node recursively
  }
}

int queue::peek() const //Peeks the first assignment
{
  if(!rear)
    return 0;
  q_node * temp = rear->next;
  cout << "Assignment Data: " << endl; //label to differentiate assignments from books
  cout << temp->data.classname << endl; 
  cout << temp->data.assignmentname << endl; 
  cout << temp->data.duedate << endl; 
  cout << "Books used for this assignment: " << endl; //label to differentiate books from assignments
  temp->object.display();
  return 1;
}
