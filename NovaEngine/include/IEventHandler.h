#ifndef IEVENTHANDLER_H
#define IEVENTHANDLER_H


#include "Object.h"
#include "SEvent.h"

namespace novaengine
{

class IEventHandler : public Object
{
    public:
       virtual bool OnEvent(SEvent) = 0;
    protected:
    private:
};

}
#endif // IEVENTHANDLER_H
