
#include <iostream>
#include <string>
#include <cstring>
#include <exception>
using namespace std;


/*
Here I have my core hierarchy.  My fifth class will be an interface class that performs all of the functions that
would be performed in main.  My four functions here consist of Activity, the base class, and then Tour, Game, and 
Concert.  I have operator overloading in all of my classes, with assignment operators in my classes that manage
dynamic memory.

 */


class Activity
{ 
    public:
        Activity();
        Activity(char *& an_activity_location, int & a_duration);
        Activity(const Activity & source);
        Activity & operator=(const Activity & an_activity);
        ~Activity();

        friend std::ostream & operator << (std::ostream & out, const Activity & op2);

        friend std::istream & operator >> (std::istream & in, Activity & op2);
       
        friend bool operator == (const Activity & op1, const Activity & op2);

        friend bool operator != (const Activity & op1, const Activity & op2);
 
    protected:
        char * activity_location;
        int duration;

};


class Tour: public Activity {
    public:
        Tour();
        Tour(char *& activity_location, int & duration, int & age, const std::string & some_features);

        ~Tour();
            
        friend std::ostream & operator << (std::ostream & out, const Tour & op2);

        friend istream & operator >> (istream & in, Tour & op2);
          
        friend bool operator < (const Tour & op1, const Tour & op2);
         
        friend bool operator <= (const Tour & op1, const Tour & op2);
         
        friend bool operator > (const Tour & op1, const Tour & op2);
         
        friend bool operator >= (const Tour & op1, const Tour & op2);

        bool operator == (const Tour & op2) const; 
        bool operator != (const Tour & op2) const; 
        
    protected:
        int site_age;
        std::string site_features;
};
 


class Game: public Activity {
    public:
        Game();
        Game(char *& activity_location, int & duration, char *& a_name, int & a_Hardness, int & a_Correct);
        Game(const Game & source);
        ~Game();
        Game & operator=(const Game & op1);
        
        friend std::ostream & operator << (std::ostream & out, const Game & op2);

        friend std::istream & operator >> (std::istream & in, Game & op2);
          
        friend bool operator < (const Game & op1, const Game & op2);
         
        friend bool operator <= (const Game & op1, const Game & op2);
         
        friend bool operator > (const Game & op1, const Game & op2);
         
        friend bool operator >= (const Game & op1, const Game & op2);
   
        bool operator == (const Game & op2) const;
        bool operator != (const Game & op2) const;
        int get_guess();
    protected:
        char * game_name;
        int levelOfHardness;
        int correctGuess;
        
};


 


class Concert: public Activity {
    public:
        Concert();
        Concert(char *& activity_location, int & duration, const std::string & a_band, int & a_time);

        ~Concert();
        
        friend std::ostream & operator << (std::ostream & op1, const Concert & op2);

        friend std::istream & operator >> (std::istream & op1, Concert & op2);
          
        friend bool operator < (const Concert & op1, const Concert & op2);
         
        friend bool operator <= (const Concert & op1, const Concert & op2);
         
        friend bool operator > (const Concert & op1, const Concert & op2);
         
        friend bool operator >= (const Concert & op1, const Concert & op2);
        
        bool operator == (const Concert & op2) const;
        bool operator != (const Concert & op2) const;
        
    protected:
        std::string band_name;
        int concertTime;

};

class ExceptionHandle: public exception
{
    public:
        const char * what() const noexcept override;
};

