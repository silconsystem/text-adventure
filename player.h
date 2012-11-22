#ifndef D_PLAYER_H
#define D_PLAYER_H

#include <iostream>
#include <sstream>

#include "world.h"
#include "room.h"
#include "enemy.h"

#include "item.h"

// Fwd declaration
class Game;

class Player
{
    public:
        Player(World* world);
        ~Player();

        void Update();

        inline int GetCurrentHealth() { return m_currentHealth; }
        inline int GetTotalHealth() { return m_totalHealth; }
        inline void AlterHealth(int delta) { m_currentHealth += delta; }

        inline int GetStrength() { return m_str; }
        inline int GetDexterity() { return m_dex; }

        inline Room* GetCurrentRoom() { return mp_currentRoom; }
        inline void SetCurrentRoom(Room* newRoom) { mp_currentRoom = newRoom; }

        inline int GetLevel() { return m_level; }
        std::string GetLevelProgress();
        int GetXpToLevel();

        void Attack(Enemy* enemy);

        void AwardXp(int xp);

        void Rest();

        bool AttemptRun();

    private:
        bool m_alive;
        int m_currentHealth;
        int m_totalHealth;

        World* mp_world;

        Room* mp_currentRoom;

        // STATS
        int m_dex;
        int m_str;

        static const int BASE_TO_HIT = 60;

        int m_level;
        int m_xpThisLevel;

        static const int XP_TO_LEVEL_SCALAR = 10;

        void BeginResting(int hours);

        // Hehehe.. rubbish.
        static const int NUM_ITEMS = 6;
        Item* m_items[NUM_ITEMS];
        enum itemPositions
        {
            head = 0,
            chest,
            legs,
            gloves,
            boots,
            weapon
        };

        // TODO: so many things. For one.. inventory.
};

#endif
