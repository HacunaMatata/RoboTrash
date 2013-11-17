#ifndef CFPSCOUNTER_H
#define CFPSCOUNTER_H

#include "NovaEngine.h"
#include "Timer.h"
#include "Logger.h"

namespace novaengine
{

class CFPSCounter
{
public:
    //--------------------------------
    inline CFPSCounter():
        FPS(60),
        MPF(16.6),
        MPFLast(0),
        FrameCount(0),
        DeltaUpdate(Timer::getTime()),
        CounterUpdate(1000)
    {

    }
    inline virtual ~CFPSCounter()
    {

    }
    //--------------------------------
    inline void register_frame()
    {
        FrameCount++;
        const u32 RealTime = Timer::getTime();
        const u32 Time = RealTime - DeltaUpdate;

        if(Time >= CounterUpdate)
        {
            FPS = (FrameCount/(f32)Time)*1000;

            if(FrameCount == 0)
                MPF = 0;
            else
                MPF = 1000 / (f32)FPS;

            FrameCount=0;
            DeltaUpdate = RealTime;
        }
    }
    //--------------------------------

    inline f32 getFPS()
    {
        return FPS;
    };
    inline f32 getMPF()
    {
        return MPF;
    };

private:

    f32 FPS;
    f32 MPF;
    f32 MPFLast;
    u32 FrameCount;
    u32 DeltaUpdate;
    u32 CounterUpdate;

};

}
#endif // CFPSCOUNTER_H
