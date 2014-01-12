#ifndef CUNITMANAGER_H
#define CUNITMANAGER_H

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "CMap.h"

using namespace std;
struct SUnit
{
        unsigned int health;

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
};

class CUnitManager
{
    public:
        CUnitManager(CMap* Map);
        virtual ~CUnitManager();

        unsigned int createUnit();
        unsigned int removeUnit(unsigned int unitId);

        SUnit* getUnitByPos(unsigned int x,unsigned int y);
        SUnit* getUnitById(unsigned int unitId);

        void process_ai();

        void render(float dt);

    protected:
    private:
        CMap* Map;
        unsigned int lastID;

        SUnit         player;
        vector<SUnit> units;

        float SimSpeed;
        float Accum;
};

#endif // CUNITMANAGER_H
