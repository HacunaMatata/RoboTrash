#include "CUnitManager.h"
#include <time.h>

CUnitManager::CUnitManager(CMap* _Map,CEffectManager* _EffMgr)
{
    Map = _Map;
    EffMgr = _EffMgr;
    lastID = 1;

    SimSpeed = 250;
    Accum = 0;
    srand(time(NULL));
}

CUnitManager::~CUnitManager()
{
    //dtor
}

unsigned int CUnitManager::createUnit()
{
    SUnit unit;

    unit.damage = 1;
    unit.health = 3;
    unit.arrmor = 1;

    unit.kills  = 0;

    SSpawnPos point = Map->getRandomSpawnPoint();

    unit.x = point.x;
    unit.y = point.y;
    unit.lx = point.x;
    unit.ly = point.y;


    unit.r  = 4;
    unit.fm = 0;

    unit.unitID = lastID;

    unit.Rcolor = rand()%256;
    unit.Gcolor = rand()%256;
    unit.Bcolor = rand()%256;

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
            units[i].lx = units[i].x;
            units[i].ly = units[i].y;


            SUnit* trg = NULL;
            unsigned int range = 0;

            switch(units[i].r)
            {
            case 1:


                for(unsigned int r = 1; r < 5; r++)
                {
                    range = r;
                    trg = getUnitByPos(units[i].x,units[i].y+r);
                    if(!Map->getMapTile(units[i].x,units[i].y+r)->passable or trg)
                        break;
                }
                if(trg)
                {
                    unit_shot(&units[i],trg,range);
                    continue;
                }
                break;

            case 2:
                for(unsigned int r = 1; r < 5; r++)
                {
                    range = r;
                    trg = getUnitByPos(units[i].x+r,units[i].y);
                    if(!Map->getMapTile(units[i].x+r,units[i].y)->passable or trg)
                        break;
                }
                if(trg)
                {
                    unit_shot(&units[i],trg,range);
                    continue;
                }
                break;

            case 3:
                for(unsigned int r = 1; r < 5; r++)
                {
                    range = r;
                    trg = getUnitByPos(units[i].x,units[i].y-r);
                    if(!Map->getMapTile(units[i].x,units[i].y-r)->passable or trg)
                        break;
                }
                if(trg)
                {
                    unit_shot(&units[i],trg,range);
                    continue;
                }
                break;

            case 4:
                for(unsigned int r = 1; r < 5; r++)
                {
                    range = r;
                    trg = getUnitByPos(units[i].x-r,units[i].y);
                    if(!Map->getMapTile(units[i].x-r,units[i].y)->passable or trg)
                        break;
                }
                if(trg)
                {
                    unit_shot(&units[i],trg,range);
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
            createUnit();
        }


    }

}

void CUnitManager::update(float dt)
{
    Accum = dt;
}

