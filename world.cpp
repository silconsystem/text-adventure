#include "world.h"

World::World()
{
    for ( int i = 0; i < WORLD_DIMENSION; ++i )
    {
        for ( int j = 0; j < WORLD_DIMENSION; ++j )
        {
            m_rooms[i][j] = new Room();
        }
    }
}

World::~World()
{

}

void World::Update()
{

}

std::vector<int> World::GetRoomXY(Room* room)
{
    for( int i = 0; i < WORLD_DIMENSION; ++i )
    {
        for( int j = 0; j < WORLD_DIMENSION; ++j )
        {
            if ( m_rooms[i][j] == room )
            {
                std::vector<int> xy;
                xy.push_back(i);
                xy.push_back(j);

                return xy;
            }
        }
    }
}
