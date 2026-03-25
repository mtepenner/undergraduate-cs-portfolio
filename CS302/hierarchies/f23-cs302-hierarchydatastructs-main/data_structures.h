/*
This file contains all the prototypes for my data structures. I am using a
CLL for my Actor Class and an ARR for my Artist Class.  Cosplayers will all
be stored in a vector.

*/
#include "celebrities.h"
#pragma once
class ArtistNode: public Artist //node for the artist
{
	public:
		ArtistNode();
		ArtistNode(const ArtistNode & source);
		ArtistNode(const Artist & new_art);
		int set_next(ArtistNode * new_next);
		ArtistNode *& get_next();

	private:
		ArtistNode * next;

};

class ActorNode: public Actor //node for the actor
{
	public:
		ActorNode();
		ActorNode(const ActorNode & source);
		ActorNode(const Actor & new_act);
		int set_next(ActorNode * new_next);
		ActorNode *& get_next();
	private:
		ActorNode * next;

};

class CLL //mostly implemented.  
{
	public:
		CLL();
		CLL(const CLL & to_copy);
		~CLL();
		CLL & operator=(const CLL & source);
		int insert(const Actor & new_act);
		int retrieve(char *& name);
		int retrieve_autocost(char *& a_name, int a_time);
		int retrieve_acclaimed(char *& a_name);
		int retrieve_slf(char *& a_name);
		
		int remove(char *& name); //this still has issues.  Was unable to resolve it
		int display() const;
		int remove_all();
	private:
		ActorNode * rear;
		int retrieve(char *& name, ActorNode *& rear);
		int retrieve_acclaimed(char *& a_name, ActorNode *& rear);
		int retrieve_autocost(char *& a_name, int a_time, ActorNode *& rear);
		int retrieve_slf(char *& a_name, ActorNode *& rear);
		
		int remove(char *& name, ActorNode *& current, ActorNode *& prev);	
		int remove_all(ActorNode *& current);
		int display(ActorNode *& current) const;
		int copy(ActorNode *& dest, ActorNode * src, ActorNode * src_rear);
};


class ARR //array of linear linked lists work in progress
{
	public:
		ARR(int size=3); //Constructor
		~ARR(void); //Destructor
		ARR & operator=(const ARR & source);
		int display() const;
		int retrieve(char *& a_name) const;
		int counter(ArtistNode *& ptr);
		int remove(char *& a_name);
		int remove_all();
		int insert(const Artist & new_art);
	private:
		ArtistNode ** ARR_table; //dynamically allocated array of head pointers
		int ARR_size;
		int remove_all(int i, ArtistNode *& ptr);
    		int insert(const Artist & new_art, ArtistNode *& current);
    		int display(int i, ArtistNode *& ptr) const;
		int copy(ArtistNode *& dest, ArtistNode * src);
		int remove(int i, char *& a_name, ArtistNode *& ptr);
		int retrieve(int i, char *& a_name, ArtistNode *& ptr) const;

};

