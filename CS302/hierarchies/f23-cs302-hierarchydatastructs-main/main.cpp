 /*Matthew Penner
 *10/23/2023
 *CS302
 *
 *
 *
 *
 * */

#include <iostream>
#include "celebrities.h"
#include "data_structures.h"
/*
User/tester is prompted with a menu that allows them to see what options are available.  I tried to 
make it as friendly as possible.  I made functions that allows the user to build celebrities. 
Every function I created that requires traversal is done recursively.  The menu function goes in a loop
recursively until the user is done with the program.  

*/
using namespace std;


Actor MakeAnActor() //pretty self explanatory, basically a function that builds and puts together an actor object, same thing will exist for artists and cosplayers
{ 

  	char * name = new char[100];
 	//Actor data members
	int award_count;
	int autograph_cost;
	bool selfie_allowed;
	int a_wealth;
	int a_age;
	string a_comic;
 	cout << "Enter the name of the Celebrity you are interested in: " << endl;
  	//found a bug right here
	cin.get(name, 100, '\n');
	cin.ignore(100, '\n');
	cout << endl;
	
	cout << "Enter the age of the Celebrity: ";
	cin >> a_age;
	cin.ignore(100, '\n');
	cout << endl;

	cout << "Enter the celebrity's wealth: ";
	cin >> a_wealth;
	cin.ignore(100, '\n');
	cout << endl;

	cout << "Enter what Comic Book Company this Celebrity is a part of: ";
	getline(cin, a_comic);
	cout << endl;

	int early;
	int late;
	cout << "Enter the earliest availability of this Actor: ";
	cin >> early;
	cin.ignore(100, '\n');
  	cout << endl;

	cout << "Enter the latest availability of this Actor: ";
	cin >> late;
	cin.ignore(100, '\n');
  	cout << endl;

	cout << "Enter the number of awards this actor has achieved: ";
	cin >> award_count;
	cin.ignore(100, '\n');
	cout << endl;

	cout << "Enter the price to have an autograph from this actor: ";
	cin >> autograph_cost;
	cin.ignore(100, '\n');
	cout << endl;

	int yayornay;
	cout << "Does this actor allow selfies?\nPress (1) and hit enter if yes or any other number if no: ";
	cin >> yayornay;
	cin.ignore(100, '\n');
	cout << endl;
	
		
	if(yayornay == 1)
		selfie_allowed = true;
	else
		selfie_allowed = false;

  	//cout << "hit" << endl;
	Actor new_actor (name, a_age, a_wealth, a_comic, early, late, award_count, autograph_cost, selfie_allowed);
  	//cout << "hit" << endl;
	return new_actor;

}

Artist MakeAnArtist() //pretty self explanatory, basically a function that builds and puts together an artist object, same thing will exist for actors and cosplayers
{
  char * name = new char[100];


	int a_wealth;
	int a_age;
	string a_comic;
 
  	char * art_drawing_types = new char[100];
  	int art_years;
 	bool art_is_sig;
 	string art_the_characters_drawn;
  
 	cout << "Enter the name of the Celebrity you are interested in: " << endl;
  
	cin.get(name, 100, '\n');
	cin.ignore(100, '\n');
	cout << endl;
	
	cout << "Enter the age of the Celebrity: ";
	cin >> a_age;
	cin.ignore(100, '\n');
	cout << endl;

	cout << "Enter the celebrity's wealth: ";
	cin >> a_wealth;
	cin.ignore(100, '\n');
	cout << endl;

	cout << "Enter what Comic Book Company this Celebrity is a part of: ";
	getline(cin, a_comic);
	cout << endl;

	int early;
	int late;
	cout << "Enter the earliest availability of this Artist: ";
	cin >> early;
	cin.ignore(100, '\n');
  	cout << endl;

	cout << "Enter the latest availability of this Artist: ";
	cin >> late;
	cin.ignore(100, '\n');
  	cout << endl;
  
 	cout << "Input some of the characters drawn: " << endl;
 	cin.get(art_drawing_types, 100, '\n');
	cin.ignore(100, '\n');
	cout << endl;
 
  	cout << "Enter the years this artist has been drawing: ";
	cin >> art_years;
	cin.ignore(100, '\n');
	cout << endl;
  
  	int yayornay;
  	cout << "Does this artist include signatures?\nPress (1) and hit enter if yes or any other number if no: ";
	cin >> yayornay;
	cin.ignore(100, '\n');
	cout << endl;
	
	
	if(yayornay == 1)
		art_is_sig = true;
	else
		art_is_sig = false;
   
	
	cout << "Make a list separated by commas of what characters this artist has drawn: ";
	getline(cin, art_the_characters_drawn);
	cout << endl;


	Artist new_art (name, a_age, a_wealth, a_comic, early, late, art_drawing_types, art_years, art_is_sig, art_the_characters_drawn);

	return new_art;

}


