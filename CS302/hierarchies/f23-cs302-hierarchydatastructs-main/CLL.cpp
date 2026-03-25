#include "celebrities.h"
#include "data_structures.h"

/*
This file is dedicated to the functions that are a part of my CLL data structure, which
is going to store information about different actors attending Comic Con.  I am basing
a lot of my code off of what was shown in Lab 3.  I am implementing wrapper functions
for all member functions that require traversal, which of course means recursion.

*/
/*********************************************************************************/
//Actor Node Constructors
ActorNode::ActorNode(): next(nullptr) {} //default constructor

//copy constructor
ActorNode::ActorNode(const ActorNode & source): Actor(source), next(nullptr) {}

//constructor that takes an actor object
ActorNode::ActorNode(const Actor & new_act): Actor(new_act), next(nullptr) {}

//a getter for the next pointer
ActorNode * & ActorNode::get_next()
{
	return next;
}

//a setter for the next pointer
int ActorNode::set_next(ActorNode * new_next)
{
	this->next = new_next;
	return 1;


}



//default constructor
CLL::CLL(): rear(nullptr) {}

//display wrapper function
int CLL::display() const
{
	if(!rear) return 0;
	
	ActorNode * current = rear->get_next();
	return display(current);
}

//display function that recursively iterates through CLL
int CLL::display(ActorNode *& current) const
{
  if(!rear) return 0;
	if(current == rear)
	{
		current->display();
		return 1;
	}
	
	current->display();
	current = current->get_next();
	return 1 + display(current);
	

}

//copy constructor for CLL
CLL::CLL(const CLL & to_copy): rear(nullptr)
{
	if(!to_copy.rear) return;
	copy (rear, to_copy.rear->get_next(), to_copy.rear);

}

//destructor for CLL
CLL::~CLL()
{
  remove_all();
}

//removal wrapper function
int CLL::remove(char *& name)
{
	 if(!rear) return -1; // return -1 if list is empty

   ActorNode * prev = rear;
   ActorNode * current = rear->get_next();

   // Special case for single node
   if(current == rear && strcmp(rear->get_name(), name) == 0)
   {
        delete rear;
        rear = nullptr;
        return 1;
   }

   return remove(name, current, prev);

}

//removal function that recursively iterates through CLL for specific pointer based on the name
int CLL::remove(char *& name, ActorNode *& current, ActorNode *& prev)
{
	
  // if we've gone full circle and haven't found the node
  if(current == rear && strcmp(current->get_name(), name) != 0)
  return 0;

  // yay node detected
  if(current->compare_name(name) == true)
  {
    

    // removes rear node
    if(current == rear)
    rear = prev;

    delete current;
    current = nullptr;
    return 1;
  }
  prev->set_next(current->get_next());
  // recursive call
  return remove(name, current->get_next(), current);



}

//function that removes every pointer, wrapper for it
int CLL::remove_all()
{
	if(!rear) return 0;
	ActorNode * current = rear->get_next();
	rear->set_next(nullptr);
	rear = nullptr;
	//cout << "First Breakpoint" << endl;
	return remove_all(current);

}	

//recursive function that removes every pointer in the CLL 
int CLL::remove_all(ActorNode *& current)
{
	if(!current) return 0;
	
	//cout << "Second Breakpoint" << endl; 
	ActorNode * next_node = current->get_next();
    if(next_node == current) // Check for self-loop
    {
        delete current;
        current = nullptr;
        return 1;
    }
    
	delete current;
	current = nullptr;

	
	
	//cout << "Third Breakpoint" << endl;
	return 1 + remove_all(next_node);

}

