//DATA_STRUCTURES.tpp
#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
/*
Here is where I put in my DLL and Node classes.  I have a bunch of wrapper functions for my DLL so 
that recursion is possible.  I have getters and setters for my Node data.  Additionally,  I have
a copy constructor for both my DLL and my Node classes.

*/
template <typename T>
class Node
{
    public:
        Node();
        Node(const T & source);
        Node(const Node<T> * source);
        Node<T>*& get_next();
        Node<T>*& get_prev();

        int set_next(Node<T> * new_next); //Ended up not using these and instead used getters to reset data
        int set_prev(Node<T> * new_prev); 
        T get_data() const;
        
        /*
        Below are my operators.  I have been trying to enable them to be able to traverse but I have had very little success
        I have had to resort to using getters for next and prev to avoid seg faults
        */
        Node<T>* operator+(int num);
        Node<T>* operator+=(int num);
        Node<T>* operator-=(int num);


    private:
        T data;
        Node<T> * next;
        Node<T> * prev;
};

template <typename T>
class DLL
{
    public:
        DLL();
        ~DLL();
        DLL & operator=(const DLL & to_copy); //Implemented
        DLL(const DLL<T> & source); //Implemented
        int insert(const T & new_data); //Implemented
        int display() const; //Implemented
        int remove(const T & to_remove);
        int remove_all(); 
        bool retrieve(const T & to_get);
    private:
        Node<T> * head;
        int display(Node<T> * current) const; //I had to pass by pointer and not by reference because the compiler gave me errors
        int remove(const T & to_remove, Node<T> *& head); //Work in Progress
        int remove_all(Node<T> *& head); //Work in Progress
        bool retrieve(const T & to_get, Node<T> *& head); //Work in Progress
        //int insert(const T & new_data, Node<T> *& head); //Ended up not needing this.  I just inserted at the beginning.
        int copy(Node<T> *& dest, Node<T> * src, Node <T> * src_head); //Implemented
};


#include "data_structures.tpp"
#endif
