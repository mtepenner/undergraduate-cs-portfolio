#include "program4.h"
/*


This is the main .cpp where I have the menu interface in which the client can test the functions.  I used a function for the menu interface so that the main function
is not overcomplicated.  The main function consists of a simple while loop that continuously runs the menu_interface program until the user quits.
*/
int menu_interface(table & BST)
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
       << "(1) Adding an animal"
       << endl
       << "(2) Removing an animal"
       << endl
       << "(3) Displaying all animals"
       << endl
       << "(4) Displaying all animals of a certain breed"
       << endl
       << "(5) Displaying all animals of a certain size"
       << endl
       << "(6) Retrieving animals of a certain breed and personality"
       << endl
       << "(7) Quitting the program" << endl;
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
    int addition = BST.add_pet(to_add);
  }
  if(decider == 2)
  {
    cout << "Enter in the breed:  " << endl;
    cin.get(BREED, 100, '\n');
    cin.ignore(100, '\n');
    char * breed = new char[strlen(BREED) +1]; 
    strcpy(breed, BREED);
    
    BST.remove_by_breed(breed);
  }
  if(decider == 3)
  {
    cout << "Here are all the animals:  " << endl;
    BST.display_all();
    
    cout << endl;
  }
  if(decider == 4) //
  {
    cout << "Enter in the breed:  " << endl;
    cin.get(BREED, 100, '\n');
    cin.ignore(100, '\n');
    char * breed = new char[strlen(BREED) +1]; 
    strcpy(breed, BREED);
    
    BST.display_all_breed(breed);
  }
  if(decider == 5) //Display with size
  {
    cout << "Enter in the size:  " << endl;
    cin.get(SIZE, 100, '\n');
    cin.ignore(100, '\n');
    char * size = new char[strlen(SIZE) +1]; 
    strcpy(size, SIZE);
    
    BST.display_with_size(size);
  }
  if(decider == 6) //Retrieval
  {
    
    animal animal_matches[100];
    
    cout << "Enter in the breed:  " << endl;
    cin.get(BREED, 100, '\n');
    cin.ignore(100, '\n');
    char * breed = new char[strlen(BREED) +1]; 
    strcpy(breed, BREED);
    
    cout << "Enter in the personality:  " << endl;
    cin.get(PERSONALITY, 100, '\n');
    cin.ignore(100, '\n');
    char * personality = new char[strlen(PERSONALITY) +1]; 
    strcpy(personality, PERSONALITY);
    
    BST.retrieve(count, breed, personality, animal_matches);
    int i = 0;
    while(i < sizeof(animal_matches) && animal_matches[i].breed != NULL)
    {
      animal_matches[i].display();
      ++i;
    }
  }
  if(decider == 7)
    return 0;
  if(decider > 7 || decider < 1)
    cout << "Invalid Integer. ";
  return 1;
}
int main() //Made it relatively simple this time around
{
  
  cout << "Welcome to the program..." << endl << endl; //Welcome prompt
  
  int testing = 1;
  table binary_table;
  while(testing != 0)
  {
    testing = menu_interface(binary_table);
  }
  
  cout << "Thank you!  Good day!" << endl << endl;

  
  return 0;
}
