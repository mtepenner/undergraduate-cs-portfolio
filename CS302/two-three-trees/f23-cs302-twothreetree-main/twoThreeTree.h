//Matthew Penner
//My two three tree header file
//twoThreeTree.h
#ifndef TWOTHREETREE_H
#define TWOTHREETREE_H
#include "animal.h"

/*
I made the decision to use zero raw pointers for this assignment and make an attempt to only use
smart pointers.  As you can see, I am using a 2-3 tree, which has two unique_ptrs of type pet, and three
unique_ptrs of type node to allow traversal left, right and in the middle.  I have wrapper functions and
private main functions so that the client side can invoke insertion, deletion and removal.  
*/
//Creation of the node class
class node
{
  public:    
    node();
    node(unique_ptr<pet> d1, unique_ptr<pet> d2);
    unique_ptr<node> & getLeft();
    unique_ptr<node> & getRight();
    unique_ptr<node> & getCenter();
    unique_ptr<pet> & getFirst();
    unique_ptr<pet> & getSecond();
  private:
    unique_ptr<node> left;
    unique_ptr<node> center;
    unique_ptr<node> right;
    unique_ptr<pet> data1;
    unique_ptr<pet> data2;

};

//Creation of the two three tree
class twoThreeTree
{
  public:
    twoThreeTree();
    int insert(unique_ptr<pet> & toInsert);
    int removeAll();
    int displayAll();
  private:
    int insert(unique_ptr<pet> & toInsert, unique_ptr<node> & current);
    int displayAll(unique_ptr<node> & current);
    unique_ptr<node> root;
};



#endif