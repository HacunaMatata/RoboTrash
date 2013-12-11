#include "CMap.h"
#include <stdio.h>

CMap::CMap(unsigned int w,unsigned int h)
{

    MapWidth  = w;
    MapHeight = h;

    Map = new SMapTile[w*h];
}

CMap::CMap(const char* file_name)
{
    FILE* file = fopen(file_name,"r");
    if(file == NULL)
    {
        printf("Cant open file %s\n",file_name);
    }
    else
    {

        char buf[256];
        fscanf(file,"%d %d",&MapWidth,&MapHeight);
        Map = new SMapTile[MapWidth*MapHeight];

        unsigned int index = 0;
        bool valid         = false;
        while(!feof(file))
        {
                SMapTile tile;
                switch(fgetc(file))
                {
                case '1':
                    tile.passable = 0;
                    tile.tileID   = 1;
                    valid = true;
                    break;
                case '2':
                    tile.passable = 0;
                    tile.tileID   = 2;
                    valid = true;
                    break;
                case '3':
                    tile.passable = 1;
                    tile.tileID   = 3;
                    valid = true;
                    break;
                case '4':
                    tile.passable = 1;
                    tile.tileID   = 4;
                    valid = true;
                    break;
                default:
                    valid = false;
                    break;
                }
            if(index >= (MapWidth * MapHeight))
                valid = false;

            if(valid)
            {
                Map[index] = tile;
                valid = false;
                index++;
            }
        }
    }
}

CMap::~CMap()
{
    //dtor
}

SMapTile* CMap::getMapTile(unsigned int x,unsigned int y)
{
    unsigned int index = x + (y*MapHeight);
    return &Map[index];
}

void CMap::setMapTile(unsigned int x,unsigned int y,SMapTile tile)
{
    unsigned int index = x + (y*MapHeight);
    Map[index] = tile;
}

void CMap::render()
{

    glBegin(GL_QUADS);
    for(unsigned int xt = 0; xt < MapWidth; xt++)
    {
        for(unsigned int yt = 0; yt < MapHeight; yt++)
        {
            unsigned int x = xt * 32;
            unsigned int y = yt * 32;

            SMapTile* tile = getMapTile(xt,yt);

            switch(tile->tileID)
            {
            case 1:
                glColor3f(1,0,0);
                break;
            case 2:
                glColor3f(1,1,0);
                break;
            case 3:
                glColor3f(0,1,1);
                break;
            case 4:
                glColor3f(0,1,0);
                break;
            }

            glVertex3f(x    ,y      ,0);
            glVertex3f(x+32 ,y      ,0);
            glVertex3f(x+32 ,y+32   ,0);
            glVertex3f(x    ,y+32   ,0);

        }
    }
    glEnd();
}
