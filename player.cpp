#include "player.h"

// Matching fwd decl
#include "game.h"

Player::Player(World* world):
    m_alive(true),
    m_totalHealth(100),
    m_currentHealth(100),
    m_dex(10),
    m_str(10),
    m_level(1),
    m_xpThisLevel(0)
{
    mp_world = world;

    // Position the player initially
    int x = rand() % mp_world->GetDimension();
    int y = rand() % mp_world->GetDimension();

    mp_currentRoom = mp_world->GetRoom(x,y);

    // DEBUG
    /*for( int i = 0; i < NUM_ITEMS; ++i )
    {
        Item* test = new Item(3,3,3);
        m_items[i] = test;
    }*/
}

Player::~Player()
{
}

void Player::Update()
{
    // Have we levelled?
    int toLevel = GetXpToLevel();
    if ( toLevel <= 0 )
    {
        m_level++;
        m_xpThisLevel = 0;
        m_xpThisLevel += (-toLevel); // Add on the excess xp
        std::cout << "DING! Your level has increased to " << m_level << "!\n";

        int whichStat;
        std::string stat;
        bool levelDecided = false;
        while ( !levelDecided )
        {
            levelDecided = true;

            std::cout << "Choose a stat to increase (hp, str, dex):\n";

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
            stat = choiceString;

            if ( choiceString == "hp" )
            {
                m_currentHealth += 50;
                m_totalHealth += 50;
                whichStat = m_currentHealth;
            }
            else if ( choiceString == "str" )
            {
                m_str += 3;
                whichStat = m_str;
            }
            else if ( choiceString == "dex" )
            {
                m_dex += 3;
                whichStat = m_dex;
            }
            else {
                levelDecided = false;
            }
        }

        m_currentHealth = m_totalHealth;

        std::cout << "Your " << stat << " has increased to " << whichStat << "!\n";
    }
}

void Player::Rest()
{
    // First determine how much HP we have of total.
    int healthPercentage = static_cast<int>((static_cast<float>(m_currentHealth) / static_cast<float>(m_totalHealth)) * 100.0f);

    if ( healthPercentage == 100 )
    {
        std::cout << "You don't need to rest right now.\n";
        return;
    }

    // For each 5% missing, add an hour to rest time.
    int missingHealthPercent = 100 - healthPercentage;
    int hoursRest = (missingHealthPercent / 5) + 1;

    std::cout << "You are at " << m_currentHealth << "/" << m_totalHealth << "HP.\n";
    std::cout << "You will need " << hoursRest << " hour(s) rest to fully recover. Are you sure?\n";

    bool yesNo = false;
    while ( !yesNo )
    {
        yesNo = true;

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

        if ( choiceString == "yes" || choiceString == "y" )
        {
            BeginResting(hoursRest);
        }
        else if ( choiceString == "no" || choiceString == "n" )
        {
        }
        else
        {
            yesNo = false;
            std::cout << "Please specify whether you wish to rest with y(es) or n(o).\n";
        }
    }
}

void Player::BeginResting(int hours)
{
    int hoursRemaining = hours;
    bool asleep = true;

    while( hoursRemaining > 0 && asleep )
    {
        int enemyRoll = rand() % 100 + 1;
        if ( enemyRoll > 98 )
        {
            asleep = false;

            // Spawn enemy and surprise attack!
            Enemy* enemy = mp_currentRoom->SpawnNewEnemy();
            Game::GetInstance().StartCombat();
            Game::GetInstance().SurpriseAttack();

            std::cout << "You have been awoken by a level " << enemy->GetLevel() << " " << enemy->GetName() << "! It suddenly attacks!\n";

            return;
        }

        // Heal the player
        int fivePercent = m_totalHealth / 20;
        m_currentHealth += fivePercent;
        if ( m_currentHealth > m_totalHealth ) m_currentHealth = m_totalHealth;

        std::cout << hoursRemaining << " hour(s) of sleep remaining.\n";
        sleep(1);

        --hoursRemaining;
    }

    std::cout << "You awake refreshed and fully healed.\n";
}

void Player::AwardXp(int xp)
{
    m_xpThisLevel += xp;
}

int Player::GetXpToLevel()
{
    int amountToLevel = (m_level*m_level*m_level) * XP_TO_LEVEL_SCALAR;
    int needed = amountToLevel - m_xpThisLevel;

    return needed;
}

std::string Player::GetLevelProgress()
{
    int total = (m_level*m_level*m_level) * XP_TO_LEVEL_SCALAR;

    std::ostringstream result;
    result << m_xpThisLevel;
    std::string output = result.str();

    output += "/";

    result.str("");
    result << total;
    output += result.str();

    return output;
}

void Player::Attack(Enemy* enemy)
{
    // First, we check the player's dex to see if we've hit.
    // TODO: stats
    int toHit = rand() % 100 + 1;

    int totalDex = m_dex;
    for ( int i = 0; i < NUM_ITEMS; ++i )
    {
        if ( m_items[i] != NULL )
        {
            int dex = m_items[i]->GetBonusDex();
            totalDex += dex;
        }
    }

    int hitsOn = 100 - ( BASE_TO_HIT + totalDex );
    std::cout << "To hit roll: REQ(" << hitsOn << ") + ROLLED(" << toHit << ")\n";

    // Account for crits.
    bool crit = false;
    if ( toHit > 90 )
    {
        crit = true;
    }

    if ( toHit > hitsOn || crit )
    {
        // Then we check the player's strength to see the damage. Bit of randomisation in there.
        int totalStr = m_str;
        for ( int i = 0; i < NUM_ITEMS; ++i )
        {
            if ( m_items[i] != NULL )
            {
                int str = m_items[i]->GetBonusStr();
                totalStr += str;
            }
        }

        int randomDamage = (rand() % totalStr - ( totalStr / 2));
        int damage = totalStr + randomDamage;
        std::cout << "Damage roll: RND(" << randomDamage << ") + STR(" << totalStr << ")\n";

        // Then we damage the enemy.
        damage = crit ? ( 2 * damage ) : damage;
        enemy->AlterHealth(-damage);

        std::string hitType = crit ? "CRIT" : "hit";
        std::cout << "You " << hitType << " the " << enemy->GetName() << " for " << damage << " damage. It has " << enemy->GetHealth() << " HP remaining.\n";
    }
    else
    {
        std::cout << "You completely miss the " << enemy->GetName() << ".\n";
    }
}

bool Player::AttemptRun()
{
    int runRoll = 100 - ( rand() % 100 + 1 );

    std::cout << "Run roll: ROLL(" << runRoll << ") + TARGET(" << 30 << ")\n";

    return (runRoll > 30);
}
