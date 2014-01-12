#include "CEffectManager.h"
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

void CEffectManager::update(float dt)
{
    for(unsigned int i = 0; i < Effects.size();i++)
    {
        if(Effects[i].TTL > 0)
            Effects[i].TTL-=dt;
        else
            Effects.erase(Effects.begin() + i);
    }
}

void CEffectManager::render()
{
    for(unsigned int i = 0; i < Effects.size();i++)
    {
        if(Effects[i].TTL > 0)
        {

            switch(Effects[i].EffectType)
            {
            case ET_LASSER:
                glColor4f(1,0,0,(0.005*Effects[i].TTL));
                glBegin(GL_LINES);
                glVertex2f(Effects[i].lasser.start_x,Effects[i].lasser.start_y);
                glVertex2f(Effects[i].lasser.end_x,Effects[i].lasser.end_y);
                glEnd();

                break;
            }
        }
    }
}
