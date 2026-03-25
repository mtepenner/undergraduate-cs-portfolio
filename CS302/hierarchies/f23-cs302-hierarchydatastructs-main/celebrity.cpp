
#include "celebrities.h"
/*
I am using an array of LLLs for the artists, a CLL for the actors, and a vector for cosplayers.
Each data structure is separate from the other and separately acts as their own databases for
each celebrity type.  I have assignment operators and copy constructors for the classes that
manage dynamic memory.

*/


Name::Name() //default constructor
{}
Name::Name(char * & a_name): the_name(a_name) //initialization list
{}

Name::Name(const Name & source) //copy constructor
{
    the_name = new char[strlen(source.the_name) + 1]; //char is initialized
    strcpy(the_name, source.the_name); //the name is copied
}
Name::~Name() //destructor
{
 
}

Name & Name::operator=(const Name & a_name) //assignment operator
{

	if(this != &a_name) //Checks for self assignment
	{
		delete [] the_name; //deallocates memory that 'the_name' points to
		//Allocate new memory and give it a good 'ol copy over
		the_name = new char[strlen(a_name.the_name) + 1]; 
		strcpy(the_name, a_name.the_name);
		
	}
	return *this; //return a reference




}
int Name::display() const //returns a name from the base class
{
  if(the_name == nullptr) return 0; //nothing in name, lets terminate. 
  else{
  cout << the_name; //print 'the_name', gonna note this part seg faults after executing the remove() function for the actor
  return 1;} //return 1

}
bool Name::compare_name(char * & comp_str) const //char compare function
{
	if(strcmp(the_name, comp_str) == 0) //return true if both are the same
  		return true;
	else
		return false; //nuhuh they are different

}


int Name::copy_name(char *& copy) const //passes input in and copies it over
{
	copy = the_name;
	return 1;
	
}

char * Name::get_name() //getter function, (I know ugh getters)
{
	return the_name;
}


Celebrity::Celebrity() //default constructor
{}

Celebrity::Celebrity(char *& a_name, int & an_age, int & a_wealth, string & a_comic, int & early, int & late): 
	Name(a_name), age(an_age), wealth(a_wealth), comic(a_comic), earliest_availability(early),
	latest_availability(late)
{}//initialization list

Celebrity::~Celebrity() 
{
  

}

int Celebrity::display() const //the display function for celebrity
{	
	cout << "Celebrity Name: "; 
	Name::display(); //this drives me nuts.  I used GDB so many times to figure out why this seg faults and it is so unclear to me.
	cout << endl; 
	cout << "Celebrity age: " << age << endl; //prints out the celebrity age
	
	cout << "Celebrity earliest availability: " << earliest_availability << endl; //earliest time a celebrity is available for a session
	cout << "Celebrity latest availability: " << latest_availability << endl; //latest time a celebrity is available for a session
	return 1;
  
}

int Celebrity::view_comic()
{

	cout << "This celebrity is associated with " << comic << endl;
	return 1;
}

bool Celebrity::is_successful()
{
	if(wealth < 100000){
		cout << "This celebrity is pretty average, nothing special. Their net worth is around $" << wealth << endl;
		cout << endl;}
	else{
		cout << "Oh yeah this celebrity is super rich, mega wealthy! Around $" << wealth << endl;}
	return true;

}

Actor::Actor() {} //default constructor
Actor::Actor(char *& a_name, int & an_age, int & a_wealth, string & a_comic, int & early, int & late, 
		int & awards_num, int & autograph_cost, bool & selfie): 
	Celebrity(a_name, an_age, a_wealth, a_comic, early, late), num_awards(awards_num), autograph(autograph_cost), selfie_included(selfie)
{} //initialization list

Actor::Actor(const Actor & source) : Celebrity(source), num_awards(source.num_awards), autograph(source.autograph), selfie_included(source.selfie_included)
{} //copy constructor
Actor::~Actor() {}

int Actor::display() //display function for each actor, works in most cases
{
	cout << "--------------------------------------------" << endl;	
	Celebrity::display(); //calls the parent class display function
	cout << endl; 
	
	
	
  	cout << "--------------------------------------------" << endl;	
	return 1;
}
int Actor::schedule_autograph(int & a_time) //user sets a time to meet with an actor for an autograph and the time is then placed into an vector of ints
{
  cout << "The cost of an autograph with this actor is: $" << autograph << ".00" << endl; //user sees how much the cost is
  if(a_time > earliest_availability && a_time < latest_availability) //makes sure requested time from user matches the time the actor can meet up
  {
	  
	  if(find(session_times.begin(), session_times.end(), a_time) != session_times.end()) //function from the algorithm STL that traverses the vector
	  {
		  cout << "Sorry, the Actor is already booked" << endl; //uh oh time won't work
		  return 0;
	  }
	  else
	  {
	  	cout << "Yes! This time works! Let's get you booked!" << endl; //session is booked
	  	session_times.push_back(a_time); //session is added (I love vectors)
	  }
  }
  else
	  cout << "Sorry, that time is out of range for when this Actor is available!" << endl; //time is invalid
  return 1;

}


