#include "game.h"

Game::Game() :
    b_running(true),
    mp_player(0),
    m_inCombat(false),
    m_playerTurn(true)
{
    mp_world = new World();

    mp_player = new Player(mp_world);

    // Seed the random number generator.
    srand(time(NULL));
}

void Game::Update()
{
    if ( !m_inCombat )
    {
        WhatShallWeDo();
    }
    else
    {
        ProcessCombat();
    }

    mp_player->Update();
}

std::vector<std::string> getStrings(std::string input)
{
    std::string bit = "";
    std::vector<std::string> output;

    // NO TIME JUST HACK IT
    input += ' ';

    for(std::string::iterator it = input.begin(); it != input.end(); ++it) 
    {
        char thisChar = *it;

        if ( thisChar != ' ' && it != input.end() ) {
            bit += thisChar;
        }
        else {
            output.push_back(bit);
            bit = "";
        }
    }

    return output;
}

void Game::MovePlayer(std::string direction)
{
    direction = direction.substr(0,1);
    
    // Get current room indices.
    std::vector<int> xyPos = mp_world->GetRoomXY(mp_player->GetCurrentRoom());
    int x = xyPos[0];
    int y = xyPos[1];
    
    if ( direction == "n" )
    {
        y++;
    }
    else if ( direction == "e" )
    {
        x++;
    }
    else if ( direction == "s" )
    {
        y--;
    }
    else if ( direction == "w" )
    {
        x--;
    }


    std::cout << "You've moved. You're now at: [" << x << ", " << y << "] \n";

    Room* newRoom = mp_world->GetRoom(x,y);
    mp_player->SetCurrentRoom(newRoom);

    if ( !newRoom->Initialised() )
    {
        // Initialise the room.
        newRoom->Init();
    }
    else
    {
        newRoom->Update();
    }
}

bool Game::DirectionAvailable(std::string direction)
{
    direction = direction.substr(0,1);

    // Get all available directions
    bool available[4];
    for ( int i = 0; i < 4; ++i ) 
    {
        available[i] = 0;
    }
    std::vector<int> xyPos = mp_world->GetRoomXY(mp_player->GetCurrentRoom());
    int x = xyPos[0];
    int y = xyPos[1];
    
    // top
    available[0] = ( y < mp_world->GetDimension() - 1);
    // right
    available[1] = ( x < mp_world->GetDimension() - 1);
    // bottom
    available[2] = ( y > 0 );
    // left
    available[3] = ( x > 0 );
    
    if ( direction == "n" )
    {
        return available[0];
    }
    else if ( direction == "e" )
    {
        return available[1];
    }
    else if ( direction == "s" )
    {
        return available[2];
    }
    else if ( direction == "w" )
    {
        return available[3];
    }
    
    return false;
}

void Game::WhatShallWeDo()
{
    bool bDone = false;
    
    while ( !bDone )
    {
        std::cout << "> ";

        char playerChoice[256];
        std::cin.getline(playerChoice, 256);
        std::string choiceString(playerChoice);

        std::vector<std::string> parts;

        // BENK
        parts = getStrings(choiceString);

        // Split the parts into:
        //     action
        //     target
        std::string action = parts.at(0);

        bDone = true;

        // Ensure we're using lower case.
        std::string strAction = "";
        for(std::string::iterator it = action.begin(); it != action.end(); ++it) 
        {
            char thisChar = *it;
            thisChar = tolower(thisChar);
            strAction += thisChar;
        }
        action = strAction;

        if ( 
            action == "n" || action == "north" ||
            action == "e" || action == "east" ||
            action == "s" || action == "south" ||
            action == "w" || action == "west" 
            )
        {
            // Handle direction choices!
            if ( DirectionAvailable(action) ) 
            {
                MovePlayer(action);
            }
            else
            {
                std::cout << "There's no exit that way!\n";
            }
        }
        /*else if ( action == "look" )
        {
            std::cout << "You chose to " << action << "\n";
        }
        else if ( action == "get" )
        {
            std::cout << "You chose to " << action << "\n";
        }
        else if ( action == "use" )
        {
            std::cout << "You chose to " << action << "\n";
        }*/
        else if ( action == "fight" || action == "f" )
        {
            Enemy* enemy = mp_player->GetCurrentRoom()->GetEnemy();
            if ( enemy != NULL && enemy->Alive() )
            {
                std::cout << "You decide to pick a fight with the " << enemy->GetName() << "\n";
                m_inCombat = true;
            }
        }
        else if ( action == "rest" || action == "r" )
        {
            mp_player->Rest();
        }
        else if ( action == "stat" || action == "stats" || action == "status" )
        {
            std::cout << "\n----------------------------------------------------------------\n";
            std::cout << "You are currently level " << mp_player->GetLevel() 
                << " with " << mp_player->GetLevelProgress() << " to level " << mp_player->GetLevel() + 1 << ".\n";

            std::cout << "\n";
            std::cout << "HP:\t\t" << mp_player->GetCurrentHealth() << "/" << mp_player->GetTotalHealth() << "\n";
            std::cout << "Strength:\t" << mp_player->GetStrength() << "\n";
            std::cout << "Dexterity:\t" << mp_player->GetDexterity() << "\n";
        }
        else if ( action == "quit" || action == "q" )
        {
            b_running = false;
            std::cout << "Goodbye!\n\n";
        }
        else
        {
            bDone = false;
            std::cout << "Try again. Accepted commands are n(orth), e(ast), s(outh), w(est), stats, f(ight), r(est), q(uit).\n";
        }
    } // while
}

