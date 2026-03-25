#include "program3.h"
/*This is the main file that houses all of the table functions.  I have a separate file for animal functions.
I have one recursive function which repeats with the i value of the elements being incremented.*/
table::table(int size) //Constructor
{
      hash_table = new node * [size]; //table is initialized
      for(int i = 0; i < size; ++i)
          hash_table[i] = NULL; //Each of the elements are set to null
      hash_table_size = size; //The size passed in is set to hash_table_size
}

table::~table(void) //Destructor
{
  node * temp;
  for(int i = 0; i < hash_table_size; ++i)
  {
    while(hash_table[i])
    {
      temp = hash_table[i]->next;
      delete hash_table[i];
      hash_table[i] = temp;

    }
  }
}

int table::add_animal(char * key_value, animal & to_add) //Add an animal   
{
  node * temp = new node;
  int index = hash_function(key_value); //hash function called to determine where animal should be placed
  temp->entity.copy_entry(to_add);
  temp->next = hash_table[index];
  hash_table[index] = temp;
  return 1;
}
bool table::retrieve(char * keyword_to_find, animal animal_array[]) //Retrieve information for a match by keyword
{
  bool determiner = false;
  int count = 0; //Determines if there are any animals
  if(!hash_table[0])
    return determiner;
  int j = 0;
  for(int i = 0; i < hash_table_size; ++i) //Iterates through the hash table elements
  {
    node * temp = hash_table[i]; //The head pointer of each element set to be a temp node
    while(temp)
    {
      if(strcmp(temp->entity.keywords, keyword_to_find) == 0) //If there are animals with the said keyword
      {  
        animal_array[j].copy_entry(temp->entity);
        ++j;
        ++count;
      }
      temp = temp->next;
    
    }
  
  }
  if(count > 0)
    determiner = true;
  return determiner;
  
}


int table::remove_by_keywords(char * keyword_to_find) //Remove animals based on keyword
{
  for(int i = 0; i < hash_table_size; ++i) //Iterates through each table element
  {
    node * temp = hash_table[i];
    node * previous = NULL;
    if(temp)
    {
    
	    if(!temp->next) //Only one node in the element
	    {
	      if(strcmp(temp->entity.keywords, keyword_to_find) == 0) //The animal has been found
	      { 
      		delete temp;
      		hash_table[i] = NULL;
	      }
	    }
	    else if(strcmp(hash_table[i]->entity.keywords, keyword_to_find)==0)
	    {
	      node * hold = hash_table[i]->next;
	      delete hash_table[i];
	      hash_table[i] = hold;
	      

	    }
	    while(temp) //Not at end of animal nodes, and need to iterate to the correct one
	    {
	      previous = temp; //previous pointer used
	      if(strcmp(temp->entity.keywords, keyword_to_find) == 0) //The animal has been found
	      {
      		node * current = temp-> next;
      		delete temp;
      		previous->next = current;
      		temp = current;
	      }
	      temp = temp->next;
	    
	    }
   }
  }
  return 1;
}
int table::display_all() //Wrapper display function for testing 
{
  int i = 0;
  return display_all(i);
}

int table::display_all(int i) //Main display all function
{
  node * temp = hash_table[i]; //Iterative node set for traversal in each element
  if(i == hash_table_size)
    return 0;
  while(temp)
  {
    temp->entity.display();
    temp = temp->next;
    
  }
  ++i;
  return 1 + display_all(i); //Recursively iterates through each element
  
  
}
int table::display_with_personality_type(char * personality_to_find) //Displays all animals that match the personality type
{
  for(int i = 0; i < hash_table_size; ++i)
  {
    node * temp = hash_table[i];
    while(temp)
    {
      if(strcmp(temp->entity.personality, personality_to_find) == 0)
        temp->entity.display();
      temp = temp->next;
    
    }
  
  }
  return 1;
}

int table::display_with_keyword_type(char * keyword_to_find) //Similar to personality but uses keywords instead and is a display function
{
  for(int i = 0; i < hash_table_size; ++i)
  {
    node * temp = hash_table[i];
    while(temp)
    {
      if(strcmp(temp->entity.keywords, keyword_to_find) == 0)
        temp->entity.display();
      temp = temp->next;
    
    }
  
  }
  return 1;
}
int table::hash_function(char * key) //Private hash function
{
  int sum = 0;
  for(int i = 0; i < strlen(key); ++i)
  {
    ++sum;
  }
  return sum % hash_table_size;
}

int table::load() //Loads the animals in the external data files
{
  int MAX = 255;

  char BREED[MAX];
  char CATEGORY[MAX];
  char PERSONALITY[MAX];
  char PURPOSE[MAX];
  char SIZE[MAX];
  char KEYWORDS[MAX];
  int AGE;

  ifstream in_file;
  in_file.open("external.txt"); //text file is opened
  if(in_file)
  {
    in_file.get(BREED, MAX, '|');
    in_file.ignore(100, '|');
    
    while(in_file && !in_file.eof()) //Retrieves all animal components from the external data file by line
    {
      animal object;
      in_file.get(CATEGORY, MAX, '|');
      in_file.ignore(100, '|');  
      
      in_file.get(PERSONALITY, MAX, '|');
      in_file.ignore(100, '|'); 
      
      in_file.get(PURPOSE, MAX, '|');
      in_file.ignore(100, '|'); 
      
      in_file.get(SIZE, MAX, '|');
      in_file.ignore(100, '|');
      
      in_file.get(KEYWORDS, MAX, '|');
      in_file.ignore(100, '|');
      
      in_file >> AGE;
      in_file.ignore(100, '\n');
      
      object.fill(BREED, CATEGORY, PERSONALITY, PURPOSE, SIZE, KEYWORDS, AGE); //Data copied over
      int added = add_animal(object.breed, object);
      in_file.get(BREED, MAX, '|');
      in_file.ignore(100, '|');
      
      
    } 
    in_file.close();
    in_file.clear();
  
  }

  return 1;
}