void CUnitManager::render()
{


    float shift_un = 640/units.size();
    glBegin(GL_TRIANGLES);
    for(unsigned int i = 0 ; i < units.size(); i++)
    {

        if(units[i].health > 0)
        {
            float curr_x,curr_y;
            float last_x,last_y;
            float surf_x,surf_y;

            curr_x = units[i].x*32;
            curr_y = units[i].y*32;

            last_x = units[i].lx*32;
            last_y = units[i].ly*32;

            surf_x = ((curr_x - last_x)/SimSpeed) * Accum;
            surf_y = ((curr_y - last_y)/SimSpeed) * Accum;

            last_x += surf_x;
            last_y += surf_y;


            glColor3ub(units[i].Rcolor,units[i].Gcolor,units[i].Bcolor);
            switch(units[i].r)
            {
            case 1:
                glVertex3f(last_x+8,last_y+8,0);
                glVertex3f(last_x+24,last_y+8,0);
                glVertex3f(last_x+16,last_y+24,0);
                break;
            case 2:
                glVertex3f(last_x+8,last_y+24,0);
                glVertex3f(last_x+8,last_y+8,0);
                glVertex3f(last_x+24,last_y+16,0);
                break;
            case 3:
                glVertex3f(last_x+8,last_y+24,0);
                glVertex3f(last_x+24,last_y+24,0);
                glVertex3f(last_x+16,last_y+8,0);
                break;
            case 4:
                glVertex3f(last_x+24,last_y+24,0);
                glVertex3f(last_x+24,last_y+8,0);
                glVertex3f(last_x+8,last_y+16,0);
                break;
            default:
                break;
            }
            glVertex3f(660+16  ,16 + shift_un * i,0);
            glVertex3f(660+48 ,16 + shift_un * i,0);
            glVertex3f(660+32 ,48+ shift_un * i,0);

            glEnd();

            glColor3ub(255,255,0);

            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
            glLineWidth(units[i].arrmor);
            if(units[i].arrmor != 0)
            {
                glBegin(GL_QUADS);
                glVertex2f(last_x+4,last_y+4);
                glVertex2f(last_x+28,last_y+4);
                glVertex2f(last_x+28,last_y+28);
                glVertex2f(last_x+4,last_y+28);
                glEnd();
            }
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
            glBegin(GL_TRIANGLES);

            glColor3ub(255,0,0);
            float shift_hp = 36 / units[i].health;
            for(unsigned int h = 0; h < units[i].health; h++)
            {
                glVertex3f(716+8 + shift_hp * h ,8 + shift_un * i,0);
                glVertex3f(716+8 + shift_hp * h ,24 + shift_un * i,0);
                glVertex3f(716+24+ shift_hp * h ,16  + shift_un * i,0);
            }


            glColor3ub(255,255,0);
            if(units[i].arrmor > 0)
            {
            float shift_ar = 36 / units[i].arrmor;
            for(unsigned int h = 0; h < units[i].arrmor; h++)
            {
                glVertex3f(716+8 + shift_ar * h ,34 + shift_un * i,0);
                glVertex3f(716+8 + shift_ar * h ,50 + shift_un * i,0);
                glVertex3f(716+24+ shift_ar * h ,42 + shift_un * i,0);
            }
            }
            glColor3ub(0,0,255);

            if(units[i].kills > 0)
            {
            float shift_kl = 36 / units[i].kills;
            for(unsigned int h = 0; h < units[i].kills; h++)
            {

            if(units[i].kills < 4)
            glColor3ub(255,0,0);
            else if(units[i].kills >= 4 and units[i].kills < 8)
            glColor3ub(204,204,255);
            else if(units[i].kills >= 8 and units[i].kills < 12)
            glColor3ub(0,0,255);
            else if(units[i].kills >= 12)
            glColor3ub(125,255,0);

                glVertex3f(716-40  ,24 + shift_un * i + shift_kl*h,0);
                glVertex3f(716-54  ,24 + shift_un * i + shift_kl*h,0);
                glVertex3f(716-54  ,8  + shift_un * i + shift_kl*h,0);
            }
            }


        }
    }
    //player

    glEnd();
}
void CUnitManager::unit_shot(SUnit* Attacking,SUnit* Target,unsigned int dist)
{
    int dist_mod = 16;
    int dist_mod_fix = 0;

    if(Attacking->kills < 4)
        dist_mod_fix = 0;
    else if(Attacking->kills >= 4 and Attacking->kills < 8)
        dist_mod_fix = 8;
    else if(Attacking->kills >= 8 and Attacking->kills < 12)
        dist_mod_fix = 16;
    else if(Attacking->kills >= 12)
        dist_mod_fix = 62;



    switch(dist)
    {
    case 1:
        dist_mod = 18 - (dist_mod_fix > 18)?18:dist_mod_fix;
        break;
    case 2:
        dist_mod = 24 - (dist_mod_fix > 24)?24:dist_mod_fix;
        break;
    case 3:
        dist_mod = 44 - (dist_mod_fix > 44)?44:dist_mod_fix;
        break;
    case 4:
        dist_mod = 64 - (dist_mod_fix > 64)?64:dist_mod_fix;
        break;
    case 5:
        dist_mod = 86 - (dist_mod_fix > 86)?86:dist_mod_fix;
        break;
    }

    int rand_x = (rand()%dist_mod) - dist_mod/2;
    int rand_y = (rand()%dist_mod) - dist_mod/2;

    int curr_x = Target->x*32+16;
    int curr_y = Target->y*32+16;
    int diff_x = Target->x*32+16+rand_x;
    int diff_y = Target->y*32+16+rand_y;

    if(Attacking->kills < 4)
        EffMgr->addeffect_laser(Attacking->x*32+16,Attacking->y*32+16,Target->x*32+16+rand_x,Target->y*32+16+rand_y);
    else if(Attacking->kills >= 4 and Attacking->kills < 8)
        EffMgr->addeffect_lightning(Attacking->x*32+16,Attacking->y*32+16,Target->x*32+16+rand_x,Target->y*32+16+rand_y);
    else if(Attacking->kills >= 8 and Attacking->kills < 12)
        EffMgr->addeffect_railgun(Attacking->x*32+16,Attacking->y*32+16,Target->x*32+16+rand_x,Target->y*32+16+rand_y);
    else if(Attacking->kills >= 12)
        EffMgr->addeffect_bfg(Attacking->x*32+16,Attacking->y*32+16,Target->x*32+16+rand_x,Target->y*32+16+rand_y);


    if (sqrt( pow((curr_x - diff_x),2) + pow((curr_y - diff_y),2)) < 16)
    {
        if(Target->arrmor > 0)
        {
            Target->arrmor-=Attacking->damage;
            EffMgr->addeffect_shildabsorb(Target->x*32+16,Target->y*32+16);
        }
        else
            Target->health-=Attacking->damage;


        if(Target->health <= 0)
        {
            Target->killerID = Attacking->unitID;
            Attacking->arrmor++;
            Attacking->kills++;

            if(Attacking->kills > 2)
            {
                Attacking->health++;
            }

            if(Attacking->kills < 4)
            Attacking->damage = 1;
            else if(Attacking->kills >= 4 and Attacking->kills < 8)
            Attacking->damage = 2;
            else if(Attacking->kills >= 8 and Attacking->kills < 12)
            Attacking->damage = 4;
            else if(Attacking->kills >= 12)
            Attacking->damage = 8;
        }



        if(Target->arrmor < 0)
            Target->arrmor = 0;
        if(Target->health < 0)
            Target->health = 0;


    }
}
