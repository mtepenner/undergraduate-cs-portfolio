#include "program4.h"
/*


This is the animal .cpp file where I have the constructor, destructor, and respective functions that allow for the program to work efficiently with as minimal
memory leaks as possible.
*/
animal::animal() //Animal constructor
{
  breed = NULL;
  category = NULL;
  personality = NULL;
  purpose = NULL;
  size = NULL;
  keywords = NULL;
  age = 0;
}

animal::~animal() //Animal destructor
{
  if (breed)
   delete [] breed; 
  if (category) 
   delete [] category;
  if (personality) 
   delete [] personality; 
  if (purpose) 
   delete [] purpose;
  if (size)
   delete [] size;
  if (keywords)
   delete [] keywords;
  if (age)
   age = 0;
}

int animal::copy_entry(const animal & copy_from) //Copies data over
{
  //First checks to see if any data exists in the animal data is being copied into
  if (breed)
   delete [] breed; 
  if (category) 
   delete [] category;
  if (personality) 
   delete [] personality; 
  if (purpose) 
   delete [] purpose;
  if (size)
   delete [] size;
  if (keywords)
   delete [] keywords;
  if (age)
   age = 0;
     
  breed = category = personality = purpose = size = keywords = NULL; 
  age = 0;

  if (copy_from.breed) //copies a breed
  { 
     breed = new char[strlen(copy_from.breed) +1]; 
     strcpy(breed, copy_from.breed); 
  } 
  if (copy_from.category) //copies the category
  { 
     category = new char[strlen(copy_from.category)+1]; 
     strcpy(category, copy_from.category); 
  } 
  
  if (copy_from.personality) //copies the personality
  { 
     personality = new char[strlen(copy_from.personality) +1]; 
     strcpy(personality, copy_from.personality); 
  } 
  
  if (copy_from.purpose) //copies the purpose
  { 
     purpose = new char[strlen(copy_from.purpose) +1]; 
     strcpy(purpose, copy_from.purpose); 
  } 
  
  if (copy_from.size) //copies the size
  { 
     size = new char[strlen(copy_from.size) +1]; 
     strcpy(size, copy_from.size); 
  } 
  
  if (copy_from.keywords) //copies the keywords
  { 
     keywords = new char[strlen(copy_from.keywords) +1]; 
     strcpy(keywords, copy_from.keywords); 
  } 
  if (copy_from.age) //copies the age
  { 
     age = copy_from.age;
  } 

  return 1;
}

int animal::display() //displays an animal object
{
  cout << endl;
  cout << "Animal Breed:       " << breed << endl;
  cout << "Animal Category:    " << category << endl;
  cout << "Animal Personality: " << personality << endl;
  cout << "Animal Purpose:     " << purpose << endl;
  cout << "Animal Size:        " << size << endl;
  cout << "Animal Keywords:    " << keywords << endl;
  cout << "Animal Age:         " << age << endl;
  cout << endl;
  
  return 1;

}

int animal::fill(char BREED[], char CATEGORY[], char PERSONALITY[], char PURPOSE[], char SIZE[], char KEYWORDS[], int AGE) //Takes statically allocated arrays and dynamically allocates them
{
 
  breed = new char[strlen(BREED) + 1];
  strcpy(breed, BREED);
  
  category = new char[strlen(CATEGORY) + 1];
  strcpy(category, CATEGORY);
  
  personality = new char[strlen(PERSONALITY) + 1];
  strcpy(personality, PERSONALITY);
  
  purpose = new char[strlen(PURPOSE) + 1];
  strcpy(purpose, PURPOSE);
  
  size = new char[strlen(SIZE) + 1];
  strcpy(size, SIZE);
  
  keywords = new char[strlen(KEYWORDS) + 1];
  strcpy(keywords, KEYWORDS);
  
  age = AGE;


  return 1;


}