Cosplayer MakeACosplayer() //pretty self explanatory, basically a function that builds and puts together an artist object, same thing will exist for actors and cosplayers
{
  	char * name = new char[100];


	int a_wealth;
	int a_age;
	string a_comic;
  	string character;
  	string favorite_outfit;
  	int experience;


  
 	cout << "Enter the name of the Celebrity you are interested in: " << endl;
  
	cin.get(name, 100, '\n');
	cin.ignore(100, '\n');
	cout << endl;
	
	cout << "Enter the age of the Celebrity: ";
	cin >> a_age;
	cin.ignore(100, '\n');
	cout << endl;

	cout << "Enter the celebrity's wealth: ";
	cin >> a_wealth;
	cin.ignore(100, '\n');
	cout << endl;

	cout << "Enter what Comic Book Company this Celebrity is a part of: ";
	getline(cin, a_comic);
	cout << endl;

	int early;
	int late;
	cout << "Enter the earliest availability of this Artist: ";
	cin >> early;
	cin.ignore(100, '\n');
	cout << endl;

	cout << "Enter the latest availability of this Artist: ";
	cin >> late;
	cin.ignore(100, '\n');
  	cout << endl;
  
  	cout << "Give a description of the character present at Comic Con: ";
	getline(cin, character);
	cout << endl;

  	cout << "What is this person's favorite outfit: ";
	getline(cin, favorite_outfit);
	cout << endl;
 
  	cout << "Enter the years of experience this cosplayer has had dressing up: ";
	cin >> experience;
	cout << endl;

	Cosplayer new_cos (name, a_age, a_wealth, a_comic, early, late, character, favorite_outfit, experience);
	return new_cos;

}

int display_vector_elements(long unsigned int i, vector <Cosplayer> & List)
{
  if(i == List.size()) return 0;
  cout << "-----------------------------------------------" << endl;
  List[i].display();
  cout << "-----------------------------------------------" << endl;
  ++i;
  return display_vector_elements(i, List);


}

int show_description(long unsigned int i, vector <Cosplayer> & List, char *& name)
{
  if(i == List.size()) return 0;
  if (List[i].compare_name(name) == true)
  {
    cout << "-----------------------------------------------" << endl;
    List[i].show_character_description();
    cout << "-----------------------------------------------" << endl;
    return 1;
  }
  ++i;
  return show_description(i, List, name);

}

int show_favorite_dressup(long unsigned int i, vector <Cosplayer> & List, char *& name)
{
  if(i == List.size()) return 0;
  if (List[i].compare_name(name) == true)
  {
    cout << "-----------------------------------------------" << endl;
    List[i].display_favorite_outfit();
    cout << "-----------------------------------------------" << endl;
    return 1;
  }
  ++i;
  return show_favorite_dressup(i, List, name);

}

int show_experience(long unsigned int i, vector <Cosplayer> & List, char *& name)
{
  if(i == List.size()) return 0;
  if (List[i].compare_name(name) == true)
  {
    cout << "-----------------------------------------------" << endl;
    List[i].show_past_experience();
    cout << "-----------------------------------------------" << endl;
    return 1;
  }
  ++i;
  return show_experience(i, List, name);

}

int remove_cosplayer(long unsigned int i, vector <Cosplayer> & List, char *& name)
{
  if(i == List.size()) return 0;
  if (List[i].compare_name(name) == true)
  {

    List.erase(List.begin()+i);

    return 1;
  }
  ++i;
  return show_description(i, List, name);

}

int stunt(long unsigned int i, vector <Cosplayer> & List, char *& name, int a_time, int & age)
{
  if(i == List.size()) return 0;
  if (List[i].compare_name(name) == true)
  {

    List[i].schedule_stunt(a_time, age);

    return 1;
  }
  ++i;
  return stunt(i, List, name, a_time, age);

}


