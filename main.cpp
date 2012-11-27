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
    input uData;
    uData.userName();
    uData.userLocation();

    cout << "Let the adventure begin !!" << endl << endl;

    // Main loop for the game.
    while ( Game::GetInstance().IsRunning() )
    {
        // Update the game.
        Game::GetInstance().Update();
    }

    return 0;
}
