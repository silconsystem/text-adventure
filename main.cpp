/*
    The little console adventure, originally named JAM.
    by: Ben Keen/bigjimbeef

    code manipulations by: R.van Ardenne
    for studying C++ game design structures
    and for fun !!
*/

// System includes
#include <iostream>

// Game includes
#include "game.h"

using namespace std;

int main()
{
    // TODO: welcome sequence to be moved into function
    string name;
    cout << "What's your name ?" << endl;
    cin >> name;

    // Instructions and welcome message
    cout << "Welcome to the console adventure " << name << "!!" << endl;
    cout << "\n";
    cout << "The program accepts the following commands:\n";
    cout << "n(orth), w(est), e(ast), s(outh) to move" << endl;
    cout << "stats for your status" << endl;
    cout << "f(ight), flight, run for combat" << endl;
    cout << "r(est) to rest and restore" << endl;
    cout << "q(uit) to end the game" << endl;
    cout << "have fun !!" << endl;
    cout << "\n";

    // Main loop for the game.
    while ( Game::GetInstance().IsRunning() )
    {
        // Update the game.
        Game::GetInstance().Update();
    }

    return 0;
}