int Menu(CLL & ActorList, ARR & ArtistList, vector <Cosplayer> & CosplayerList)
{
    int selection;
    
    
    //CLL ActorList; //Pretty much done.  Will note there currently still are some memory leaks
  	//ARR ArtistList (3); //Not quite done
  	//vector <Cosplayer> CosplayerList; //Should be easy enough to implement
    cout << endl << endl << endl;
    cout << "Press (0) and hit enter if: you would like to exit :(" << endl << endl;
   
    cout << "Press (1) and hit enter if: you would like to (for testing purposes) add an Actor to the list of attendees" << endl;	
    cout << "Press (2) and hit enter if: you want to see what actors are present at Comic-Con" << endl; 
    cout << "Press (3) and hit enter if: you would like to (for testing purposes) remove all Actors present at Comic-Con" << endl;
    cout << "Press (4) and hit enter if: you would like to find a specific Actor by name" << endl; 
    cout << "Press (5) and hit enter if: you would like to (for testing purposes) delete a specific Actor by name" << endl;  
    cout << "Press (6) and hit enter if: you would like to schedule an autograph with an Actor" << endl; 
    cout << "Press (7) and hit enter if: you would like to find out if an actor is acclaimed" << endl;  
    cout << "Press (8) and hit enter if: you would like to find out if an actor allows selfies" << endl; 
    cout << endl << endl;
    cout << "Press (9) and hit enter if: you would like to (for testing purposes) add an Artist to the list of attendees" << endl;
    cout << "Press (10) and hit enter if: you would like to see what artists are present at Comic-Con" << endl;
    cout << "Press (11) and hit enter if: you would like to (for testing purposes) remove all Artists from the list of attendees" << endl;
    cout << "Press (12) and hit enter if: you would like to (for testing purposes) remove an Artist from the list of attendees" << endl;
    cout << "Press (13) and hit enter if: you would like to find a specific artist" << endl;

    cout << endl << endl;
    cout << "Press (20) and hit enter if: you would like to (for testing purposes) add a Cosplayer to the list of attendees" << endl;
    cout << "Press (21) and hit enter if: you would like to see what Cosplayers are present at Comic-Con" << endl;
    cout << "Press (22) and hit enter if: you would like to see a description of a certain cosplayer's character" << endl;
    cout << "Press (23) and hit enter if: you would like to see what a cosplayer's favorite thing to dress up all time is" << endl;
    cout << "Press (24) and hit enter if: you would like to see how long a Cosplayer has been in the industry" << endl;
    cout << "Press (25) and hit enter if: you would like to (for testing purposes) remove a specific cosplayer" << endl;
    cout << "Press (26) and hit enter if: you would like to remove all cosplayers" << endl;
    cout << "Press (27) and hit enter if: you would like to schedule a stunt with a Cosplayer" << endl;
    
    
    cin >> selection;
    cin.ignore(100, '\n');
    if(selection == 1)
    {
      cout << "---------------------------------------------------" << endl;
      cout << "|                 WELCOME TO THE                  |" << endl;
      cout << "|              PORTAL FOR ASSISTANCE              |" << endl;
      cout << "|               AND INFO FOR ACTORS               |" << endl;
      cout << "---------------------------------------------------" << endl;
      
    	Actor new_act = MakeAnActor();
      cout << "hit" << endl;
    	ActorList.insert(new_act);
    }
    if (selection == 2)
    {
      
	    ActorList.display();

    }
    if (selection == 3)
    {
    
      
    	ActorList.remove_all();
    	cout << "The Actor List has been successfully purged" << endl;
    }
    
    if (selection == 4)
    {

    	char * r_name = new char[100];
    	cout << "Enter the name of the Actor you are interested in: " << endl;
    
    	cin.get(r_name, 100, '\n');
    	cin.ignore(100, '\n');
    	cout << endl;
    	
    	ActorList.retrieve(r_name);

    }  
    
    if (selection == 5)
    {

    	char * r_name = new char[100];
    	cout << "Enter the name of the Actor you want to remove: " << endl;
    
    	cin.get(r_name, 100, '\n');
    	cin.ignore(100, '\n');
    	cout << endl;
    
    	ActorList.remove(r_name);
    }

    if (selection == 6)
    {

    	char * r_name = new char[100];
    	int atime;
    	cout << "Enter the name of the Actor you are interested in: " << endl;
    
    	cin.get(r_name, 100, '\n');
    	cin.ignore(100, '\n');
    	cout << endl;
    	
    	cout << "Enter the time you wish to interact with this Celebrity: " << endl;
    	cin >> atime;
    	cin.ignore(100, '\n');
    	ActorList.retrieve_autocost(r_name, atime);

    }
    
    if (selection == 7)
    {

    	char * r_name = new char[100];
    	
    	cout << "Enter the name of the Actor you are interested in: " << endl;
    
    	cin.get(r_name, 100, '\n');
    	cin.ignore(100, '\n');
    	cout << endl;
    	
    	ActorList.retrieve_acclaimed(r_name);


	
    }

    if (selection == 8)
    {

    	char * r_name = new char[100];
    	
    	cout << "Enter the name of the Actor you are interested in: " << endl;
    
    	cin.get(r_name, 100, '\n');
    	cin.ignore(100, '\n');
    	cout << endl;
    	
    	ActorList.retrieve_slf(r_name);


    }
    if(selection == 9)
    {

      
    	Artist new_art = MakeAnArtist();
    	ArtistList.insert(new_art);
    }
    if(selection == 10)
    {

    	ArtistList.display();
    }

    if(selection == 11)
    {
	ArtistList.remove_all();

    }

    if(selection == 12)
    {
	char * art_name = new char[100];
    	
    	cout << "Enter the name of the Artist you are interested in: " << endl;
    
    	cin.get(art_name, 100, '\n');
    	cin.ignore(100, '\n');
    	cout << endl;
    	
    	ArtistList.remove(art_name);


 
    }
    if (selection == 13)
    {

    	char * art_name = new char[100];
    	
    	cout << "Enter the name of the Artist you are interested in: " << endl;
    
    	cin.get(art_name, 100, '\n');
    	cin.ignore(100, '\n');
    	cout << endl;
    	
    	ArtistList.retrieve(art_name);


	
    }


    if(selection == 20)
    {

      
    	Cosplayer new_cos = MakeACosplayer();
    	CosplayerList.push_back(new_cos);
    }
    
    if(selection == 21)
    {
      
    	long unsigned int i = 0;
      display_vector_elements(i, CosplayerList);
      
    }
    
    if(selection == 22)
    {
      char * c_name = new char[100];
    	cout << "Enter the name of the Cosplayer you are interested in: " << endl;
    
    	cin.get(c_name, 100, '\n');
    	cin.ignore(100, '\n');
    	cout << endl;
      
    	long unsigned int i = 0;
      show_description(i, CosplayerList, c_name);
      
    }
    
    if(selection == 23)
    {
      char * c_name = new char[100];
    	cout << "Enter the name of the Cosplayer you are interested in: " << endl;
    
    	cin.get(c_name, 100, '\n');
    	cin.ignore(100, '\n');
    	cout << endl;
      
    	long unsigned int i = 0;
      show_favorite_dressup(i, CosplayerList, c_name);
      
    }
    
    if(selection == 24)
    {
      char * c_name = new char[100];
    	cout << "Enter the name of the Cosplayer you are interested in: " << endl;
    
    	cin.get(c_name, 100, '\n');
    	cin.ignore(100, '\n');
    	cout << endl;
      
    	long unsigned int i = 0;
      show_experience(i, CosplayerList, c_name);
      
    }
    
    if(selection == 25)
    {
      char * c_name = new char[100];
    	cout << "Enter the name of the Cosplayer you are interested in deleting: " << endl;
    
    	cin.get(c_name, 100, '\n');
    	cin.ignore(100, '\n');
    	cout << endl;
      
    	long unsigned int i = 0;
      remove_cosplayer(i, CosplayerList, c_name);
      
    }
    
    if(selection == 26)
    {
      CosplayerList.clear();
      
    }
    if(selection == 27)
    {
      int age;
      int a_time;
      char * c_name = new char[100];
    	cout << "Enter the name of the Cosplayer you are interested in: " << endl;
    
    	cin.get(c_name, 100, '\n');
    	cin.ignore(100, '\n');
    	cout << endl;
      cout << "Enter the time you want this to take place: " << endl;
      cin >> a_time;
      cin.ignore(100, '\n');
      
      
      cout << "Enter your age: " << endl;
      cin >> age;
      cin.ignore(100, '\n');
      
    	long unsigned int i = 0;
      stunt(i, CosplayerList, c_name, a_time, age);
      
    }
    if(selection == 0) 
    {

      return 0;
    }
    return Menu(ActorList, ArtistList, CosplayerList);
}

int main()
{

	

  cout << "---------------------------------------------------" << endl;
  cout << "|           WELCOME TO THE (UNOFFICIAL)           |" << endl;
  cout << "|                    COMIC-CON                    |" << endl;
  cout << "|                BOOKING ASSISTANT                |" << endl;
  cout << "|                                                 |" << endl;
  cout << "|    Please select from the following options:    |" << endl;
  cout << "---------------------------------------------------" << endl;

  CLL ActorList; //Pretty much done.  Will note there currently still are some memory leaks
  ARR ArtistList (3); //Not quite done
  vector <Cosplayer> CosplayerList;
  Menu(ActorList, ArtistList, CosplayerList);

  
  cout << "\n\n" << endl;
  cout << "---------------------------------------------------" << endl;
  cout << "|                     GOODBYE                     |" << endl;
  cout << "---------------------------------------------------" << endl;
  
  return 0;
}
