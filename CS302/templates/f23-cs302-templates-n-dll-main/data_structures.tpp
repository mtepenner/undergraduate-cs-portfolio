//DATA_STRUCTURES.tpp
#ifndef DATA_STRUCTURES_TPP
#define DATA_STRUCTURES_TPP
#include <iostream>



using namespace std;
//START OF CLASS NODE

template <typename T>
Node<T>::Node(): next(nullptr), prev(nullptr) {}

template <typename T>
Node<T>::Node(const T & source): data(source), next(nullptr), prev(nullptr) {}

    template <typename T>
Node<T>::Node(const Node<T> * source) 
{
    data = source->data;
    next = nullptr;
    prev = nullptr;

}


    template <typename T>
Node<T> *& Node<T>::get_prev() 
{
    return prev;
}

    template <typename T>
Node<T> *& Node<T>::get_next() 
{
    return next;
}


template <typename T>
T Node<T>::get_data() const
{
    return data;
}

    template <typename T>
Node<T>* Node<T>::operator+(int num)
{
    //Node<T>* temp = new Node<T>(this);
    Node<T>* temp = this;


    for(int i = 0; i < num && temp != nullptr; ++i)
    {

        temp = temp->get_next();


    }
    //*this = *temp;
    //return *this;
    return temp;
}
    template <typename T>
Node<T>* Node<T>::operator-=(int num)
{
    Node<T> * temp = this;
    for(int i = 0; i < num && temp != nullptr; ++i)
    {
        temp = temp->get_prev();

    }
    return temp;
}

template <typename T>

Node<T>* Node<T>::operator+=(int num)
{
    Node<T>* temp = this;

    for(int i = 0; i < num && temp != nullptr; ++i)
    {

        temp = temp->get_next();


    }
    return temp;
}


//End of class Node

//START OF CLASS DLL
template <typename T>
DLL<T>::DLL(): head(nullptr) {}

template <typename T>
DLL<T>::~DLL() 
{
    remove_all(head);
}


    template <typename T>
int DLL<T>::insert(const T & new_data)
{ 

    if(!head)
    {
        head = new Node<T>(new_data);
        head->get_next() = head->get_prev() = nullptr;
        return 1;

    }
    if(head)
    {
        Node<T> * temp = head;
        head = new Node<T>(new_data);
        head->get_prev() = nullptr;
        temp->get_prev() = head;
        head->get_next() = temp;


        return 1;
    }
    return 0;

}


template <typename T>
int DLL<T>::display() const
{
    if(!head) return 0;
    return display(head);
}

template <typename T>
int DLL<T>::display(Node<T> * current) const
{
    if(!current) return 0;
    cout << current->get_data();
    //current += 1;
    //if(current) return display(current);
    //else return 0;
    current = *current + 1;
    return display(current);
    //return 1 + display(current->get_next());
}
    template <typename T>
int DLL<T>::remove(const T & to_remove)
{
    if(!head) return 0;
    return remove(to_remove, head);
}
    template <typename T>
int DLL<T>::remove(const T & to_remove, Node<T> *& current)
{
    if(!current) return 0;
    if(current->get_data() == to_remove)
    {
      
        Node<T> * temp = current->get_next();
        delete current;
        current = temp;
        return 1;

    }
    current = current + 1;
    return remove(to_remove, current);

}
    template <typename T>
int DLL<T>::remove_all()
{
    if(!head) return 0;
    if(!head->get_next())
    {
        delete head;
        head = nullptr;
        return 1;
    }
    
    return remove_all(head);

}
    template <typename T>
int DLL<T>::remove_all(Node<T> *& current)
{
    if(!current) return 0;
    Node<T>* temp = current->get_next();
    delete current;
    current = nullptr;
    current = temp;
    return remove_all(current);

}


    template <typename T>
bool DLL<T>::retrieve(const T & to_get)
{
    if(!head) return false;
    return retrieve(to_get, head);

}

    template <typename T>
bool DLL<T>::retrieve(const T & to_get, Node<T> *& current)
{
    if(!current) 
    {
        cout << "No matches!\n";
        return false;
    }
    if(current->get_data() == to_get)
    {
        return true;
    }
    return retrieve(to_get, current->get_next());

}
    template <typename T>
int DLL<T>::copy(Node<T> *& dest, Node<T> * src, Node<T> * src_head)
{
    if(!src) return 0;
    Node<T> * temp = new Node<T>(*src);
    if(!dest)
    {
        temp->get_next = temp;
        temp->get_prev = temp;
        dest = temp;
    }
    else
    {
        temp->get_next() = dest;
        temp->get_prev() = dest->get_prev();
        dest->get_prev()->get_next() = temp;
        dest->get_prev() = temp;
        dest = temp;
    }

    if(src == src_head)
    {
        head = dest;
        return 1;
    }

    return 1 + copy(dest->get_next(), src->get_next(), src_head);
}
    template <typename T>
DLL<T> & DLL<T>::operator=(const DLL<T> & source)
{
    if(this == & source)
        return *this;
    remove_all(head);
    copy(head, source.head->get_next(), source.head);
    return *this;

}
#endif


