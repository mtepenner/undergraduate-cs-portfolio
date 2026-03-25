//Matthew Penner
//Professor Fant
//CS163 Data Structures
/*This will be the client program that will have a menu interface.  The user can add, delete, and 
display as many times as they so choose.  There will be 7 options to choose from, as explained below.
*/
#include "list.h"
#include <iostream>
using namespace std;

int main()
{ 
  int function{0};
  char parkname[100];

  char NAME[25];
  char INFO[100];
  int rate;
  
  list dogparks; //The dog park list
  
  int selection; //The user input
  cout << "Welcome to the testing platform for a dog park ADT, please select what you want to do today..." << endl
       << "(1) Add a dog park, (2) Add an amenity to a given dog park, (3) Remove a dog park, (4) Display all amenities" << endl
       << "(5) Display all dog parks, (6) Display all parks that have an amenity you are looking for, or (0) to terminate program: " << endl;
  cin >> selection;
  cin.ignore(100, '\n');
  cout << endl;
  while(selection)
  {
    if(selection == 1)
    {
      cout << "Enter the name for the dog park you are adding: " << endl;
      cin.get(parkname, 100, '\n');
      cin.ignore(100, '\n');
      cout << endl;
      
      function = dogparks.add(parkname); //Add a park to the linear linked list
      
      cout << "Please select your next action..." << endl
       << "(1) Add another dog park, (2) Add an amenity to a given dog park, (3) Remove a dog park, (4) Display all amenities" << endl
       << "(5) Display all dog parks, (6) Display all parks that have an amenity you are looking for, or (0) to terminate program: " << endl;
      cin >> selection;
      cin.ignore(100, '\n');
      cout << endl;
    }
    else if(selection == 2)
    {
      cout << "Enter the name for the dog park you want to add an amenity to: " << endl;
      cin.get(parkname, 100, '\n');
      cin.ignore(100, '\n');
      cout << endl;
      
      cout << "Enter the name of the amenity: " << endl;
      cin.get(NAME, 25, '\n');
      cin.ignore(100, '\n');
      cout << endl;
      
      cout << "Enter a description of it: " << endl;
      cin.get(INFO, 100, '\n');
      cin.ignore(100, '\n');
      cout << endl;
      
      cout << "Enter the rating of this amenity: " << endl;
      cin >> rate;
      cout << endl;
      
      
      function = dogparks.add_amenity(parkname, NAME, INFO, rate);    
      
      cout << "Please select your next action..." << endl
       << "(1) Add another dog park, (2) Add an amenity to a given dog park, (3) Remove a dog park, (4) Display all amenities" << endl
       << "(5) Display all dog parks, (6) Display all parks that have an amenity you are looking for, or (0) to terminate program: " << endl;
      cin >> selection;
      cin.ignore(100, '\n');
      cout << endl;
    }
    else if(selection == 3)
    {
      cout << "Enter the name for the dog park you want to remove: " << endl;
      cin.get(parkname, 100, '\n');
      cin.ignore(100, '\n');
      cout << endl;
      
      function = dogparks.remove(parkname);   
      
      cout << "Please select your next action..." << endl
       << "(1) Add another dog park, (2) Add an amenity to a given dog park, (3) Remove a dog park, (4) Display all amenities" << endl
       << "(5) Display all dog parks, (6) Display all parks that have an amenity you are looking for, or (0) to terminate program: " << endl;
      cin >> selection;
      cin.ignore(100, '\n');
      cout << endl;
      
    }
    else if(selection == 4)
    {
      cout << "Enter the name for the dog park you want to see the amenities for: " << endl;
      cin.get(parkname, 100, '\n');
      cin.ignore(100, '\n');
      cout << endl;
      
      function = dogparks.display_all_amenities(parkname);
      
      cout << "Please select your next action..." << endl
       << "(1) Add another dog park, (2) Add an amenity to a given dog park, (3) Remove a dog park, (4) Display all amenities" << endl
       << "(5) Display all dog parks, (6) Display all parks that have an amenity you are looking for, or (0) to terminate program: " << endl;
      cin >> selection;
      cin.ignore(100, '\n');
      cout << endl;
    }
    else if(selection == 5)
    {
      cout << "Here are all of the parks by name: " << endl;
      function = dogparks.display_all();
      
      cout << "Please select your next action..." << endl
       << "(1) Add another dog park, (2) Add an amenity to a given dog park, (3) Remove a dog park, (4) Display all amenities" << endl
       << "(5) Display all dog parks, (6) Display all parks that have an amenity you are looking for, or (0) to terminate program: " << endl;
      cin >> selection;
      cin.ignore(100, '\n');
      cout << endl;
    }
    else if(selection == 6)
    {
      cout << "Enter the name of the amenity you are looking for: " << endl;
      cin.get(NAME, 25, '\n');
      cin.ignore(100, '\n');
      cout << endl;
      
      function = dogparks.display_with_amenity(NAME);
      
      cout << "Please select your next action..." << endl
       << "(1) Add another dog park, (2) Add an amenity to a given dog park, (3) Remove a dog park, (4) Display all amenities" << endl
       << "(5) Display all dog parks, (6) Display all parks that have an amenity you are looking for, or (0) to terminate program: " << endl;
      cin >> selection;
      cin.ignore(100, '\n');
      cout << endl;
    
    }
    
    else
    {
      cout << "Invalid" << endl;
      selection = 0;
    }
  }
    
    
    
  
  
  cout << "Have a nice day!" << endl;

  return 0;
}
