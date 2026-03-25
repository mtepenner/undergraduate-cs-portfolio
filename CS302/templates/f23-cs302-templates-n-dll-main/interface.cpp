
#include "interface.h"

using namespace std;
/*
   Here is my fifth main class functions.  This allows my main method to be simplified to just calling the main_menu, 
   which in turn will call other functions within Interface.  
 */

Interface::Interface() {}
Interface::~Interface() {}

int Interface::populateTicketPrices() //Commented out because it does not work
{
    concertTicketPrices[0] = "Base Price: $25";
    concertTicketPrices[1] = "Upgraded Price: $50";
    concertTicketPrices[2] = "Platinum Price: $75";
    return 1;
}

int Interface::showTicketPrices(int i)
{
    cout << concertTicketPrices[0] << endl << concertTicketPrices[1] << endl << concertTicketPrices[2] << endl << endl;
    return 1;
}

int Interface::main_menu() //Main method
{
    Concert concert;
    Game game;
    Tour tour;
    int selection;
    cout << "PLEASE SELECT FROM THE FOLLOWING OPTIONS: " << endl;
    cout << "(1) Build a game\n(2) Take a tour\n(3) Attend a concert" 
        << "\n(4) See concert ticket prices" << "\n(5) Display tours" 
        << "\n(6) Display games" << "\n(7) Display concerts" 
        << "\n(8) Remove everything" << "\n(9) Remove a specific tour"
        << "\n(10) Remove a specific concert" << "\n(11) Play a simple game" 
        << "\n(12) Show failed guesses" << "\n(13) Find a specific tour"
        << "\n(14) Find a specific concert" << "\n(0) Quit" << endl;
    cin >> selection;
    cin.ignore(100, '\n');

    if(selection == 1) 
    {
        cin >> game; 
        GameList.insert(game);

        return main_menu();
    }
    if(selection == 2) 
    {
        cin >> tour;
        TourList.insert(tour);

        return main_menu();
    }
    if(selection == 3) 
    {
        cin >> concert;
        ConcertList.insert(concert);

        return main_menu();
    }
    if(selection == 4) 
    {
        populateTicketPrices();
        int i = 0;
        showTicketPrices(i);

        return main_menu();
    }
    if(selection == 5)
    {
        TourList.display();

        return main_menu();
    }
    if(selection == 6)
    {
        GameList.display();

        return main_menu();
    }
    if(selection == 7)
    {
        ConcertList.display();

        return main_menu();
    }

    if(selection == 8)
    {
        TourList.remove_all();
        GameList.remove_all();
        ConcertList.remove_all();

        return main_menu();
    }
    if(selection == 9)
    {
        Tour a_tour;
        cout << "Please enter information about the tour you want gone: \n";
        cin >> a_tour;
        TourList.remove(a_tour);

        return main_menu();

    }

    if(selection == 10)
    {
        Concert a_concert;
        cout << "Please enter information about the concert you want gone: \n";
        cin >> a_concert;
        ConcertList.remove(a_concert);

        return main_menu();

    }


    if(selection == 11)
    {
        Game a_guess;

        cout << "I am thinking of a number between 1 and 10, can you guess that number?\n";

        cin >> a_guess;
        play_game(a_guess);

        return main_menu();
    }

    if(selection == 12)
    {
        for (list<int>::iterator it = failedGuesses.begin(); it != failedGuesses.end(); ++it)
        {
            cout << *it << endl;
        }

        return main_menu();

    }

    if(selection == 13)
    {
        Tour a_tour;
        cout << "Please enter information about the concert you want to find: \n";
        cin >> a_tour;
        TourList.retrieve(a_tour);

        return main_menu();

    }

    if(selection == 14)
    {
        Concert a_concert;
        cout << "Please enter information about the concert you want to find: \n";
        cin >> a_concert;
        ConcertList.retrieve(a_concert);

        return main_menu();

    }




    ConcertList.remove_all();
    TourList.remove_all();
    GameList.remove_all();


    return 1;    
}

int Interface::play_game(Game & game)
{   


    bool exists = GameList.retrieve(game);
    if(exists)
    {
        cout << "Congrats! You win the game" << endl;

    }
    else
    {
        cout << "Better luck next time" << endl;
        failedGuesses.push_back(game.get_guess());

    }
    return 1;
}
