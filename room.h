#ifndef D_ROOM_H
#define D_ROOM_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <string>

#include "enemy.h"

class Game;

class Room
{
    public: 
        Room();
        ~Room();

        void Init();

        void Update();

        inline bool Initialised() { return m_initialised; } 
        inline Enemy* GetEnemy() { return mp_enemy; }

        Enemy* SpawnNewEnemy();
    private:
        // Item* mp_item;
        Enemy* mp_enemy;

        bool m_initialised;
};

#endif
