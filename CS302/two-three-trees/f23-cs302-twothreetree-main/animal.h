//Matthew Penner
//My header file
//animal.h
#include <iostream>
#ifndef ANIMAL_H
#define ANIMAL_H
#include <memory>
#include <string>
#include <map>
/*
My pet class is my abstract base class with two pure virtual functions: display() and
showTemperamentLevel().  I also have two non virtual functions called addHistory() and 
showCareLevel().  All of the data in pet is common of all pet types.  Each derived class
has a set of unique functions.
*/
using namespace std;

class pet
{
    public:
        pet();
        pet(const pet& toCopy);
        pet(const string & a_name, int & care, int & aTemperament, bool & friendly);
        int addHistory();
        int showCareLevel();
        //My virtual functions:
        virtual string getName() const;
        virtual int showHistory() const = 0;
        virtual int display() const = 0;
        virtual int showTemperamentLevel() const = 0;
    protected:
        string name;
        int levelOfCare;
        int temperament;
        bool isFriendly;
        string history;
};


class dog: public pet
{
    public:
        dog();
        dog(const string & a_name, int & care, int & aTemperament, bool & friendly, string & aToy);
        dog(const dog& toCopy);
        string getName() const override;
        int display() const;
        int showTemperamentLevel() const;
        int showHistory() const;
        //Unique functions
        int updateFavoriteToy(string & aToy);
        bool installMicrochip();
        bool obtainLicense();
    private:
        bool isChipped;
        bool hasLicense;
        string favoriteChewToy;
};

class cat: public pet
{
    public:
        cat();
        cat(const string & a_name, int & care, int & aTemperament, bool & friendly, int & adjTime);
        cat(const cat& toCopy);
        string getName() const override;
        int display() const;
        int showTemperamentLevel() const;
        int showHistory() const;
        //Unique functions        
        bool isAnAddict();
    private:
        int adjustmentTime;
        bool catnipAddict;

};

class bunny: public pet
{
    public:
        bunny();
        bunny(const string & a_name, int & care, int & aTemperament, bool & friendly, bool & sharpTeeth, string & aBrand);
        bunny(const bunny& toCopy);
        string getName() const override;
        int display() const;
        int showTemperamentLevel() const;
        int showHistory() const;
        //Unique functions   
        int updateFavoriteCarrot(string & carrot);
        bool isOutdoor();
    private:
        bool hasSharpTeeth;
        string favoriteCarrotBrand;
        bool outdoorBunny;
        
};




#endif