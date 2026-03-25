//Matthew Penner
//My two three tree cpp file
//twoThreeTree.cpp
#ifndef TWOTHREETREE_CPP
#define TWOTHREETREE_CPP
#include "twoThreeTree.h"

/*
I have a series of getters below for each private data member of the node class.  My insertion function does not 
fully work, and as of submission it still gives me errors.  From what I could tell, my removal and display seem to 
be working just fine.
*/
/*MY NODE CLASS FUNCTIONS*/
node::node() {}

node::node(unique_ptr<pet> d1, unique_ptr<pet> d2): data1(move(d1)), data2(move(d2)) {}

unique_ptr<node> & node::getLeft() 
{
  return left;
}
unique_ptr<node> & node::getRight() 
{
  return right;
}
unique_ptr<node> & node::getCenter() 
{
  return center;
}
unique_ptr<pet> & node::getFirst() 
{
  return data1;
}
unique_ptr<pet> & node::getSecond() 
{
  return data2;
}

/*MY TWOTHREETREE CLASS FUNCTIONS*/
twoThreeTree::twoThreeTree() 
{}

int twoThreeTree::insert(unique_ptr<pet> & toInsert) 
{
  if(!root)
  {
    root = make_unique<node>();
    if (typeid(*toInsert) == typeid(bunny)) {
    root->getFirst() = make_unique<bunny>(*(dynamic_cast<bunny*>(toInsert.get())));
    } else if (typeid(*toInsert) == typeid(cat)) {
        root->getFirst() = make_unique<cat>(*(dynamic_cast<cat*>(toInsert.get())));
    } else if (typeid(*toInsert) == typeid(dog)) {
        root->getFirst() = make_unique<dog>(*(dynamic_cast<dog*>(toInsert.get())));
    }
    return 1;
  
  }
  return insert(toInsert, root);
}

int twoThreeTree::removeAll() 
{
  if(!root) return 0;
  root.reset();
  return 1;
}

int twoThreeTree::displayAll() 
{
  if(!root) return 0;
  return displayAll(root);
}

int twoThreeTree::insert(unique_ptr<pet> & toInsert, unique_ptr<node> & current) 
{
 
  if(!current)
  {
    current = make_unique<node>();
    
    if (typeid(*toInsert) == typeid(bunny)) {
    current->getFirst() = make_unique<bunny>(*(dynamic_cast<bunny*>(toInsert.get())));
    } else if (typeid(*toInsert) == typeid(cat)) {
        current->getFirst() = make_unique<cat>(*(dynamic_cast<cat*>(toInsert.get())));
    } else if (typeid(*toInsert) == typeid(dog)) {
        current->getFirst() = make_unique<dog>(*(dynamic_cast<dog*>(toInsert.get())));
    }
    return 1;
  }

  if(!current->getSecond())
  {
    if (typeid(*toInsert) == typeid(bunny)) {
    current->getSecond() = make_unique<bunny>(*(dynamic_cast<bunny*>(toInsert.get())));
    } else if (typeid(*toInsert) == typeid(cat)) {
        current->getSecond() = make_unique<cat>(*(dynamic_cast<cat*>(toInsert.get())));
    } else if (typeid(*toInsert) == typeid(dog)) {
        current->getSecond() = make_unique<dog>(*(dynamic_cast<dog*>(toInsert.get())));
    }
    return 1;
  }

  if(current->getSecond())
  {
    if (!current->getLeft()) {
      return insert(toInsert, current->getLeft());  
    } 
    else if (!current->getRight()){
    
      return insert(toInsert, current->getRight());
    } 
    else {
      return insert(toInsert, current->getCenter());
    }
  
  } 
  
  
  
  return 1;
}

int twoThreeTree::displayAll(unique_ptr<node> & current)
{
  if (!current)
    return 1;


  if (current->getFirst() != nullptr)
    current->getFirst()->display();
  if (current->getSecond() != nullptr)
    current->getSecond()->display();

 
  displayAll(current->getLeft());
  displayAll(current->getCenter());
  displayAll(current->getRight());

  return 1;
}

#endif