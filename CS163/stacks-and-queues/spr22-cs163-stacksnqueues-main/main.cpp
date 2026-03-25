#include <iostream>
#include <cstring>
using namespace std;
/*This is the client program, which has a function to make a book, and a menu interface to test out the code.  The client does not know an LLL is being used.*/
#include "queue.h"

book MakeABook() //Function that exists to get information on a book to be added to a stack of books
{
  book bookToAdd;
  
  char bookName[50];
  char authorName[50];
  char publisherName[50];
  int whereLeftOff{0};
  
  cout << "Enter the name of a book: ";
  cin.get(bookName, 100, '\n');
  cin.ignore(100, '\n');
  cout << endl;
  
  cout << "Enter the author of the book: ";
  cin.get(authorName, 100, '\n');
  cin.ignore(100, '\n');
  cout << endl;
  
  cout << "Enter the publisher of the book: ";
  cin.get(publisherName, 100, '\n');
  cin.ignore(100, '\n');
  cout << endl;
  
  cout << "Enter the last page you left off on: ";
  cin >> whereLeftOff;
  cin.ignore(100, '\n');
  cout << endl;
  
  char * dynamicBookName = new char[strlen(bookName) + 1]; //Fits a standard char into a dynamically allocated one
  strcpy(dynamicBookName, bookName); //copies it over
  
  char * dynamicAuthorName = new char[strlen(authorName) + 1]; //Fits a standard char into a dynamically allocated one
  strcpy(dynamicAuthorName, authorName); //copies it over
  
  char * dynamicPublisherName = new char[strlen(publisherName) + 1]; //Fits a standard char into a dynamically allocated one
  strcpy(dynamicPublisherName, publisherName); //copies it over
  
  bookToAdd.title = dynamicBookName;
  bookToAdd.author = dynamicAuthorName;
  bookToAdd.publisher = dynamicPublisherName;
  bookToAdd.pageleftoff = whereLeftOff;
  
  
  return bookToAdd;
}


int main()
{
  book elements[2];
  queue assignments;
  stack books;
  assignment data;
  int decider{0};
  cout << "Welcome, please select what you would like to accomplish today:\nCreate a stack of books(1)\nAdd an assignment to a queue of Assignments(4)" << endl
  << "Terminating the program(0): ";
  cin >> decider;
  cin.ignore(100, '\n');
  cout << endl;
  
  
  while(decider != 0) //Large while loop
  {
    if(decider == 1) //Book added to a stack
    {
      int add{0};
      book addition = MakeABook();
      add = books.push(addition); //A book is placed on top of the stack
      
    }
    if(decider == 2) //Displays all books in a stack
    {
      int show = books.display();
    }
    
    if(decider == 3) //Book at the top of the stack popped off
    {
      int show = books.pop();
    }
    
    if(decider == 4)
    {
      stack newbooks; //New stack of books
      char className[50]; //Statically allocated arrays which get dynamically allocated
      char assignmentName[50];
      char dueDate[50];
      
      cout << "Enter the name of the class: ";
      cin.get(className, 100, '\n');
      cin.ignore(100, '\n');
      cout << endl;
      
      cout << "Enter the name of the assignment: ";
      cin.get(assignmentName, 100, '\n');
      cin.ignore(100, '\n');
      cout << endl;
      
      cout << "Enter the due date of the assignment: ";
      cin.get(dueDate, 100, '\n');
      cin.ignore(100, '\n');
      cout << endl;
    
      
      char * dynamicClassName = new char[strlen(className) + 1]; //Fits a standard char into a dynamically allocated one
      strcpy(dynamicClassName, className); //copies it over
      
      char * dynamicAssignmentName = new char[strlen(assignmentName) + 1]; //Fits a standard char into a dynamically allocated one
      strcpy(dynamicAssignmentName, assignmentName); //copies it over
      
      char * dynamicDueDate = new char[strlen(dueDate) + 1]; //Fits a standard char into a dynamically allocated one
      strcpy(dynamicDueDate, dueDate); //copies it over
      
      data.classname = dynamicClassName;
      data.assignmentname = dynamicAssignmentName;
      data.duedate = dynamicDueDate;
      
      cout << "Now, you can't get this done empty handed...let's add some books to max your grade: " << endl; //Prompts user to enter in books
      int add{0};
      int stackdecider{1};
      while(stackdecider)
      {
        int i = 0;
        book addition = MakeABook();
        add = newbooks.push(addition); //A book is placed on top of the stack
        cout << "Again? (1) or no (0): ";
        cin >> stackdecider;
        cin.ignore(100, '\n');
        cout << endl;
      }
      int show = assignments.enqueue(newbooks, data); //Books are queued
    }
    
    if(decider == 5)
    {
      int show = assignments.display(); //The user does not know this is an LLL
    }
    
    if(decider == 6)
    {
      int show = books.peek(); //The book at the top is peeked
    }
    
    if(decider == 7)
    {
      int show = assignments.dequeue(); //The assignment at the front is dequeued
    }
    if(decider == 8)
    {
      int show = assignments.peek(); //The next assignment up is queued in
    }
    
    
    cout << "Select your next action: \nAdding another book to a stack of books(1)\nDisplaying all books in a stack(2)" << endl
    << "Removing a book from the top of the stack(3)\nAdd an assignment to the queue(4)\nDisplay all Assignents(5)\nPeek the book at the top of a book stack(6)" 
    << endl << "Dequeue an Assignment(7)\nPeek the assignment due next(8)\nTerminating the program(0)"; //Prompts for the user
    cin >> decider;
    cin.ignore(100, '\n'); //As I have discovered last time, this is really important
  }
  
  cout << "Thank you for using the program, good day!" << endl << endl << endl; //Program terminated.  This is the only place the code seg faults


  return 0;
}
