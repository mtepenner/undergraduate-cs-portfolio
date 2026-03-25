#include "program3.h"
/*This is the main file, which has the menu interface along with a while loop that runs through
each possible decision the user can make.  The program is terminated with a 0 entered in*/
using namespace std;
int main()
{
  table animal_organizer;
  animal_organizer.load();
  animal animal_to_add;
  
  int decider;
  
  //Menu interface for client
  cout << "Welcome to the program!  Please select what you would like to accomplish..." 
       << endl
       << "(1) Adding an animal"
       << endl
       << "(2) Removing an animal using a keyword"
       << endl
       << "(3) Display all animals"
       << endl
       << "(4) Displaying all animals that match a specified personality"
       << endl
       << "(5) Retrieving if animals exist based on inputted keywords"
       << endl
       << "(6) Displaying all animals that match specified keywords"
       << endl
       << "(0) Ending the program"
       << endl;
  cin >> decider;
  cin.ignore(100, '\n');
  cout << endl;
  
  while(decider) //While the decider is not set to zero
  {
    if(decider == 1) //Adds an animal into the code
    {      
      //Statically allocated arrays initialized
      char BREED[100];
      char CATEGORY[100];
      char PERSONALITY[100];
      char PURPOSE[100];
      char SIZE[100];
      char KEYWORDS[100];
      int AGE;
      
      cout << "Enter the breed of the animal: ";
      cin.get(BREED, 100, '\n');
      cin.ignore(100, '\n');
    
      
      cout << "Enter the category of the animal: ";
      cin.get(CATEGORY, 100, '\n');
      cin.ignore(100, '\n');
      
      cout << "Enter the personality of the animal: ";
      cin.get(PERSONALITY, 100, '\n');
      cin.ignore(100, '\n');
      
      cout << "Enter the purpose of the animal: ";
      cin.get(PURPOSE, 100, '\n');
      cin.ignore(100, '\n');
      
      cout << "Enter the size of the animal: ";
      cin.get(SIZE, 100, '\n');
      cin.ignore(100, '\n');
      
      cout << "Enter the keywords of the animal: ";
      cin.get(KEYWORDS, 100, '\n');
      cin.ignore(100, '\n');
      
      cout << "Enter the age of the animal: ";
      cin >> AGE;
      cin.ignore(100, '\n');
      
      //Dynamically allocated memory for animal components
      animal_to_add.fill(BREED, CATEGORY, PERSONALITY, PURPOSE, SIZE, KEYWORDS, AGE);

      
      int addition = animal_organizer.add_animal(animal_to_add.breed, animal_to_add);
    }
    if(decider == 2) //Removes animals by keywords
    {
      char keywords[100];
      cout << "Enter in the keywords: ";
      cin.get(keywords, 100, '\n');
      cin.ignore(100, '\n');
      char * dykeywords = new char[strlen(keywords) + 1];
      strcpy(dykeywords, keywords);
      int removal = animal_organizer.remove_by_keywords(dykeywords);
    }
    if(decider == 3) //Displays all of the animals
    {
      cout << "Here are all the animals: ";
      int show = animal_organizer.display_all();
    
      cout << endl << endl;
    }
    if(decider == 4) //Displays all that match a personality 
    {
      char personality[100];
      cout << "Enter in the personality you are looking for: ";
      cin.get(personality, 100, '\n');
      cin.ignore(100, '\n');
      char * dypersonality = new char[strlen(personality) + 1];
      strcpy(dypersonality, personality);
      cout << "Here are the following animals that match the personality you entered in: " << endl;
      int specified = animal_organizer.display_with_personality_type(dypersonality);
    }
    if(decider == 5) //Retrieve animal based on keyword
    {
      animal animal_array[100];
      char keyword[100];
      cout << "Enter in the keyword you are looking for: ";
      cin.get(keyword, 100, '\n');
      cin.ignore(100, '\n');
      char * dykeyword = new char[strlen(keyword) + 1];
      strcpy(dykeyword, keyword);
      
      bool retrieved = animal_organizer.retrieve(dykeyword, animal_array);
      
      if(retrieved == true)
      {
        cout << "Yes, there is an animal(s) that fits this description.";
        int i = 0;
        while(i < sizeof(animal_array) && animal_array[i].breed != NULL)
        {
          animal_array[i].display();
          ++i;
        }
      }
      else
        cout << "Nope, there are none.  Sorry.";
      cout << endl;
    
    }
    
    if(decider == 6) //Display animals by keywords entered in
    {
      char keyword[100];
      cout << "Enter in the keyword you are looking for: ";
      cin.get(keyword, 100, '\n');
      cin.ignore(100, '\n');
      char * dykeyword = new char[strlen(keyword) + 1];
      strcpy(dykeyword, keyword);
      cout << "Here are the following animals that match the keyword you entered in: " << endl;
      int specified = animal_organizer.display_with_keyword_type(dykeyword);
    
    }
    
    cout << "Please select your next action..." //Interface comes back up
         << endl
         << "(1) Adding an animal"
         << endl
         << "(2) Removing an animal using a keyword"
         << endl
         << "(3) Display all animals"
         << endl
         << "(4) Displaying all animals that match a specified personality"
         << endl
         << "(5) Retrieving if animals exist based on inputted keywords"
         << endl
         << "(6) Displaying all animals that match specified keywords"
         << endl
         << "(0) Ending the program"
         << endl;
       
    cin >> decider;
    cin.ignore(100, '\n');
    cout << endl;
  }
  
  
  
  cout << "Thank you, goodbye!" << endl; //End of the code
  

  
  return 0;
}