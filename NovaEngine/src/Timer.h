#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <sys/time.h>
#include "Types.h"

namespace novaengine
{

class Timer
{
    public:
        static inline u64 getTime()
        {
            timeval tv;
            gettimeofday(&tv,0);
            return (u64) (tv.tv_sec * 1000) + (tv.tv_usec / 1000);

        }
};

}
#endif // TIMER_H
