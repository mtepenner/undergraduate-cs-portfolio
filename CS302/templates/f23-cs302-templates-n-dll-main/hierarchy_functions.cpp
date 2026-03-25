
#include "hierarchy.h"
#include <stdexcept>
using namespace std;

/*
   Below I have implemented all of my operator overloading for my hierarchy classes.  Additionally I have created default constructors,
   copy constructors, destructors, and assignment operators.  The Concert and Tour classes only required the default constructor as
   they are not managing dynamic memory.  The Game class and base Activity class are however.
 */
 
const char * ExceptionHandle::what() const noexcept //My Exception Handle function
{
    return "Uh oh spagettio no data here\n\n";
}
/***************************ACTIVITY CLASS FUNCTIONS*********************************/
Activity::Activity(): activity_location(nullptr), duration(0)
{

}
Activity::Activity(char *& an_activity_location, int & a_duration): activity_location(nullptr), duration(a_duration)
{
    if(an_activity_location != nullptr)
    {
        this->activity_location = new char[strlen(an_activity_location) + 1];
        strcpy(this->activity_location, an_activity_location);
    }
}
Activity::Activity(const Activity & source): activity_location(nullptr)
{
    if(source.activity_location) {
        activity_location = new char[strlen(source.activity_location) + 1];
        strcpy(activity_location, source.activity_location);
    }
    duration = source.duration;


}
Activity::~Activity()
{
    if(activity_location){
    delete [] activity_location;
    activity_location = nullptr;}
}

Activity & Activity::operator=(const Activity & op1)
{

    if(this != &op1)
    {
        delete [] activity_location;
        activity_location = nullptr;

    }
    if(op1.activity_location)
    {
        activity_location = new char[strlen(op1.activity_location) + 1];

        strcpy(activity_location, op1.activity_location);
    }
    duration = op1.duration;


    return *this;
}

ostream & operator << (ostream & out, const Activity & op2)
{
    try {
        if(!op2.activity_location) {
            throw ExceptionHandle();
        }
        out << "Location Name: " << op2.activity_location << endl << "Activity Duration: " << op2.duration << " hours" << endl;
    }
    catch(const ExceptionHandle& e) {
        cerr << "AHA! Caught an exception\n" << e.what();
    }

    return out;
}

istream & operator >> (istream & in, Activity & op2)
{ 

    cout << "Enter the location of this Activity: ";
    char temp[100]; 
    in.get(temp, 100, '\n');
    in.ignore(100, '\n');
    op2.activity_location = new char[strlen(temp) + 1];
    strcpy(op2.activity_location, temp);

    cout << "Enter the duration of this Activity: ";
    in >> op2.duration;
    in.ignore(100, '\n');
    return in;
}


/***************************TOUR CLASS FUNCTIONS*********************************/

Tour::Tour()
{}
Tour::Tour(char *& an_activity_location, int & a_duration, int & age, const string & some_features): 
    Activity(an_activity_location, a_duration), site_age(age), site_features(some_features)
{}
Tour::~Tour()
{

}



ostream & operator << (ostream & out, const Tour & op2)
{
    try {
    if(!op2.activity_location){
        throw ExceptionHandle();
    }
    out << "-------------------------------------------------------------------------\n";
    out << "Activity Details:\n" << static_cast<const Activity&>(op2);
    out << "Site Age: " << op2.site_age << "\nSite Features: " << op2.site_features;
    out << "\n------------------------------------------------------------------------\n";

    }

    catch(const ExceptionHandle & e) {
      cerr << "Uh oh.  Did not work as expected: " << e.what() << endl;
    }
    return out;
}

istream & operator >> (istream & in, Tour & op2)
{
        operator >> (in, static_cast<Activity&>(op2));
        cout << "Enter the age of the site you are visiting: \n";
        in >> op2.site_age;
        cout << "\nEnter the features of the site you are visiting: \n";
        in.ignore();
        getline(in, op2.site_features);
    
    return in;
}

bool operator < (const Tour & op1, const Tour & op2)
{
    if(op1.site_age < op2.site_age) return true;

    return false;

}

bool operator <= (const Tour & op1, const Tour & op2)
{
    if(op1.site_age <= op2.site_age) return true;

    return false;

}

bool operator > (const Tour & op1, const Tour & op2)
{
    if(op1.site_age > op2.site_age) return true;

    return false;

}

bool operator >= (const Tour & op1, const Tour & op2)
{
    
    if(op1.site_age >= op2.site_age) return true;
    

    return false;

}

bool Tour::operator == (const Tour & op2) const
{

    if(site_features == op2.site_features) return true;

    return false;
}
bool Tour::operator != (const Tour & op2) const
{
    if(site_features != op2.site_features) return true;
    return false;
}

/***************************GAME CLASS FUNCTIONS*********************************/
Game::Game(): game_name(nullptr), levelOfHardness(0), correctGuess(0)
{}
Game::Game(char *& an_activity_location, int & a_duration, char *& a_name, int & a_Hardness, int & a_Correct): 
    Activity(an_activity_location, a_duration), game_name(a_name), levelOfHardness(a_Hardness), correctGuess(a_Correct)
{
    if(a_name != nullptr)
    { 
        this->game_name = new char[strlen(a_name) + 1];
        strcpy(this->game_name, a_name);

    }
}
Game::Game(const Game & source): Activity(source), levelOfHardness(source.levelOfHardness), correctGuess(source.correctGuess)
{
    if(!source.game_name) {
        game_name = new char[strlen(source.game_name) + 1];
        strcpy(game_name, source.game_name);
    }
    levelOfHardness = source.levelOfHardness;
    correctGuess = source.correctGuess;
}
Game::~Game()
{
    if(game_name){
        delete [] game_name;
    }
}

