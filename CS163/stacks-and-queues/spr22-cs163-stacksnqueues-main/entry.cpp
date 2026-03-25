//Matthew Penner
#include "stack.h"
//This is a file that contains code to copy book data over to a stack as well as display it
int book::copy_entry(const book & copy_from) //Copies data over
{
  //First checks to see if any data exists in the book data is being copied into
  if (author)
   delete [] author; 
  if (title) 
   delete [] title;
  if (publisher) 
   delete [] publisher; 
  if (pageleftoff) 
   pageleftoff = 0; 
     
  title = author = publisher = NULL; 
  pageleftoff = 0;

  if (copy_from.author) //copies an author
  { 
     author = new char[strlen(copy_from.author) +1]; 
     strcpy(author, copy_from.author); 
  } 
  if (copy_from.title) //copies the title
  { 
     title = new char[strlen(copy_from.title)+1]; 
     strcpy(title, copy_from.title); 
  } 
  
  if (copy_from.publisher) //copies the publisher
  { 
     publisher = new char[strlen(copy_from.publisher) +1]; 
     strcpy(publisher, copy_from.publisher); 
  } 
  if (copy_from.pageleftoff) //copies the page left off
  { 
     pageleftoff = copy_from.pageleftoff;
  } 

  return 1;
}

int book::display() //displays a book object
{
  cout << title << endl;
  cout << author << endl;
  cout << publisher << endl;
  cout << pageleftoff << endl;
  
  return 1;

}


