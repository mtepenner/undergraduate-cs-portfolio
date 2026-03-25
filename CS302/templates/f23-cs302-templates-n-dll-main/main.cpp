

#include "interface.h"
using namespace std;

/*
This is as simple as I think it can get for a main method.  The Interface class does all the work so main is nowhere near as
complex as it was in Program 1.
*/
int main()
{
    cout << "----------------------------WELCOME TO THE PORTLAND ACTIVITY CENTER----------------------------\n\n";
    
    Interface myinterface;
    
    myinterface.main_menu();

	return 0;
}
