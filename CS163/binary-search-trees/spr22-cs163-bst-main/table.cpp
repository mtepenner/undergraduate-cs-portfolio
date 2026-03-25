#include "program4.h"

/*


This is the cpp file that contains code for the table class.  I have several wrapper functions and private access functions that are all mostly recursive.  
These functions are crucial as being part of my BST data structure.  


*/

table::table()
{
  root = new node;
  root->left = NULL;
  root->right = NULL;
  root = NULL;
}
table::~table() //Destructor
{
   remove_all(root); //Removes every root
}
int table::display_all() //Wrapper function
{
  return display_all(root); //Calls private function and accesses root
}
int table::display_all(node * & root) //Private function that displays every node in the BST
{
  if(!root) //Is null
    return 0;
  else
  {
    int show = display_all(root->left);
    root->object.display(); //Displays each component of the nodes
    show = display_all(root->right); //Recursive call to both the left and right nodes
    
    
  }
  return 1;
}
int table::display_all_breed(char * breed) //Displays all of a certain breed
{
  return display_all_breed(root, breed); //Accesses private data structure
}
int table::display_all_breed(node * & root, char * breed) //Private data structure
{
  if(!root) //Nothing to display in root
    return 0;
  
  int show = display_all_breed(root->left, breed)+display_all_breed(root->right, breed); //Recursive call
  
  if(strcmp(root->object.breed, breed) == 0) //Is a match
    root->object.display(); //Animal display function called
  
  return 1;
}
int table::retrieve(int count, char * breed, char * personality, animal animal_array[]) //Wrapper function
{
  return retrieve(count, breed, personality, animal_array, root);
}
int table::retrieve(int count, char * breed, char * personality, animal animal_array[], node * & root) //Retrieves every animal with the matching key
{

  if (!root) return 0;
  if(strcmp(root->object.breed, breed) == 0) //Is a match
  {
    if(strcmp(root->object.personality, personality) == 0) //Is a match
    {
      animal_array[count].copy_entry(root->object); //Copies entry into passed in animal array
      ++count;
    }
  }
  
  int grab = retrieve(count, breed, personality, animal_array, root->left) + retrieve(count, breed, personality, animal_array, root->right); //Recursive call
  
  return 1;
}
int table::remove_all() //Wrapper
{
    return remove_all(root);
}
int table::remove_all(node * & root) //Recursive destructor function
{
  if (!root) return 0;
  int getout = remove_all(root->left)+remove_all(root->right); //Recursive call
  delete root;
  
  return 1;
}  

int table::add_pet(animal & to_add) //Wrapper function
{
  return add_pet(root, to_add); //Function call to access root

}
int table::add_pet(node * & root, animal & to_add) //Recursive function to add a pet
{
  int add{0};
  if(!root) //Nothing in root, time to add a node
  {
    root = new node;
    root->object.copy_entry(to_add);
    root->left = root->right = NULL;
    return 1;
  }
  if(strcmp(root->object.breed, to_add.breed) < 0) //Compares to determine alphabetical order
    return add_pet(root->right, to_add);
  if(strcmp(root->object.breed, to_add.breed) > 0)
    return add_pet(root->left, to_add);
  else
  {
    if(strcmp(root->object.personality, to_add.personality) < 0)
      return add_pet(root->right, to_add);
    else
      return add_pet(root->left, to_add);
  }
  root = new node;
  root->object.copy_entry(to_add);
  
  return 1;
}


int table::remove_by_breed(char * breed) //Wrapper
{
    return remove_by_breed(root, breed);
}
int table::remove_by_breed(node * & root, char * breed) //Recursive destructor function
{
  if (!root) return 0;
  int getout = remove_by_breed(root->left, breed)+remove_by_breed(root->right, breed);
  if(strcmp(root->object.breed, breed) == 0)
  {
    if(root->right && root->left)
    { 
      node * hold = root->right;
      node * previous = hold;
      while(hold->left)
      {
        previous = hold;
        hold = hold->left;
      }
      root->object.copy_entry(hold->object);
      previous->left = hold->right;
      delete hold;	

    }
    else if(root->right)
    {
      node * hold = root->right;
      delete root;
      root = hold;
    }
    else if(root->left)
    {
      node * hold = root->left;
      delete root;
      root = hold;
    }
    else
    {
     delete root;
     root = NULL;
    }
  }
  

  return 1;
} 
int table::display_with_size(char * size) //Displays with certain size parameter
{
  return display_with_size(root, size); //Calls private function
}
int table::display_with_size(node * & root, char * size) //Recursive function
{
  if(!root) //Nothing to display
    return 0;
  
  int show = display_with_size(root->left, size)+display_with_size(root->right, size); //Recursive call
  
  if(strcmp(root->object.size, size) == 0) //Is a match
    root->object.display();
  
  return 1;
}
