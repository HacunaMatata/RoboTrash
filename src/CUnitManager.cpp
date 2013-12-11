#include "CUnitManager.h"

CUnitManager::CUnitManager(CMap* _Map)
{
    Map = _Map;
    lastID = 1;
}

CUnitManager::~CUnitManager()
{
    //dtor
}

unsigned int CUnitManager::createUnit(unsigned int x,unsigned int y)
{
    SUnit unit;

    unit.health = 3;

    unit.x = x;
    unit.y = y;

    unit.r = 4;

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
    if(player.x == x && player.y == y)
        return &player;

    for(unsigned int i = 0; i < units.size(); i++)
    {
        if(units[i].x == x && units[i].y == y )
        {
            return &units[i];
        }
    }
}

SUnit* CUnitManager::getUnitById(unsigned int unitId)
{
    if(unitId == 0)
        return &player;

    for(unsigned int i = 0; i < units.size(); i++)
    {
        if(units[i].unitID == unitId )
        {
            return &units[i];
        }
    }
}

void CUnitManager::process_ai()
{
    for(unsigned int i = 0 ; i < units.size(); i++)
    {
        if(units[i].health > 0)
        {

            //check avalible ways
            int ways_alv = 0;
            if(Map->getMapTile(units[i].x-1,units[i].y)->passable)
                ways_alv++;
            if(Map->getMapTile(units[i].x,units[i].y-1)->passable)
                ways_alv++;
            if(Map->getMapTile(units[i].x+1,units[i].y)->passable)
                ways_alv++;
            if(Map->getMapTile(units[i].x,units[i].y+1)->passable)
                ways_alv++;

            //avalible path pool
            vector<int> path_pool;
            if(Map->getMapTile(units[i].x,units[i].y+1)->passable && !(ways_alv > 1 && units[i].r == 1))
                path_pool.push_back(1);
            if(Map->getMapTile(units[i].x+1,units[i].y)->passable && !(ways_alv > 1 && units[i].r == 2))
                path_pool.push_back(2);
            if(Map->getMapTile(units[i].x,units[i].y-1)->passable && !(ways_alv > 1 && units[i].r == 3))
                path_pool.push_back(3);
            if(Map->getMapTile(units[i].x-1,units[i].y)->passable && !(ways_alv > 1 && units[i].r == 4))
                path_pool.push_back(4);

            //fix pool

            //chance to change way modifer
            int chng_dir_chance_mod = 5 - path_pool.size();
            //chance to change direction
            bool chng_dir = false;
            chng_dir = ((rand() % chng_dir_chance_mod) == 1);
            //check if way avalible
            if(!chng_dir)
            {
                switch(units[i].r)
                {
                case 1:
                    if(!Map->getMapTile(units[i].x,units[i].y+1)->passable)
                        chng_dir = true;
                    break;
                case 2:
                    if(!Map->getMapTile(units[i].x+1,units[i].y)->passable)
                        chng_dir = true;
                    break;
                case 3:
                    if(!Map->getMapTile(units[i].x,units[i].y-1)->passable)
                        chng_dir = true;
                    break;
                case 4:
                    if(!Map->getMapTile(units[i].x-1,units[i].y)->passable)
                        chng_dir = true;
                    break;
                default:
                    break;
                }
            }

            if(chng_dir)
            {
                //get random way from pool
                unsigned int random_way = path_pool[rand() % path_pool.size()];
                units[i].r = random_way;
            }
            else
            {
                //or move
                switch(units[i].r)
                {
                case 1:
                    units[i].y++;
                    break;
                case 2:
                    units[i].x++;
                    break;
                case 3:
                    units[i].y--;
                    break;
                case 4:
                    units[i].x--;
                    break;
                default:
                    break;
                }
            }

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
