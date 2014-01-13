#include "CEffectManager.h"
#include <stdlib.h>
#include <stdio.h>
CEffectManager::CEffectManager()
{
    glLineWidth(2);
    //ctor
}

CEffectManager::~CEffectManager()
{
    //dtor
}
void CEffectManager::addeffect_laser(float sx,float sy,float ex,float ey)
{
    SEffect lasser_effect;

    lasser_effect.EffectType = ET_LASSER;
    lasser_effect.lasser.start_x = sx;
    lasser_effect.lasser.start_y = sy;
    lasser_effect.lasser.end_x = ex;
    lasser_effect.lasser.end_y = ey;
    lasser_effect.TTL = 200;

    Effects.push_back(lasser_effect);
}
void CEffectManager::addeffect_lightning(float sx,float sy,float ex,float ey)
{
    SEffect lightning;

    lightning.EffectType = ET_LIGHTNING;
    lightning.lightning.start_x = sx;
    lightning.lightning.start_y = sy;

    lightning.lightning.mid1_x = sx + (ex-sx)/4 + rand()%8-4;
    lightning.lightning.mid1_y = sy + (ey-sy)/4 + rand()%8-4;
    lightning.lightning.mid2_x = sx + (ex-sx)/3 + rand()%8-4;
    lightning.lightning.mid2_y = sy + (ey-sy)/3 + rand()%8-4;
    lightning.lightning.mid3_x = sx + (ex-sx)/2 + rand()%8-4;
    lightning.lightning.mid3_y = sy + (ey-sy)/2 + rand()%8-4;

    lightning.lightning.end_x = ex;
    lightning.lightning.end_y = ey;
    lightning.TTL = 200;

    Effects.push_back(lightning);
}

void CEffectManager::addeffect_railgun(float sx,float sy,float ex,float ey)
{
    SEffect railgun;

    railgun.EffectType = ET_RAILGUN;
    railgun.railgun.start_x = sx;
    railgun.railgun.start_y = sy;
    railgun.railgun.end_x = ex;
    railgun.railgun.end_y = ey;
    railgun.TTL = 100;

    Effects.push_back(railgun);
}

void CEffectManager::addeffect_bfg(float sx,float sy,float ex,float ey)
{
    SEffect bfg;

    bfg.EffectType = ET_BFG;
    bfg.bfg.start_x = sx;
    bfg.bfg.start_y = sy;
    bfg.bfg.end_x = ex;
    bfg.bfg.end_y = ey;
    bfg.TTL = 200;

    Effects.push_back(bfg);
}

void CEffectManager::addeffect_shildabsorb(float x,float y)
{
    SEffect shild;

    shild.EffectType = ET_SHILD;
    shild.shildeffect.x = x;
    shild.shildeffect.y = y;
    shild.TTL = 500;

    Effects.push_back(shild);
}

void CEffectManager::update(float dt)
{
    for(unsigned int i = 0; i < Effects.size(); i++)
    {
        if(Effects[i].TTL > 0)
            Effects[i].TTL-=dt;
        else
            Effects.erase(Effects.begin() + i);
    }
}

void CEffectManager::render()
{
    for(unsigned int i = 0; i < Effects.size(); i++)
    {
        if(Effects[i].TTL > 0)
        {

            switch(Effects[i].EffectType)
            {
            case ET_LASSER:
                glLineWidth(1);
                glColor4f(1,0,0,(0.005*Effects[i].TTL));
                glBegin(GL_LINES);
                glVertex2f(Effects[i].lasser.start_x,Effects[i].lasser.start_y);
                glVertex2f(Effects[i].lasser.end_x,Effects[i].lasser.end_y);
                glEnd();

                break;

            case ET_LIGHTNING:
                glLineWidth(2);
                glColor4ub(204,204,255,(1.275*Effects[i].TTL));
                glBegin(GL_LINE_STRIP);

                glVertex2f(Effects[i].lightning.start_x,Effects[i].lightning.start_y);
                glVertex2f(Effects[i].lightning.mid1_x,Effects[i].lightning.mid1_y);
                glVertex2f(Effects[i].lightning.mid2_x,Effects[i].lightning.mid2_y);
                glVertex2f(Effects[i].lightning.mid3_x,Effects[i].lightning.mid3_y);
                glVertex2f(Effects[i].lightning.end_x,Effects[i].lightning.end_y);
                glEnd();
                break;
            case ET_RAILGUN:
                glLineWidth(5);
                glColor4ub(0,71,171,(1.275*Effects[i].TTL));
                glBegin(GL_LINES);
                glVertex2f(Effects[i].railgun.start_x,Effects[i].railgun.start_y);
                glVertex2f(Effects[i].railgun.end_x,Effects[i].railgun.end_y);
                glEnd();
                break;
            case ET_BFG:
                glLineWidth(24);

                glColor4ub(0,255,0,(1.275*Effects[i].TTL));
                glBegin(GL_LINES);
                glVertex2f(Effects[i].bfg.start_x,Effects[i].bfg.start_y);
                glColor4ub(0,0,255,(1.275*Effects[i].TTL));
                glVertex2f(Effects[i].bfg.end_x,Effects[i].bfg.end_y);
                glEnd();


                // +(rand()%64 - 32)
                glLineWidth(6);
                glBegin(GL_LINES);

                glColor4ub(200,150,0,(1.275*Effects[i].TTL));
                glVertex2f(Effects[i].bfg.end_x,Effects[i].bfg.end_y);
                glColor4ub(255,0,0,(1.275*Effects[i].TTL));
                glVertex2f(Effects[i].bfg.end_x+(rand()%64 - 32),Effects[i].bfg.end_y+(rand()%64 - 32));

                glColor4ub(200,150,0,(1.275*Effects[i].TTL));
                glVertex2f(Effects[i].bfg.end_x,Effects[i].bfg.end_y);
                glColor4ub(255,0,0,(1.275*Effects[i].TTL));
                glVertex2f(Effects[i].bfg.end_x+(rand()%64 - 32),Effects[i].bfg.end_y+(rand()%64 - 32));

                glColor4ub(200,150,0,(1.275*Effects[i].TTL));
                glVertex2f(Effects[i].bfg.end_x,Effects[i].bfg.end_y);
                glColor4ub(255,0,0,(1.275*Effects[i].TTL));
                glVertex2f(Effects[i].bfg.end_x+(rand()%64 - 32),Effects[i].bfg.end_y+(rand()%64 - 32));

                glColor4ub(200,150,0,(1.275*Effects[i].TTL));
                glVertex2f(Effects[i].bfg.end_x,Effects[i].bfg.end_y);
                glColor4ub(255,0,0,(1.275*Effects[i].TTL));
                glVertex2f(Effects[i].bfg.end_x+(rand()%64 - 32),Effects[i].bfg.end_y+(rand()%64 - 32));

                glEnd();
                break;
            case ET_SHILD:
                glPointSize(24);
                glColor4ub(255,255,0,(0.51*Effects[i].TTL));
                glBegin(GL_POINTS);
                glVertex2f(Effects[i].shildeffect.x,Effects[i].shildeffect.y);
                glEnd();
                break;
            }
        }
    }
}