Game & Game::operator=(const Game & op1)
{
    if(this != &op1)
    {
        delete [] game_name;
        game_name = nullptr;

    }
    if(op1.game_name)
    {
        game_name = new char[strlen(op1.game_name) + 1];

        strcpy(game_name, op1.game_name);
    }
    levelOfHardness = op1.levelOfHardness;
    correctGuess = op1.correctGuess;


    return *this;

}
ostream & operator << (ostream & out, const Game & op2)
{
    
    try {
        if(!op2.game_name) {
            throw ExceptionHandle();
        }
        out << "-------------------------------------------------------------------------\n";
        out << "Activity Details:\n" << static_cast<const Activity&>(op2);

        out << "Game Name: " << op2.game_name << endl << "Hardness Level: " << op2.levelOfHardness << endl;
        out << "\n-------------------------------------------------------------------------\n";

    }
    catch (const ExceptionHandle & e) {
        cerr << "Uh oh.  Did not work as expected: " << e.what();
    }
    return out;
}

istream & operator >> (istream & in, Game & op2)
{
    try {
        in >> static_cast<Activity&>(op2);
        cout << "Enter the name of the game you are playing: \n";
        char temp[100]; 
        in.get(temp, 100, '\n');
        in.ignore(100, '\n');
        op2.game_name = new char[strlen(temp) + 1];
        strcpy(op2.game_name, temp);
        cout << "\nEnter on a scale of 1-10 how hard this game is: \n";
        in >> op2.levelOfHardness;
        cout << "\nEnter a guess from 1-10: \n";
        in >> op2.correctGuess;
    }
    catch (const ExceptionHandle & e) {
        cerr << "Uh oh.  Did not work as expected: " << e.what() << endl;
    }
    return in;
}

bool operator < (const Game & op1, const Game & op2)
{
    try {
        if(op1.levelOfHardness < op2.levelOfHardness) return true;
    }

    catch (const ExceptionHandle & e) {
        cerr << "Uh oh.  Did not work as expected: " << e.what() << endl;
    }
    return false;

}

bool operator <= (const Game & op1, const Game & op2)
{
    try {
        if(op1.levelOfHardness <= op2.levelOfHardness) return true;
    }
    catch (const ExceptionHandle & e) {
        cerr << "Uh oh.  Did not work as expected: " << e.what() << endl;
    }
    return false;

}

bool operator > (const Game & op1, const Game & op2)
{
    try {

        if(op1.levelOfHardness > op2.levelOfHardness) return true;
    }
    catch (const ExceptionHandle & e) {
        cerr << "Uh oh.  Did not work as expected: " << e.what() << endl;
    }
    return false;

}

bool operator >= (const Game & op1, const Game & op2)
{
    try {
        if(op1.levelOfHardness >= op2.levelOfHardness) return true;
    }
    catch (const exception & e) {
        cerr << "Uh oh.  Did not work as expected: " << e.what() << endl;
    }
    return false;

}

bool Game::operator == (const Game & op2) const
{
    try {
        if(correctGuess == op2.correctGuess) return true;
    }
    catch (const ExceptionHandle & e) {
        cerr << "Uh oh.  Did not work as expected: " << e.what() << endl;
    }
    return false;
}
bool Game::operator != (const Game & op2) const
{
    try {
        if(op2.correctGuess != correctGuess) return true;
    }
    catch (const ExceptionHandle & e) {
        cerr << "Uh oh.  Did not work as expected: " << e.what() << endl;
    }
    return false;
}

int Game::get_guess()
{
  return correctGuess;
}

/***************************CONCERT CLASS FUNCTIONS*********************************/
Concert::Concert()
{}
Concert::Concert(char *& an_activity_location, int & a_duration, const string & a_band, int & a_time): 
    Activity(an_activity_location, a_duration), band_name(a_band), concertTime(a_time)
{}

Concert::~Concert()
{}

ostream & operator << (ostream & out, const Concert & op2)
{

        out << "-------------------------------------------------------------------------\n";

        out << "Activity Details:\n" << static_cast<const Activity&>(op2);

        out << "Band Name: " << op2.band_name << endl << "\nConcert Time: " << op2.concertTime << endl;
        out << "\n-------------------------------------------------------------------------\n";

    
    return out;
}
istream & operator >> (istream & in, Concert & op2)
{
        in >> static_cast<Activity&>(op2);
        cout << "Enter the name of the band: \n";
        in.ignore();
        getline(in, op2.band_name);
        cout << "\nEnter the concert time (the hour): \n";
        in >> op2.concertTime;

    return in;
}

bool operator < (const Concert & op1, const Concert & op2)
{
    if(op1.concertTime < op2.concertTime) return true;
    
    return false;

}

bool operator <= (const Concert & op1, const Concert & op2)
{
    if(op1.concertTime <= op2.concertTime) return true;
    
    return false;

}

bool operator > (const Concert & op1, const Concert & op2)
{
    if(op1.concertTime > op2.concertTime) return true;
    

    return false;

}

bool operator >= (const Concert & op1, const Concert & op2)
{

    if(op1.concertTime >= op2.concertTime) return true;
    
    return false;

}

bool Concert::operator == (const Concert & op2) const
{
    if(band_name == op2.band_name) return true;
   
    return false;
}
bool Concert::operator != (const Concert & op2) const
{

    if(band_name != op2.band_name) return true;
    
    return false;
}





















