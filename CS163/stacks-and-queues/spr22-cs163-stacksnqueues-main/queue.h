/*


This file will initialize the queue class.  All member functions
will be initialized in the respective classes along with any private data members.  The goal is
to implement the two data types in order to store data inputted by the client in the client interface, and
make a list that follows the ADT correctly.


*/
#include "stack.h"
struct assignment //holds assignment data
{
  //int copy_entry(assignment & data)
  char * classname; //The class for the assignment
  char * assignmentname; //The name of the assignment
  char * duedate; //The due date of the assignment
};

struct q_node //This is the node for an assignment 
{
  assignment data; //an assignment
  stack object; //A stack object
  q_node * next; //A next pointer
  

};


class queue 
{
  public:
    queue(); //Constructor
    ~queue(); //Destructor
    int enqueue(stack & collection, assignment & project); //Enqueue an assignment to the rear
    int dequeue(void); //Dequeue an assignment from the front
    int peek() const; //Peek from the queue
    int display(); //Wrapper function
  private:
    q_node * rear;
    int display(q_node * temp);
  
  
};

