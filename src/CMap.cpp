#include "CMap.h"
#include <stdio.h>

CMap::CMap(int w,int h)
{
    Map = new SMapTile[w*h];
}

CMap::CMap(const char* file_name)
{
    FILE* file = fopen(file_name,"r");
    char buf[256];
    fscanf(file,"%d %d",MapWidth,MapHeight);
    Map = new SMapTile[MapWidth*MapHeight];

    for(int h = 0;h < MapHeight;h++)
    {
        for(int w = 0;w < MapWidth;w++)
        {
            SMapTile tile;
            switch(fgetc(file))
            {
            case '1':
                tile.passable = 0;
                tile.tileID   = 1;

                break;
            case '2':
                tile.passable = 0;
                tile.tileID   = 2;

                break;
            case '3':
                tile.passable = 1;
                tile.tileID   = 3;

                break;
            case '4':
                tile.passable = 1;
                tile.tileID   = 4;

                break;
            default:
                    break;
            }

            setMapTile(w,h,tile);
        }
    }
}

CMap::~CMap()
{
    //dtor
}

SMapTile* CMap::getMapTile(unsigned int x,unsigned int y)
{

}

void CMap::setMapTile(unsigned int x,unsigned int y,SMapTile tile)
{

}
