/*


This is the main client side file, where code is run, and of course, 
in this file you do not need to know what ADT is being used.  I 
copied the structure from my previous program 4, which used a similar
menu function.
*/

#include "program5.h"

int menu_interface(table & GRAPH)
{
  char BREED[100];
  char CATEGORY[100];
  char PERSONALITY[100];
  char PURPOSE[100];
  char SIZE[100];
  char KEYWORDS[100];
  int age;
  
  int decider;
  cout << "Please select what you would like to accomplish: " //This is the menu of options
       << endl
       << "(1) Inserting a new vertex into the graph"
       << endl
       << "(2) Displaying the adjacency list"
       << endl
       << "(3) Inserting a connection between two vertices"
       << endl
       << "(4) Quitting the program" << endl;
  cin >> decider;
  cin.ignore(100, '\n');
  int count{0};
  if(decider == 1)
  {
    animal to_add;
    cout << "Enter the breed of the animal: " << endl;
    cin.get(BREED, 100, '\n');
    cin.ignore(100, '\n');
    
    cout << "Enter the category of the animal: " << endl;
    cin.get(CATEGORY, 100, '\n');
    cin.ignore(100, '\n');
    
    cout << "Enter the personality of the animal: " << endl;
    cin.get(PERSONALITY, 100, '\n');
    cin.ignore(100, '\n');
    
    cout << "Enter the purpose of the animal: " << endl;
    cin.get(PURPOSE, 100, '\n');
    cin.ignore(100, '\n');
    
    cout << "Enter the size of the animal: " << endl;
    cin.get(SIZE, 100, '\n');
    cin.ignore(100, '\n');
    
    cout << "Enter any keywords of the animal: " << endl;
    cin.get(KEYWORDS, 100, '\n');
    cin.ignore(100, '\n');
    
    cout << "Enter the age of the animal: " << endl;
    cin >> age;
    cin.ignore(100, '\n');
    
    to_add.fill(BREED, CATEGORY, PERSONALITY, PURPOSE, SIZE, KEYWORDS, age);
    GRAPH.insert_vertex(to_add);
  }
  
  if(decider == 2)
  {
    
    cout << "Here are all the animals:  " << endl;
    GRAPH.display_adjacent();
    
    cout << endl;
  }
  
  if(decider == 3) //Display with size
  {
    char KEYWORD1[100];
    char KEYWORD2[100];
    cout << "Enter in the first breed:  " << endl;
    cin.get(KEYWORD1, 100, '\n');
    cin.ignore(100, '\n');
    char * keyword1 = new char[strlen(KEYWORD1) +1]; 
    strcpy(keyword1, KEYWORD1);
    
    cout << "Now enter in the second breed:  " << endl;
    cin.get(KEYWORD2, 100, '\n');
    cin.ignore(100, '\n');
    char * keyword2 = new char[strlen(KEYWORD2) +1]; 
    strcpy(keyword2, KEYWORD2);
    
    GRAPH.insert_edge(keyword1, keyword2);
  }
  if(decider == 4)
    return 0;
  
  if(decider > 4 || decider < 1)
    cout << "Invalid Integer. ";
  return 1;
}
int main() //Made it relatively simple
{
  
  cout << "Welcome to the program..." << endl << endl; //Welcome prompt
  
  int testing = 1; //Parameter for the following while loop
  table graph;
  while(testing != 0)
  {
    testing = menu_interface(graph);
  }
  
  cout << "Thank you!  Good day!" << endl << endl;

  
  return 0;
}
