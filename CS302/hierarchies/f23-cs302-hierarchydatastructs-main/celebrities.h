/* 
Matthew Penner
CS302-001
Professor Fant

Program #1 Header File

All of my celebrity class function prototypes are here.  I am planning on keeping it relatively simple.
I will have 5 classes and have the three celebrity derived classes come from a celebrity class that is derived from a Name class.  
I was originally going to have it be more complicated with an itenerary class and an appointment class, but decided that it would
be best if I just was more straightforward to just keep it light and not focus so much on scheduling other than 
to add or cancel an appointment.  I instead will just have a Name class be the base. My data structure classes and nodes
will be in a separate .h file.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
#pragma once

using std::vector;
using std::string;
using namespace std;
enum class celebrity_type {actor, artist, cosplayer};

class Name //The base class that houses a Celebrity's name
{
    public:
        Name();
        Name(char * & a_name);
        Name(const Name & source);
        ~Name();
	Name & operator=(const Name & a_name);
        int display() const;
        bool compare_name(char * & comp_str) const;
        int copy_name(char *& copy) const;
        char * get_name();		
    protected:
        char * the_name;
};


class Celebrity: public Name /*The derived class of Name, which has pretty much every other information about the 
celebrity, can probably push most of it up*/			   
{
    public:
        Celebrity();
	Celebrity(char *& a_name, int & an_age, int & a_wealth, string & a_comic, int & early, int & late);  
        ~Celebrity();     
        int view_comic();
      	int schedule_session(int & time);
      	
      	bool is_successful();
      	int display() const;
    protected:
        int age;
      	int wealth;
      	string comic;
      	int earliest_availability;
      	int latest_availability;
      	vector <int> session_times;
};




class Artist: public Celebrity //Derived celebrity class
{
    public:
        Artist();
        ~Artist();
        Artist(char *& a_name, int & an_age, int & a_wealth, string & a_comic, int & early, int & late, char * & the_drawing_types, 
        int num_years, bool sig_is, string characters);
        Artist(const Artist & source);
        Artist & operator=(const Artist& an_artist);		
	int display() const;
        int years_of_drawing_experience ();
        string characters_drawn();
        bool signature_included() const;
    protected:
        char * drawing_types;
        int years;
      	bool is_sig;
      	string the_characters_drawn;
	


};

class Actor: public Celebrity //Derived celebrity class
{
    public:
	Actor();
        Actor(char *& a_name, int & an_age, int & a_wealth, string & a_comic, int & early, int & late, 
		  	  int & awards_num, int & autograph_cost, bool & selfie);
        Actor(const Actor & source);
        ~Actor();
        int schedule_autograph(int & a_time);
	bool is_selfie();
        bool acclaimed_actor();
	int display();
    protected:
        int num_awards;
        int autograph;
	bool selfie_included;
	

};

class Cosplayer: public Celebrity //Derived celebrity class
{
    public:
        Cosplayer();
	      Cosplayer(char *& a_name, int & an_age, int & a_wealth, string & a_comic, int & early, int & late, string a_character
          ,string fav_out, int exp);
   
        int schedule_stunt(const int & time, const int & age);
        bool verify_age(const int & age);
        int show_character_description();
        int show_past_experience();
        int display_favorite_outfit();
    protected:
        string character;
        string favorite_outfit;
        int experience;


};


