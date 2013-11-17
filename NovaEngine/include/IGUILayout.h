#ifndef IGUILAYOUT_H
#define IGUILAYOUT_H

#include "Object.h"
#include "IGUIManager.h"

namespace novaengine
{
namespace gui
{

class IGUINode;

class IGUILayout : public Object
{
public:
    virtual bool OnEvent(SEvent event)    = 0;
    //NodeList
    virtual void addNode(IGUINode*)       = 0;
    virtual void removeNode(IGUINode*)    = 0;
    virtual IGUINode** getNodeList()      = 0;
    virtual u32  getNodeCount()           = 0;
    virtual void eraseLayout()            = 0;
    virtual IGUINode* getNodeByID(s32 id) = 0;
    //--------------------------------------

    //Sceme
    virtual void setActive() = 0;
    virtual bool isActive()  = 0;
    //Render
    virtual void update()  = 0;
    virtual void animate() = 0;
    virtual void render()  = 0;

protected:
private:
};

}
}

#endif // IGUILAYOUT_H
