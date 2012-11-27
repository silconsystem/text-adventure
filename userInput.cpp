/*
    userInput script

*/
#include "game.h"

using namespace std;

// get the userName
string userName()
{
    string input = "";

    cout << "Please enter your name: ";
    getline(cin, input);
    cout << "You entered " << input << endl;
    return input;
}
