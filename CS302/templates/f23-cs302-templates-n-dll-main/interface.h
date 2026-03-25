#pragma once
#include "data_structures.h"
#include "hierarchy.h"
#include <list>
#include <array>

/*
Here is my Interface class, where I have functions that will enable the client to interact with each
activity type and be able to call on the different methods associated.  There will be calls made in
each of the functions listed below to DLL functions.
*/



class Interface 
{
    public:
        Interface(); //Constructor
        ~Interface(); //Destructor
        int main_menu(); //The main interface
        int play_game(Game & game); //Function to play the guessing game and return a statement if the guess was false
        
        int showFailedGuesses(); //Would add the failed guess to a list of integers
        int populateTicketPrices(); //Array filled with ticket prices
        int showTicketPrices(int i); //Ticket prices displayed
    private:
        DLL<Tour> TourList;
        DLL<Game> GameList;
        DLL<Concert> ConcertList;
        list<int> failedGuesses;
        array<string, 3> concertTicketPrices;
        

};


