//Matthew Penner
//My main cpp file
//main.cpp
#ifndef MAIN_CPP
#define MAIN_CPP
#include "animal.h"
#include "twoThreeTree.h"

/*
My main function is super simple.  It initializes a 2-3 tree and calls my recursive menu function.
This is very similar to how I had program 1 except creation of the animal objects is done here instead 
of separate functions.  A 2-3 tree is passed into my display function from main so that data inserted 
is saved, and will proceed to loop until the user decides to exit.  This was a great opportunity to use
exception handling.
*/
int displayMenu(twoThreeTree & petTree)
{
  
  int selection;
  cout << "Please select from the following options: \n"
  << "(0)Quit\n"
  << "(1)Add a pet\n" 
  << "(2)Remove all pets\n"
  << "(3)Display all pets\n";
  
  cin >> selection;
  cin.ignore(100, '\n');
  
  if(selection == 1) 
  {
    int choice;
    try {
      cout << "What kind of pet do you want to add?\n"
      << "(1) A cat\n(2) A dog\n(3) A bunny\n";
      cin >> choice;
      cin.ignore(100, '\n');
      if(!choice)
      {
        throw(exception());      
      }
    }
    catch (const exception &e) {
        cout << "Exception has been caught: " << e.what() << '\n';
        return 0;      
    }
    if(choice == 1) 
    {
      string name;
      int temperament;
      int care;
      int adjustmentTime;
      int aFriendly;
      bool friendly;
      cout << "Enter the name of your cat: ";
      cin >> name;
      cin.ignore(100, '\n');
      try {
        cout << "Enter the temperament of your cat: ";
        cin >> temperament;
        cin.ignore(100, '\n');
        if(!temperament)
        {
          throw(exception());
        }
        cout << "Enter the level of care your cat requires: ";
        cin >> care;
        cin.ignore(100, '\n');
        if(!care)
        {
          throw(exception());
        }
        cout << "Does your cat get along with other animals? (1) if yes or (2) if no: ";
        cin >> aFriendly;
        cin.ignore(100, '\n');
        if(!aFriendly)
        {
          throw(exception());
        }
        cout << "Enter the time it takes your cat to adjust to a new environment (months): ";
        cin >> adjustmentTime;
        cin.ignore(100, '\n');
        if(!adjustmentTime)
        {
          throw(exception());
        }
        if(aFriendly == 1) { friendly = true; }
        else { friendly = false; }
      }
      
      catch (const exception &e) {
        cout << "Exception has been caught: " << e.what() << '\n';
        return 0;      
      }
      try {
        unique_ptr<pet> addCat = make_unique<cat>(name, care, temperament, friendly, adjustmentTime);
        if(!addCat)
        {
          throw(exception());
        }
        int catnipSet;
        cout << "Is your cat an addict (1) if yes or (2) if no: ";
        cin >> catnipSet;
        cin.ignore(100, '\n');
        if(!catnipSet)
        {
          throw(exception());
        }
        if(catnipSet == 1)
        {
          dynamic_cast<cat*>(addCat.get())->isAnAddict(); 
        }
        dynamic_cast<pet*>(addCat.get())->addHistory();
        petTree.insert(addCat);
      }
      catch (const exception &e) {
        cout << "Exception has been caught: " << e.what() << '\n';
        return 0;      
      }
      
      
    }
    if(choice == 2) 
    {
      string name;
      int temperament;
      int care;
      int aFriendly;
      bool friendly;
      string favoriteToy;
      
      cout << "Enter the name of your dog: ";
      cin >> name;
      cin.ignore(100, '\n');
      try {
        cout << "Enter the temperament of your dog: ";
        cin >> temperament;
        cin.ignore(100, '\n');
        if(!temperament)
        {
          throw(exception());
        }
        cout << "Enter the level of care your dog requires: ";
        cin >> care;
        cin.ignore(100, '\n');
        if(!care)
        {
          throw(exception());
        }
        cout << "Does your dog get along with other animals? (1) if yes or (2) if no: ";
        cin >> aFriendly;
        cin.ignore(100, '\n');
        if(!aFriendly)
        {
          throw(exception());
        }
        cout << "Enter your dog's favorite toy: ";
        cin >> favoriteToy;
        cin.ignore(100, '\n');
        if(aFriendly == 1) { friendly = true; }
        else { friendly = false; }
      }
      catch (const exception &e) {
        cout << "Exception has been caught: " << e.what() << '\n';
        return 0;      
      }
      unique_ptr<pet> addDog = make_unique<dog>(name, care, temperament, friendly, favoriteToy);
      int chipped;
      cout << "Would you like to chip your dog? (1) if yes or (2) if no: ";
      cin >> chipped;
      cin.ignore(100, '\n');
      if(!chipped)
      {
        throw(exception());
      }
      if(chipped == 1)
      {
        dynamic_cast<dog*>(addDog.get())->installMicrochip(); 
      }  
      int license;
      cout << "Does your dog have a license? (1) if yes or (2) if no: ";
      cin >> license;
      cin.ignore(100, '\n');
      if(!license)
      {
        throw(exception());
      }
      if(license == 1)
      {
        dynamic_cast<dog*>(addDog.get())->obtainLicense(); 
      }     
      dynamic_cast<pet*>(addDog.get())->addHistory();
      petTree.insert(addDog);
    }
    if(choice == 3) 
    {
      string name;
      int temperament;
      int care;
      int aFriendly;
      bool friendly;
      int isSharp;
      bool teethSharp;
      string favoriteCarrot;
      
      cout << "Enter the name of your bunny: ";
      cin >> name;
      cin.ignore(100, '\n');
      try {
        cout << "Enter the temperament of your bunny: ";
        cin >> temperament;
        cin.ignore(100, '\n');
        if(!temperament)
        {
          throw(exception());
        }
        cout << "Enter the level of care your bunny requires: ";
        cin >> care;
        cin.ignore(100, '\n');
        if(!care)
        {
          throw(exception());
        }
        cout << "Does your bunny get along with other animals? (1) if yes or (2) if no: ";
        cin >> aFriendly;
        cin.ignore(100, '\n');
        if(!aFriendly)
        {
          throw(exception());
        }
        cout << "Does your bunny have sharp teeth? (1) if yes or (2) if no: ";
        cin >> isSharp;
        cin.ignore(100, '\n');
        if(!isSharp)
        {
          throw(exception());
        }
        cout << "Enter your bunny's favorite carrot brand: ";
        cin >> favoriteCarrot;
        cin.ignore(100, '\n');
      }
      
      catch (const exception &e) {
        cout << "Exception has been caught: " << e.what() << '\n';
        return 0;      
      }
      if(aFriendly == 1) { friendly = true; }
      else { friendly = false; }
      
      if(isSharp == 1) { teethSharp = true; }
      else { teethSharp = false; }
      
      unique_ptr<pet> addBunny = make_unique<bunny>(name, care, temperament, friendly, teethSharp, favoriteCarrot);
      dynamic_cast<pet*>(addBunny.get())->addHistory();
      try {
        int yesOrNo;
        cout << "Does your bunny like the outdoors? (1) if yes or (2) if no: ";
        cin >> yesOrNo;
        cin.ignore(100, '\n');
        if(yesOrNo != 1 && yesOrNo != 2)
        {
          throw(exception());
        }
        else
        {
          dynamic_cast<bunny*>(addBunny.get())->isOutdoor();
        }
      }
      
      catch (const exception &e) {
        cout << "Exception has been caught: " << e.what() << '\n';
        return 0; 
      }
      
      
      petTree.insert(addBunny);
    }
  
  }
  if(selection == 2)
  {
    petTree.removeAll();
  }
  if(selection == 3)
  {
    petTree.displayAll();
  }
  
  if(selection != 0)
  {
    displayMenu(petTree);
  }
  

  return 0;
}

int main()
{
  twoThreeTree petTree;
  cout << "--------WELCOME TO THE PET CENTER--------\n";
  displayMenu(petTree);
  cout << "HAVE A NICE DAY!\n";
  return 0;
}
#endif