#ifndef D_WORLD_H
#define D_WORLD_H

#include "room.h"

#include <vector>

class World
{
    public:
        World();
        ~World();

        void Update();

        inline Room* GetRoom(int x, int y) { return m_rooms[x][y]; }
        std::vector<int> GetRoomXY(Room* room);

        inline const int GetDimension() { return WORLD_DIMENSION; }

    private:
        static const int WORLD_DIMENSION = 1000;

        // The rooms.
        Room* m_rooms[WORLD_DIMENSION][WORLD_DIMENSION];

};

#endif
