#ifndef CEFFECTMANAGER_H
#define CEFFECTMANAGER_H

#include <GL\gl.h>
#include <vector>

enum EFFECT_TYPE
{
    ET_LASSER = 0x1,
};

struct SLasserEffect
{
    float start_x;
    float start_y;
    float end_x;
    float end_y;
};

struct SEffect
{
    EFFECT_TYPE EffectType;
    SLasserEffect lasser;
    float       TTL;
};

class CEffectManager
{
    public:
        CEffectManager();
        virtual ~CEffectManager();
        void addeffect_laser(float sx,float sy,float ex,float ey);

        void update(float dt);
        void render();
    protected:
    private:
        std::vector<SEffect> Effects;
};

#endif // CEFFECTMANAGER_H
