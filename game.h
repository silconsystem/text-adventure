#ifndef D_GAME_H
#define D_GAME_H

#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <cctype>
#include <string>
#include <sstream>

#include "player.h"
#include "world.h"
#include "input.h"

// Game is a singleton because there's only one!

class Game
{
    public:
        static Game& GetInstance()
        {
            static Game instance;
            return instance;
        }

        void Update();

        inline bool IsRunning() { return b_running; }
        inline Player* GetPlayer() { return mp_player; }

        inline void StartCombat() { m_inCombat = true; }
        inline void SurpriseAttack() { m_playerTurn = false; }

    private:
        Game();

        Game(Game const&);           // Don't Implement
        void operator=(Game const&); // Don't implement

        bool b_running;
        bool m_inCombat;
        bool m_playerTurn;
        // World instance.
        World* mp_world;

        // Player instance
        Player* mp_player;

        void ProcessCombat();
        void WhatShallWeDo();
        bool DirectionAvailable(std::string direction);
        void MovePlayer(std::string direction);
};

#endif
