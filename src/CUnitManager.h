#ifndef CUNITMANAGER_H
#define CUNITMANAGER_H

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <math.h>
#include "CMap.h"
#include "CEffectManager.h"

using namespace std;
struct SUnit
{
        unsigned int health;
        unsigned int arrmor;

        unsigned int x;
        unsigned int y;
        unsigned int lx;
        unsigned int ly;


        unsigned int r;
        unsigned int fm;

        unsigned char Rcolor;
        unsigned char Gcolor;
        unsigned char Bcolor;


        unsigned int unitID;
        unsigned int killerID;
};

class CUnitManager
{
    public:
        CUnitManager(CMap* Map,CEffectManager* EffMgr);
        virtual ~CUnitManager();

        unsigned int createUnit();
        unsigned int removeUnit(unsigned int unitId);

        SUnit* getUnitByPos(unsigned int x,unsigned int y);
        SUnit* getUnitById(unsigned int unitId);

        void process_ai();
        void update(float dt);
        void render();

    protected:
    private:
        void unit_shot(SUnit* Attacking,SUnit* Target,unsigned int dist);

        CMap* Map;
        CEffectManager* EffMgr;
        unsigned int lastID;

        SUnit         player;
        vector<SUnit> units;

        float SimSpeed;
        float Accum;
};

#endif // CUNITMANAGER_H
