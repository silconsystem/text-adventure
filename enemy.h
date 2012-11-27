#ifndef D_ENEMY_H
#define D_ENEMY_H

#include <string>
#include <cstdlib>
#include <time.h>
#include <iostream>

class Game;

class Enemy
{
    public:
        Enemy();
        ~Enemy();

        inline std::string GetName() { return m_name; }
        inline int GetLevel() { return m_level; }

        inline bool Alive() { return m_alive; }
        inline void SetAlive(bool alive) { m_alive = alive; }
        inline int GetHealth() { return m_health; }
        inline void AlterHealth(int delta) { m_health += delta; }

        void AttackPlayer();

        int GetXpReward();

    private:
        std::string m_name;
        bool m_alive;

        int m_level;

        int m_health;
        int m_dex;
        int m_str;

        void GenerateName();
        void GenerateLevel();
        std::string GetHitType();
        std::string GetHitLocation();

        static const int ENEMY_BASE_TO_HIT = 50;
        static const int BASE_XP = 5;
        static const int BASE_HEALTH = 30;
};

#endif
