#ifndef CUNITMANAGER_H
#define CUNITMANAGER_H

#include <stdlib.h>
#include <vector>
#include "CMap.h"

using namespace std;
struct SUnit
{
        unsigned int health;

        unsigned int x;
        unsigned int y;
        unsigned int r;
        unsigned int lr;
        unsigned int fm;

        unsigned int unitID;
};

class CUnitManager
{
    public:
        CUnitManager(CMap* Map);
        virtual ~CUnitManager();

        unsigned int createUnit(unsigned int x,unsigned int y);
        unsigned int removeUnit(unsigned int unitId);

        SUnit* getUnitByPos(unsigned int x,unsigned int y);
        SUnit* getUnitById(unsigned int unitId);

        void process_ai();

        void render();

    protected:
    private:
        CMap* Map;
        unsigned int lastID;

        SUnit         player;
        vector<SUnit> units;
};

#endif // CUNITMANAGER_H
