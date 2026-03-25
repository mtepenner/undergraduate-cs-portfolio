//Matthew Penner
//My animal cpp file
//animal.cpp
#ifndef ANIMAL_CPP
#define ANIMAL_CPP
#include "animal.h"
#include "twoThreeTree.h"

/*
Here is the cpp file that contains all of my functions.  Each class has a copy constructor.
I did not create an assignment operator since I am not using any raw pointers in my code.
Because pet is virtual dynamic binding must take place to allow instances of pet objects.
*/


//PET CLASS FUNCTIONS
/*********************************************************************************/
pet::pet() 
{}

pet::pet(const pet& toCopy) 
{
  name = toCopy.name;
  levelOfCare = toCopy.levelOfCare;
  temperament = toCopy.temperament;
  isFriendly = toCopy.isFriendly;
}

pet::pet(const string & a_name, int & care, int & aTemperament, bool & friendly): 
        name(a_name), levelOfCare(care), temperament(aTemperament), isFriendly(friendly)
{}

int pet::addHistory()
{
  string description;
  cout << "Write down a list of incidents involving this pet separated by commas, then press return: \n";
  cin >> description;
  cin.ignore(100, '\n');
  history = description;
  return 1;
}
int pet::showHistory() const
{
  cout << "This pet has the following history: \n" << history << endl;
  return 1;
}
int pet::showCareLevel()
{
  cout << "Level of Care Required: " << levelOfCare << endl;
  return 1;

}
string pet::getName() const 
{ return name; }
int pet::display() const
{
  
  return 1;
}

int pet::showTemperamentLevel() const
{
  cout << "This pet's temperament level is: " << temperament << endl;
  return 1;
}

/*********************************************************************************/

//DOG CLASS FUNCTIONS
/*********************************************************************************/
dog::dog()
{}

dog::dog(const string & a_name, int & care, int & aTemperament, bool & friendly, string & aToy): 
        pet(a_name, care, aTemperament, friendly), favoriteChewToy(aToy)
{
  isChipped = false;
  hasLicense = false;
}

dog::dog(const dog& toCopy): pet(toCopy)
{
  favoriteChewToy = toCopy.favoriteChewToy;
  isChipped = toCopy.isChipped;
  hasLicense = toCopy.hasLicense;
}

string dog::getName() const 
{ return pet::getName(); }

int dog::display() const
{
  cout << "Dog Name: " << getName() << endl;

  if(isChipped)
  {
    cout << "This dog is chipped!\n";
  }
  else
  {
    cout << "This dog is NOT chipped!\n";
  }
  
  if(hasLicense)
  {
    cout << "This dog has a license\n";
  }
  else
  {
    cout << "This dog does NOT have a license!\n";
  }
  showTemperamentLevel();
  pet::display();
  cout << "Dog's favorite toy: " << favoriteChewToy << endl;
  return 1;
}

int dog::showTemperamentLevel() const
{
  pet::showTemperamentLevel();
  return 1;
}
int dog::showHistory() const
{
  pet::showHistory();
  return 1;

}
int dog::updateFavoriteToy(string & aToy)
{
  favoriteChewToy = aToy;
  return 1;
}

bool dog::installMicrochip()
{
  isChipped = true;
  return isChipped;
}

bool dog::obtainLicense()
{
  hasLicense = true;
  return hasLicense;
}

/*********************************************************************************/

//CAT CLASS FUNCTIONS
/*********************************************************************************/
cat::cat()
{}
cat::cat(const string & a_name, int & care, int & aTemperament, bool & friendly, int & adjTime):
        pet(a_name, care, aTemperament, friendly), adjustmentTime(adjTime)
{
  catnipAddict = false;
}
cat::cat(const cat& toCopy): pet(toCopy)
{
  adjustmentTime = toCopy.adjustmentTime;
  catnipAddict = toCopy.catnipAddict;
}
string cat::getName() const 
{ return pet::getName(); }
int cat::display() const
{
  cout << "Cat Name: " << getName() << endl;
  cout << "Time to adjust to new home: " << adjustmentTime << endl;
  if(catnipAddict)
  {
    cout << "This cat IS a catnip addict\n";
  }
  else
  {
    cout << "This cat is NOT a catnip addict\n";
  }
  showTemperamentLevel();
  pet::display();
  return 1;

}
int cat::showTemperamentLevel() const
{
  pet::showTemperamentLevel();
  return 1;
}
        
bool cat::isAnAddict()
{
  catnipAddict = true;
  return catnipAddict;
}

int cat::showHistory() const
{
  pet::showHistory();
  return 1;

}
/*********************************************************************************/

//BUNNY CLASS FUNCTIONS
/*********************************************************************************/
bunny::bunny()
{}
bunny::bunny(const string & a_name, int & care, int & aTemperament, bool & friendly, bool & sharpTeeth, string & aBrand):
            pet(a_name, care, aTemperament, friendly), hasSharpTeeth(sharpTeeth), favoriteCarrotBrand(aBrand)
{
  outdoorBunny = false;
}

bunny::bunny(const bunny& toCopy): pet(toCopy)
{
  hasSharpTeeth = toCopy.hasSharpTeeth;
  favoriteCarrotBrand = toCopy.favoriteCarrotBrand;
}
string bunny::getName() const 
{ return pet::getName(); }   
int bunny::display() const
{
  cout << "Bunny Name: " << getName() << endl;
  cout << "This bunny loves " << favoriteCarrotBrand << " carrots\n";
  if(hasSharpTeeth)
  {
    cout << "This bunny DOES have sharp teeth\n";
  }
  else
  {
    cout << "This bunny does NOT have sharp teeth\n";
  }
  showTemperamentLevel();
  if(outdoorBunny)
  {
    cout << "This bunny DOES love the outdoors\n";
  }
  else
  {
    cout << "This bunny DOES NOT love the outdoors\n";
  }
  cout << "Pet History: " << pet::history << endl;
  return 1;
}
int bunny::showHistory() const
{
  pet::showHistory();
  return 1;
}
int bunny::showTemperamentLevel() const
{
  pet::showTemperamentLevel();
  return 1;
}

 
int bunny::updateFavoriteCarrot(string & carrot)
{
  favoriteCarrotBrand = carrot;
  return 1;
}

bool bunny::isOutdoor()
{
  outdoorBunny = true;
  return true;

}
/*********************************************************************************/



#endif