void Game::ProcessCombat()
{
    // Whose turn is it?
    if ( m_playerTurn )
    {
        // Prompt for input:
        bool bDone = false;

        while ( !bDone )
        {
            bDone = true;

            std::cout << "> ";

            char playerChoice[256];
            std::cin.getline(playerChoice, 256);
            std::string choiceString(playerChoice);

            // Ensure we're using lower case.
            std::string strAction = "";
            for(std::string::iterator it = choiceString.begin(); it != choiceString.end(); ++it) 
            {
                char thisChar = *it;
                thisChar = tolower(thisChar);
                strAction += thisChar;
            }
            choiceString = strAction;

            if ( choiceString == "fight" || choiceString == "f" )
            {
                Enemy* enemy = mp_player->GetCurrentRoom()->GetEnemy();
                if ( enemy != NULL && enemy->Alive() )
                {
                    // Attaaaaaaaack!
                    mp_player->Attack(enemy);

                    if ( enemy->GetHealth() <= 0 )
                    {
                        std::cout << "You have slain the " << enemy->GetName() << ". Songs shall be sung of your valour this day.\n";

                        // Winner winner chicken dinner.
                        enemy->SetAlive(false);

                        int xp = enemy->GetXpReward();
                        mp_player->AwardXp(xp);

                        std::cout << "You gained " << xp << "xp. You need "
                            << mp_player->GetXpToLevel() << " to level " << mp_player->GetLevel() + 1 << ".\n";

                        m_inCombat = false;
                        return;
                    }
                }
            }
            else if ( choiceString == "flight" || choiceString == "run" )
            {
                if ( mp_player->AttemptRun() )
                {
                    std::cout << "You ran away, like a small dog faced with a much larger dog. Still, at least you got away.\n";
                    m_inCombat = false;
                }
                else
                {
                    std::cout << "You turned you tail and fled, but the " << mp_player->GetCurrentRoom()->GetEnemy()->GetName() << " caught up to you.\n";
                    m_playerTurn = false;
                }
            }
            else if ( choiceString == "quit" )
            {
                b_running = false;
                std::cout << "Why you yeller-bellied....\n\n";
            }
            else
            {
                std::cout << "You are in combat! The only options now are fight or flight!\n";
                bDone = false;
            }
        }
        
        m_playerTurn = false;
    }
    else
    {
        // Pause that shit.
        sleep(1);

        Enemy* attacker = mp_player->GetCurrentRoom()->GetEnemy();

        if ( attacker != NULL )
        {
            attacker->AttackPlayer();

            if ( mp_player->GetCurrentHealth() <= 0 )
            {
                std::cout << "Joseph Gordon Levitt sidles over to your corpse and looks upon it with a sombre expression: ";

                std::cout << "\n\n\"Hey. Listen. It looks like your saga has come to an end. I guess that " 
                    << attacker->GetName() << " was just a step too far. Better luck next time, amigo.\"\n";

                std::cout << "\n\nGAME OVER\n\n";

                b_running = false;
            }
        }

        m_playerTurn = true;
    }

}