bool Actor::is_selfie() //checks to see if a selfie is included with the autograph and lets the user know if it is.
{

	if(selfie_included == true)
	{	cout << "Yes! You can take a selfie with this actor at an autograph session\n";
		return true;
	}
  	cout << "Sorry, this actor does not allow selfies" << endl;
	return false;
}
bool Actor::acclaimed_actor() //provides information about if this actor is accomplished enough to be "acclaimed"
{
  if(num_awards >= 3)
  {
	cout << "Yeah! This actor has been recognized for many of their works" << endl;
  	

  }
  else
  {
	cout << "Meh, this actor is alright, nothing special!" << endl;
	
  }
  cout << "The actor has a total of " << num_awards << " awards!" << endl;
  return true; 
}



Artist::Artist() //default constructor
{}
Artist::~Artist() //destructor
{}
Artist::Artist(char *& a_name, int & an_age, int & a_wealth, string & a_comic, int & early, int & late, char * & the_drawing_types, int num_years, bool sig_is, string characters): 
	Celebrity(a_name, an_age, a_wealth, a_comic, early, late), drawing_types(the_drawing_types), years(num_years), is_sig(sig_is), the_characters_drawn(characters)
{} //initialization list/copy constructor
Artist::Artist(const Artist & source) : Celebrity(source), // Call the copy constructor of the base class
      years(source.years), is_sig(source.is_sig),  the_characters_drawn(source.the_characters_drawn) // Copy simple data members
{
    // Allocate new memory for drawing_types and copy the content from source.drawing_types
    drawing_types = new char[strlen(source.drawing_types) + 1];
    strcpy(drawing_types, source.drawing_types);
}
Artist & Artist::operator=(const Artist & an_artist) //assignment operator
{
	if(this != &an_artist) { //gives protection against bad self-assignment
		delete [] drawing_types; //deletes memory drawing_types points to
	drawing_types = new char[strlen(an_artist.drawing_types) + 1]; //new memory allocated and then copied
	strcpy(drawing_types, an_artist.drawing_types); 

	
	//other data members are copied over
	years = an_artist.years;
	is_sig = an_artist.is_sig;
	the_characters_drawn = an_artist.the_characters_drawn;
	}
	return *this; //reference returned

}
int Artist::years_of_drawing_experience() //returns the years of experience this artist has drawing
{

  cout << "This artist has been drawing for " << years << " years!" << endl;
  return 1;

}
string Artist::characters_drawn() //returns a string of characters drawn, each separated by commas. 
{
	cout << "The characters that this artist has drawn include: ";
	return the_characters_drawn;

}
bool Artist::signature_included() const //returns if a signature is included when doing business with the client
{
  if(is_sig == false)
  {
	 cout << "No, the artist does not include a signature" << endl;
	 return false; 
  }
  cout << "Yes, the artist does include a signature" << endl;
  return true;

}

int Artist::display() const //full display function for the artist
{
	cout << "--------------------------------------------" << endl;	
        cout << "Celebrity Name: ";
	Celebrity::display();
	cout << endl;	
	

	cout << "Drawing types that this artist does may include: " << drawing_types << endl;
	cout << "--------------------------------------------" << endl;	
		
	return 1;

	
	

}

Cosplayer::Cosplayer() //default constructor for cosplayer
{}
Cosplayer::Cosplayer(char *& a_name, int & an_age, int & a_wealth, string & a_comic, int & early, int & late, string a_character,
  string fav_out, int exp): Celebrity(a_name, an_age, a_wealth, a_comic, early, late), character(a_character), 
  favorite_outfit(fav_out), experience(exp)
{}


int Cosplayer::schedule_stunt(const int & a_time, const int & age) //gonna work on this a bit if I still have time, it will store the stunt time in a vector
{
  if(verify_age(age) == true)
  {
    if(find(session_times.begin(), session_times.end(), a_time) != session_times.end()) //function from the algorithm STL that traverses the vector
    {
      cout << "Sorry, the Cosplayer is already booked" << endl; //uh oh time won't work
      return 0;
    }
    else
    {
   	  cout << "Yes! This time works! Let's get you booked!" << endl; //session is booked
   	  session_times.push_back(a_time); //session is added (I love vectors)
    }
  }
  return 1;

}

bool Cosplayer::verify_age(const int & age)
{
  if(age < 12)
  {
    cout << "You are too young, we legally cannot permit any activities!" << endl;
    return false;
  }
  cout << "You are good to participate with this Cosplayer in a stunt!" << endl;
  return true;
}
int Cosplayer::show_character_description() //a description of what the character is is returned
{
  cout << "The description of this cosplayer: " << character << endl;
  return 1;
}

int Cosplayer::display_favorite_outfit() //a description of what the character is is returned
{
  cout << "Out of all characters this cosplayer has ever done, they most especially enjoyed: " << favorite_outfit << endl;
  return 1;
}

int Cosplayer::show_past_experience() //a description of what the character is is returned
{
  if(experience < 2)
  {
    cout << "This cosplayer has only really been active in this industry for " << experience << " years, so they are still\n kind of rookies" << endl;
  }
  else
  {
    cout << "This cosplayer has been really active in this industry for " << experience << " years, so they are super pro at what they do" << endl;
  }
  return 1;
}

