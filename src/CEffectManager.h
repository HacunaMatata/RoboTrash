#ifndef CEFFECTMANAGER_H
#define CEFFECTMANAGER_H

#include <GL\gl.h>
#include <vector>

enum EFFECT_TYPE
{
    ET_LASSER    = 0x1,
    ET_LIGHTNING = 0x2,
    ET_RAILGUN   = 0x3,
    ET_BFG       = 0x4,
    ET_SHILD     = 0x5,
};

struct SLasserEffect
{
    float start_x;
    float start_y;
    float end_x;
    float end_y;
};

struct SLightningEffect
{
    float start_x;
    float start_y;

    float mid1_x;
    float mid1_y;

    float mid2_x;
    float mid2_y;

    float mid3_x;
    float mid3_y;

    float end_x;
    float end_y;
};

struct SRailGunEffect
{
    float start_x;
    float start_y;
    float end_x;
    float end_y;
};
struct SBFGEffect
{
    float start_x;
    float start_y;
    float end_x;
    float end_y;
};

struct SShildAbsorbEffect
{
    float x;
    float y;
};
struct SEffect
{
    EFFECT_TYPE EffectType;
    SLasserEffect       lasser;
    SLightningEffect    lightning;
    SRailGunEffect      railgun;
    SBFGEffect          bfg;
    SShildAbsorbEffect  shildeffect;
    float       TTL;
};

class CEffectManager
{
    public:
        CEffectManager();
        virtual ~CEffectManager();
        void addeffect_laser(float sx,float sy,float ex,float ey);
        void addeffect_lightning(float sx,float sy,float ex,float ey);
        void addeffect_railgun(float sx,float sy,float ex,float ey);
        void addeffect_bfg(float sx,float sy,float ex,float ey);
        void addeffect_shildabsorb(float x,float y);


        void update(float dt);
        void render();
    protected:
    private:
        std::vector<SEffect> Effects;
};

#endif // CEFFECTMANAGER_H
