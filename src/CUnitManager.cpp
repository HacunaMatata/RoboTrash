#include "CUnitManager.h"

CUnitManager::CUnitManager(CMap* _Map)
{
    Map = _Map;
    lastID = 1;
    player.health = 0;
}

CUnitManager::~CUnitManager()
{
    //dtor
}

unsigned int CUnitManager::createUnit()
{
    SUnit unit;

    unit.health = 3;

    SSpawnPos point = Map->getRandomSpawnPoint();

    unit.x = point.x;
    unit.y = point.y;

    unit.r  = 4;
    unit.fm = 0;

    unit.unitID = lastID;

    units.push_back(unit);

    lastID++;

    return unit.unitID;
}

unsigned int CUnitManager::removeUnit(unsigned int unitId)
{
    for(unsigned int i = 0; i < units.size(); i++)
    {
        if(units[i].unitID == unitId)
        {
            units.erase(units.begin() + i);
        }
    }
}

SUnit* CUnitManager::getUnitByPos(unsigned int x,unsigned int y)
{
    //if(player.x == x && player.y == y)
    //    return &player;

    for(unsigned int i = 0; i < units.size(); i++)
    {
        if(units[i].x == x && units[i].y == y )
        {
            if(units[i].health > 0)
                return &units[i];
        }
    }
    return NULL;
}

SUnit* CUnitManager::getUnitById(unsigned int unitId)
{
    if(unitId == 0)
        return &player;

    for(unsigned int i = 0; i < units.size(); i++)
    {
        if(units[i].unitID == unitId)
        {
            if(units[i].health > 0)
                return &units[i];
        }
    }
    return NULL;
}

void CUnitManager::process_ai()
{
    for(unsigned int i = 0 ; i < units.size(); i++)
    {
        if(units[i].health > 0)
        {
            switch(units[i].r)
            {
            case 1:
                if(getUnitByPos(units[i].x,units[i].y+1) || getUnitByPos(units[i].x,units[i].y+2))
                {
                    SUnit* c1 = getUnitByPos(units[i].x,units[i].y+1);
                    SUnit* c2 = getUnitByPos(units[i].x,units[i].y+2);

                    if(c1)
                        c1->health--;
                    else
                        c2->health--;

                    continue;
                }
                break;
            case 2:
                if(getUnitByPos(units[i].x+1,units[i].y) || getUnitByPos(units[i].x+2,units[i].y))
                {
                    SUnit* c1 = getUnitByPos(units[i].x+1,units[i].y);
                    SUnit* c2 = getUnitByPos(units[i].x+2,units[i].y);

                    if(c1)
                        c1->health--;
                    else
                        c2->health--;

                    continue;
                }
                break;

            case 3:
                if(getUnitByPos(units[i].x,units[i].y-1) || getUnitByPos(units[i].x,units[i].y-2))
                {
                    SUnit* c1 = getUnitByPos(units[i].x,units[i].y-1);
                    SUnit* c2 = getUnitByPos(units[i].x,units[i].y-2);

                    if(c1)
                        c1->health--;
                    else
                        c2->health--;

                    continue;
                }
                break;

            case 4:
                if(getUnitByPos(units[i].x-1,units[i].y) || getUnitByPos(units[i].x-2,units[i].y))
                {
                    SUnit* c1 = getUnitByPos(units[i].x-1,units[i].y);
                    SUnit* c2 = getUnitByPos(units[i].x-2,units[i].y);

                    if(c1)
                        c1->health--;
                    else
                        c2->health--;

                    continue;
                }
                break;
            }

            switch(units[i].r)
            {
            case 1:
                if(units[i].fm or (Map->getMapTile(units[i].x,units[i].y+1)->passable and not Map->getMapTile(units[i].x-1,units[i].y)->passable) )
                {
                    units[i].y++;
                    units[i].lr = 1;
                    units[i].fm = 0;
                    break;
                }
                else
                {
                    if(Map->getMapTile(units[i].x-1,units[i].y)->passable)
                    {
                        units[i].r = 4;
                        units[i].fm = 1;
                        break;
                    }
                    if(not Map->getMapTile(units[i].x-1,units[i].y)->passable)
                    {
                        units[i].r = 2;
                        break;
                    }
                }

                break;
            case 2:
                if(units[i].fm or (Map->getMapTile(units[i].x+1,units[i].y)->passable and not Map->getMapTile(units[i].x,units[i].y+1)->passable))
                {
                    units[i].x++;
                    units[i].lr = 2;
                    units[i].fm = 0;
                    break;
                }
                else
                {
                    if( Map->getMapTile(units[i].x,units[i].y+1)->passable)
                    {
                        units[i].r = 1;
                        units[i].fm = 1;
                        break;
                    }
                    if( not Map->getMapTile(units[i].x,units[i].y+1)->passable)
                    {
                        units[i].r = 3;
                        break;
                    }
                }

                break;
            case 3:
                if(units[i].fm or (Map->getMapTile(units[i].x,units[i].y-1)->passable and not Map->getMapTile(units[i].x+1,units[i].y)->passable))
                {
                    units[i].y--;
                    units[i].lr = 3;
                    units[i].fm = 0;
                    break;
                }
                else
                {
                    if(Map->getMapTile(units[i].x+1,units[i].y)->passable)
                    {
                        units[i].r = 2;
                        units[i].fm = 1;
                        break;
                    }
                    if(not Map->getMapTile(units[i].x+1,units[i].y)->passable)
                    {
                        units[i].r = 4;
                        break;
                    }
                }

                break;
            case 4:

                if(units[i].fm or (Map->getMapTile(units[i].x-1,units[i].y)->passable and not Map->getMapTile(units[i].x,units[i].y-1)->passable))
                {
                    units[i].x--;
                    units[i].lr = 4;
                    units[i].fm = 0;
                    break;
                }
                else
                {
                    if(Map->getMapTile(units[i].x,units[i].y-1)->passable)
                    {
                        units[i].r = 3;
                        units[i].fm = 1;
                        break;
                    }
                    if(not Map->getMapTile(units[i].x,units[i].y-1)->passable)
                    {
                        units[i].r = 1;
                        break;
                    }
                }

            default:
                units[i].r = (rand()%4)+1;
                break;
            }
            if(units[i].r == 5)
                units[i].r = 1;
        }
        else
        {
            units.erase(units.begin() + i);
        }


    }

}

