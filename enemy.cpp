#include "enemy.h"

#include "game.h"

Enemy::Enemy() :
    m_name(""),
    m_alive(true),
    m_health(30),
    m_dex(5),
    m_str(5),
    m_level(1)
{
    GenerateName();

    GenerateLevel();
}

Enemy::~Enemy()
{

}

int Enemy::GetXpReward()
{
    int xp = (m_level*m_level) * BASE_XP;
    return xp;
}

void Enemy::GenerateLevel()
{
    int playerLevel = Game::GetInstance().GetPlayer()->GetLevel();

    // Based on this, let's have some random level action.
    int variation = rand() % 3 - 1;

    int level = playerLevel + variation;
    if ( level < 1 ) level = 1;

    m_level = level;
    m_health = BASE_HEALTH * m_level;
}

void Enemy::GenerateName()
{
    std::string adjectives[] = {
        "covetous",
        "corpulent",
        "rotund",
        "robust",
        "forthright",
        "slightly fey",
        "baritone",
        "discourteous",
        "two-dimensional",
        "triumphant",
        "text-based",
        "clever",
        "consistently incorrect",
        "pendantic",
        "metallic",
        "sharpened",
        "keen",
        "gyrating",
        "wildly inappropriate",
        "shapeless",
        "fabulously wealthy",
        "spicy",
        "garrulous",
        "jejune",
        "proselytizing",
        "crepuscular",
        "cromulent",
        "jism-covered",
        "polyphonic",
        "vampiric",
        "pine-scented",
        "ripe"
    };

    int numAdjectives = sizeof(adjectives) / sizeof(std::string);
    int random = rand() % numAdjectives;

    std::string adjective = adjectives[random];
    
    std::string enemies[] = {
        "Hare Krishna",
        "Parrot",
        "Donkey",
        "Weasel",
        "Llama",
        "Alpaca",
        "Beet Farmer",
        "Good Ole Boy",
        "Radio 1 DJ",
        "Maths Teacher",
        "Baker",
        "Pirate",
        "Talking Egg",
        "Roll of Magic Whiteboard",
        "Clunge",
        "Beaver",
        "Janet Jackson",
        "Vampire",
        "Game Developer",
        "Goth Kid",
        "Systems Analyst",
        "St Paul's Cathedral",
        "Diddy Kong",
        "Munt Cuffin",
        "Smut Peddler",
        "Impressionist Painter",
        "Stream of Consciousness Stand Up Comedian",
        "Journalist",
        "Cockney",
        "Geordie",
        "Angel of the North",
        "Cabinet Minister",
        "Were-Llama",
        "Pair of Trainers",
        "Sitcom Writer",
        "Samurai",
        "Shogun",
        "Fallout Boy",
        "Comic-Book Guy",
        "Mormon",
        "Jew",
        "Free Methodist",
        "Bzuzu",
        "Second-tier Steve Coogan character",
        "Picture of a Man in full Naval dress"
    };

    int numEnemies = sizeof(enemies) / sizeof(std::string);
    int randomEn = rand() % numEnemies;

    std::string enemy = enemies[randomEn];

    m_name = adjective + " " + enemy;
}

void Enemy::AttackPlayer()
{
    // First, we check the enemy's dex to see if we've hit.
    int toHit = rand() % 100 + 1;
    int hitsOn = 100 - ( ENEMY_BASE_TO_HIT + m_dex );
    std::cout << "\nEnemy to hit roll: REQ(" << hitsOn << ") + ROLLED(" << toHit << ")\n";

    if ( toHit > hitsOn )
    {
        // Then we check the enemy's strength to see the damage. Bit of randomisation in there.
        int baseDmg = m_str + m_level;
        int randomDamage = (rand() % baseDmg - ( baseDmg / 2));
        int damage = baseDmg + randomDamage;
        std::cout << "Enemy damage roll: RND(" << randomDamage << ") + BASE(" << baseDmg << ")\n";

        // Then we damage the player.
        Game::GetInstance().GetPlayer()->AlterHealth(-damage);

        std::string randomAttack = GetHitType();
        std::string randomLocation = GetHitLocation();

        std::cout << "The " << m_name << " " <<  randomAttack << " you in the " << randomLocation << " for "
            << damage << " damage. You have " << Game::GetInstance().GetPlayer()->GetCurrentHealth() << " HP remaining.\n";
    }
    else
    {
        std::cout << "The " << m_name << " misses you utterly.\n";
    }
}

std::string Enemy::GetHitType()
{
    std::string types[] = {
        "bites",
        "kicks",
        "nuts",
        "wellies",
        "knees",
        "gently prods",
        "suggestively tickles",
        "rubs",
        "slaps",
        "jangles",
        "licks",
        "buggers",
        "reams",
        "donkey punches",
        "elbows",
        "rogers"
    };

    int numTypes = sizeof(types) / sizeof(std::string);
    int randomType = rand() % numTypes;

    std::string type = types[randomType];

    return type;
}

std::string Enemy::GetHitLocation()
{
    std::string locations[] = {
        "face",
        "arse",
        "bojangles",
        "dangly parts",
        "crotch",
        "arm",
        "shin",
        "nose",
        "eyesocket",
        "posterior",
        "unmentionables",
        "leg",
        "knee",
        "elbow",
        "cock",
        "shoe",
        "ear",
        "mouth",
        "beard",
        "moustache",
        "mangina",
        "fairy cave",
        "armpit",
        "growler",
        "foot",
        "poop deck",
        "haircut",
        "lips"
    };

    int numLocations = sizeof(locations) / sizeof(std::string);
    int randomLocation = rand() % numLocations;

    std::string location = locations[randomLocation];

    return location;
}
