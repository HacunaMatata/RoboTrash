#ifndef CMAP_H
#define CMAP_H

#include <vector>
#include <GL\gl.h>
#include <stdlib.h>

struct SSpawnPos
{
    unsigned int x;
    unsigned int y;
};

struct SMapTile
{
    bool passable;
    int tileID;
};

class CMap
{
    public:
        CMap(unsigned int w,unsigned int h);
        CMap(const char* file_name);
        virtual ~CMap();

        SSpawnPos getRandomSpawnPoint();
        SMapTile* getMapTile(unsigned int x,unsigned int y);
        void setMapTile(unsigned int x,unsigned int y,SMapTile tile);
        void render();

    protected:
    private:
        std::vector<SSpawnPos> SpawnPoints;
        unsigned int CurrentSpanwPointID;

        unsigned int MapWidth;
        unsigned int MapHeight;
        SMapTile* Map;
};

#endif // CMAP_H