void CUnitManager::render()
{
    glBegin(GL_TRIANGLES);
    for(unsigned int i = 0 ; i < units.size(); i++)
    {

        if(units[i].health > 0)
        {

            glColor3f(0,0,1);
            switch(units[i].r)
            {
            case 1:
                glVertex3f(units[i].x*32+8,units[i].y*32+8,0);
                glVertex3f(units[i].x*32+24,units[i].y*32+8,0);
                glVertex3f(units[i].x*32+16,units[i].y*32+24,0);
                break;
            case 2:
                glVertex3f(units[i].x*32+8,units[i].y*32+24,0);
                glVertex3f(units[i].x*32+8,units[i].y*32+8,0);
                glVertex3f(units[i].x*32+24,units[i].y*32+16,0);
                break;
            case 3:
                glVertex3f(units[i].x*32+8,units[i].y*32+24,0);
                glVertex3f(units[i].x*32+24,units[i].y*32+24,0);
                glVertex3f(units[i].x*32+16,units[i].y*32+8,0);
                break;
            case 4:
                glVertex3f(units[i].x*32+24,units[i].y*32+24,0);
                glVertex3f(units[i].x*32+24,units[i].y*32+8,0);
                glVertex3f(units[i].x*32+8,units[i].y*32+16,0);
                break;
            default:
                glEnd();
                glBegin(GL_QUADS);
                glVertex3f(units[i].x*32+8,units[i].y*32+8,0);
                glVertex3f(units[i].x*32+24,units[i].y*32+8,0);
                glVertex3f(units[i].x*32+24,units[i].y*32+24,0);
                glVertex3f(units[i].x*32+8,units[i].y*32+24,0);
                glEnd();
                glBegin(GL_TRIANGLES);
            }

        }
    }
    //player

    glEnd();
}
