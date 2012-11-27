#ifndef USERINPUT_H_INCLUDED
#define USERINPUT_H_INCLUDED
#include <string>
#include "game.h"

using namespace std;

class userInput
{
    public:

    string& userName()
    {
        return input;
    }

    private:

    string input;
};

#endif // USERINPUT_H_INCLUDED
