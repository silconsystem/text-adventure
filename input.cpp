/*
    get user input
*/
#include "game.h"
#include "input.h"

using namespace std;

input::input()
{
    // Constructor
    cout << "Welcome to the little console adventure " << endl << endl;
    cout << "To travel use: n(orth), s(outh), e(ast), w(est)" << endl;
    cout << "To fight  use: f(ight), flight or run" << endl;
    cout << "for your status use: stats" << endl << endl;

}

input::~input()
{
    // Destructor
    // still empty
}

// get userdata
string* input::userName()
{
    string name;

    cout << "Please enter your name: ";
    getline(cin, name);

    cout << "Welcome " << name << endl;

    return 0;
}

string* input::userLocation()
{
    string location;

    cout << "Please enter your location: ";
    getline(cin, location);

    cout << "You are from: " << location << endl << endl;

    return 0;
}
