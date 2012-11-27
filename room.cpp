#include "room.h"

// Matching fwd decl
#include "game.h"

Room::Room():
    m_initialised(false)
{
}

Room::~Room()
{

}

void Room::Init()
{
    int enemyEncounterChance = 60; // 60%
    int encounter = rand() % 100 + 1;
    if ( encounter > enemyEncounterChance )
    {
        if ( mp_enemy == NULL )
        {
            mp_enemy = new Enemy();
        }

        std::cout << "You encounter a level " << mp_enemy->GetLevel() << " " << mp_enemy->GetName() << "\n";

        // Randomly attack!
        if ( encounter > 75 )
        {
            std::cout << "The " << mp_enemy->GetName() << " suddenly attacks!\n";
        
            Game::GetInstance().StartCombat();
            Game::GetInstance().SurpriseAttack();
        }
    }
    else
    {
        std::cout << "The area is empty.\n";
    }

    m_initialised = true;
}

void Room::Update()
{
    // Update the encounter.
    // TODO: More things
    if ( mp_enemy == NULL )
    {
        std::cout << "The area continues to be empty.\n";
    }
    else if ( mp_enemy->Alive() )
    {
        std::cout << "You've found the " << mp_enemy->GetName() << " again.\n";
    }
    else
    {
        std::cout << "You see the remains of the " << mp_enemy->GetName() << ". Your eyes fill with passionate tears of remembrance.\n";
    }
}

Enemy* Room::SpawnNewEnemy()
{
    delete mp_enemy;
    mp_enemy = 0;

    mp_enemy = new Enemy();
    return mp_enemy;
}
