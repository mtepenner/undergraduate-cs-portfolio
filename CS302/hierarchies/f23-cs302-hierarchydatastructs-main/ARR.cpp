/*
This is the CPP file dedicated to my array of linear linked lists, which
I am using for my Artist class.  From my understanding what this 
implementation is will be similar to a hash table except there is
no hash function.  That concept sounded very straightforward to me.



*/


#include "data_structures.h"

//Artist Node Constructors
ArtistNode::ArtistNode(): next(nullptr) {}

ArtistNode::ArtistNode(const ArtistNode & source): Artist(source), next(nullptr) {} //copy constructor
 
ArtistNode::ArtistNode(const Artist & new_art): Artist(new_art), next(nullptr) {} //constructor that takes in an artist

ArtistNode *& ArtistNode::get_next() //points to the next node
{
	return next;
}

int ArtistNode::set_next(ArtistNode * new_next) //sets up a new node
{
	next = new_next;
	return 1;
}



ARR::ARR(int size): ARR_table(nullptr) //default constructor for the ARR
{
	ARR_table = new ArtistNode * [size];
	for(int i = 0; i < size; ++i)
		ARR_table[i] = nullptr;

	ARR_size = size;	

}

ARR::~ARR() //destructor
{

}

int ARR::remove_all() //wrapper function for remove all
{
	int i = 0;
	
	if(i >= ARR_size || !ARR_table[i]) return 0;
	return remove_all(i, ARR_table[i]);
}

int ARR::remove_all(int i, ArtistNode *& ptr) //recursive function that traverses ARR
{
	if(!ptr) 
	{
		++i;
		if(i >= ARR_size) return 0;
		return remove_all(i, ARR_table[i]);
	}
	ArtistNode * temp = ptr->get_next();
	delete ptr;
	ptr = temp;
	return remove_all(i, ptr);

		

}


int ARR::display() const//wrapper function for remove all
{
	int i = 0;
	
	if(i >= ARR_size || !ARR_table[i]) return 0;
	return display(i, ARR_table[i]);
}

int ARR::display(int i, ArtistNode *& ptr) const //recursive function that traverses ARR
{
	if(!ptr) 
	{
		++i;
		if(i >= ARR_size) return 0;
		return display(i, ARR_table[i]);
	}
  	ptr->display();
	ptr = ptr->get_next();

	return display(i, ptr);

		

}


int ARR::copy(ArtistNode *& dest, ArtistNode * src) //copy function for the assignment operator
{
	
	if(src == nullptr) 
	{
		dest = nullptr;
		return 0;
	}
	
	else
	{
	
		dest = new ArtistNode(*src);
		copy(dest->get_next(), src->get_next());
	}
	
	return 1;



}

ARR & ARR::operator=(const ARR & source) //assignment operator
{
	
	//self assignment?
	if(this == &source)
	return *this;
	//list deallocated
	remove_all();
	//copy
	for(int i = 0; i < ARR_size; ++i)
	{
		copy(ARR_table[i], source.ARR_table[i]);
	}
	//current object:
	return *this;
}
int ARR::counter(ArtistNode *& ptr) //counts the number of nodes
{
	if(!ptr)
		return 0;
	else
		return 1 + counter(ptr->get_next());
}
//removal wrapper function
int ARR::remove(char *& a_name)
{
	int i = 0;
	if(!ARR_table[i]) return 0;

	return remove(i, a_name, ARR_table[i]);

}
//recursive removal function
int ARR::remove(int i, char *& a_name, ArtistNode *& ptr)
{
	if(!ptr) 
	{
		++i;
		return remove(i, a_name, ARR_table[i]);
	}

	if(!ARR_table[i]) return 0;
	if(ptr->compare_name(a_name) == true)
	{
		
		delete ptr;
		ptr = nullptr;
		
	}
	return 1 + remove(i, a_name, ptr->get_next());

}
//retrieval wrapper function
int ARR::retrieve(char *& a_name) const
{
	int i = 0;
	if(!ARR_table[i] || i >= ARR_size) return 0;

	return retrieve(i, a_name, ARR_table[i]);

}
//recursive retrieval function
int ARR::retrieve(int i, char *& a_name, ArtistNode *& ptr) const
{
	if(!ptr) 
	{
		++i;
		if (i >= ARR_size) return 0;

		if(!ARR_table[i]) return 0;
		return retrieve(i, a_name, ARR_table[i]);
		
	}
	int count = 0;
	if(ptr->compare_name(a_name) == true)
	{
		
		ptr->display();
		count = 1;
	}
	return count + retrieve(i, a_name, ptr->get_next());

}

//insertion function for array of linear linked list
int ARR::insert(const Artist & new_art) 
{
  
  int j = 0;
  for(int i = 0; i < ARR_size; ++i)
  {
  	  int count = counter(ARR_table[i]);
	  if(count >= 25){
	  	j = i;
		i = ARR_size;
	  }
  }
  return insert(new_art, ARR_table[j]);
  
}
//recursive implementation
int ARR::insert(const Artist & new_art, ArtistNode *& current) 
{

  if(!current)
  {
	current = new ArtistNode(new_art);
	current->set_next(nullptr);
	return 1;
  }

  return insert(new_art, current->get_next());
}


