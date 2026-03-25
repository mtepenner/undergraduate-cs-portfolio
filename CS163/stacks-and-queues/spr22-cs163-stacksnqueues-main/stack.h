/*


This file will initialize the stack class.  All member functions
will be initialized in the respective classes along with any private data members.  The goal is
to implement the two data types in order to store data inputted by the client in the client interface, and
make a list that follows the ADT correctly.



*/
#include <iostream>
#include <cstring>
using namespace std;

struct book;
struct s_node;
struct q_node;

class stack
{
  public:
    stack(); //Constructor
    ~stack(); //Destructor
    int push(book & data); //Push a book to the top
    int pop(); //Pop the most recent book from the top
    int display(); //Displays all books on the stack
    int peek(); //Peek the book at the top of the stack
    int copy_stack(const stack & data); //Copies a stack over
  private:
    s_node * head; //A head pointer to the top
    int display(s_node * & head);
  

};

class book
{
  public:
    int copy_entry(const book & copy_from); //copies a book
    int display();
    
  public:
    char * author; //Name of the author
    char * title; //Title of the book
    char * publisher; //Book publisher
    int pageleftoff; //Page reader left off on
};

struct s_node //This is the node for a book element
{
  book * object;
  s_node * next; //A next pointer
  int top_index;

};

