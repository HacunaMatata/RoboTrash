#ifndef ITIMER_H
#define ITIMER_H

namespace novaengine
{
class ITimer
{
    public:
        virtual u64 getTime() = 0;

        virtual void stop()   = 0;
        virtual void pause()  = 0;

    protected:
    private:
};
}
#endif // ITIMER_H