//copy function
int CLL::copy(ActorNode *& dest, ActorNode * src, ActorNode * src_rear)
{
	if(!src) return 0;
	ActorNode * temp = new ActorNode(*src);
	if(!dest)
	{
		temp->set_next(temp); //point to itself
		dest = temp;
	}
	else
	{
		temp->set_next(dest -> get_next());
		dest = temp;
	}
	if(src == src_rear)
	{
		rear = dest;
		return 1;
	}
	return 1 + copy(dest->get_next(), src->get_next(), src_rear);



}
//assignment operator
CLL & CLL::operator=(const CLL & source) 
{
	//check for self assignment
	if(this == &source)
	return *this;
	//deallocation of the existing list
	remove_all(rear);
	//perform the copy
	copy(rear, source.rear->get_next(), source.rear);
	//return current object:
	return *this;
}
//insert function
int CLL::insert(const Actor & new_act) 
{
    ActorNode * person = new ActorNode(new_act);
    if(!rear) //nothing in rear
    {
        rear = person; //time to create a new node
        rear->set_next(rear); //use the setter function to tie everything together
        return 1;
    }
    else //rear does exist
    {
        ActorNode * temp = rear->get_next(); //temp variable created
        rear->set_next(person); //setter function is used 
        person->set_next(temp); //setter is used
        rear = person; //set rear to person
        return 1;
    }
    return 0;
}

int CLL::retrieve(char *& a_name) //looks for a specific actor
{
	if(!rear) //there is nobody, comic con is a ghost town oooOOOOOOoooooo
	{
		cout << "There are no actors." << endl;
		return 0;
	}
	
	return retrieve(a_name, rear->get_next()); //wrapper function calls main recursive function
}
int CLL::retrieve(char *& a_name, ActorNode *& rear)
{
	
	if(rear->compare_name(a_name)) //yippee, the actor is found
	{
		cout << "Yes. This actor exists" << endl;
		rear->display();
		return 1;
	}

	if(rear == this->rear) //we are at the end of the line, no luck finding the actor
	{
		
		return 0;
	}
	return retrieve(a_name, rear->get_next()); //iterate recursively
	

}

//similar to retrieve but displays the cost for an autograph
int CLL::retrieve_autocost(char *& a_name, int a_time)
{
	if(!rear)
	{
		cout << "There are no actors." << endl;
		return 0;
	}
	
	return retrieve_autocost(a_name, a_time, rear->get_next());

}

int CLL::retrieve_autocost(char *& a_name, int a_time, ActorNode *& rear)
{
	if(rear->compare_name(a_name))
	{
		rear->schedule_autograph(a_time);
		return 1;
	}

	if(rear == this->rear)
	{
		cout << "There are no actors." << endl;
		return 0;
	}
	return retrieve_autocost(a_name, a_time, rear->get_next());
	
}

//similar to retrieve but focuses on how many awards a celebrity obtained
int CLL::retrieve_acclaimed(char *& a_name)
{
	if(!rear)
	{
		cout << "There are no actors." << endl;
		return 0;
	}
	
	return retrieve_acclaimed(a_name, rear->get_next());
}
int CLL::retrieve_acclaimed(char *& a_name, ActorNode *& rear)
{
	if(rear->compare_name(a_name))
	{
		cout << "Yes. This actor exists" << endl;
		rear->acclaimed_actor();
		return 1;
	}

	if(rear == this->rear)
	{
		cout << "There are no actors." << endl;
		return 0;
	}
	return retrieve_acclaimed(a_name, rear->get_next());
	
	

}

//retrieves info about if this celebrity allows selfies
int CLL::retrieve_slf(char *& a_name)
{
	if(!rear)
	{
		cout << "There are no actors." << endl;
		return 0;
	}
	
	return retrieve_slf(a_name, rear->get_next());
}
int CLL::retrieve_slf(char *& a_name, ActorNode *& rear)
{
	
	if(rear->compare_name(a_name))
	{
		cout << "Yes. This actor exists" << endl;
		rear->is_selfie();
		return 1;
	}

	if(rear == this->rear)
	{
		
		return 0;
	}
	return retrieve_slf(a_name, rear->get_next());
	
	

}

//this is it for my CLL functions




















