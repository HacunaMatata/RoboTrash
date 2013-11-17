#ifndef IGUINODE_H
#define IGUINODE_H

#include "Types.h"
#include "Object.h"
#include "SEvent.h"
#include "IGUIManager.h"

namespace novaengine
{
namespace gui
{

class IGUINode : public Object
{
public:
    IGUINode(IGUIManager* guimgr,s32 id,core::rects rect):
        GUIManager(guimgr),
        NodeID(id),
        Location(rect),
        ZLay(0),
        Visible(true),
        Enabled(true),
        Layout(NULL)
    {
        if(Location.X1 >= Location.X2)
        {
            s32 tmp = Location.X1;
            Location.X1 = Location.X2;
            Location.X2 = tmp;
        }

        if(Location.Y1 >= Location.Y2)
        {
            s32 tmp = Location.Y1;
            Location.Y1 = Location.Y2;
            Location.Y2 = tmp;
        }

    }
    virtual ~IGUINode()
    {
        UnRegisterNode();
    }
    //---------------------------------------------------
    virtual bool OnEvent(SEvent event)
    {
        return false;
    };
    //---------------------------------------------------
    virtual void setLocation(core::rects location)
    {
        Location = location;
    }
    virtual  core::rects getLocation()
    {
        return Location;
    }
    virtual void moveLocation(core::vector2df ScreenPos)
    {
        core::dimension2du ScreenRes = GUIManager->getRenderer()->getViewport().getDimension();

        core::vector3df newPos;
        newPos.x = (ScreenPos.x * (ScreenRes.width/2)) + (ScreenRes.width/2);
        newPos.y = (ScreenPos.y * (ScreenRes.height/2)) + (ScreenRes.height/2);

        core::dimension2ds LocationRes = Location.getDimension();

        Location.X1 = -(LocationRes.width  /2) + newPos.x;
        Location.X2 =  (LocationRes.width  /2) + newPos.x;
        Location.Y1 = -(LocationRes.height /2) + newPos.y;
        Location.Y2 =  (LocationRes.height /2) + newPos.y;
    }
    //---------------------------------------------------
    virtual void setZLay(u32 p_zlay)
    {
        ZLay = p_zlay;
    }
    virtual u32 getZLay()
    {
        return ZLay;
    }
    //---------------------------------------------------
    virtual void setVisible(bool visible)
    {
        Visible = visible;
    }
    virtual bool isVisible()
    {
        return Visible;
    }
    //---------------------------------------------------
    virtual void setEnabled(bool enable)
    {
        Enabled = enable;
    }
    virtual bool isEnabled()
    {
        return Enabled;
    }
    //---------------------------------------------------
    virtual void setNodeID(s32 ID)
    {
        NodeID = ID;
    }
    virtual s32 getNodeID()
    {
        return NodeID;
    }
    //---------------------------------------------------
    virtual bool isPointInside(core::vector2ds point)
    {
        return (point.x >= Location.X1 && point.x <= Location.X2 && point.y >= Location.Y1 && point.y <= Location.Y2 );
    }
    //-------------------------------------------Preparing
    virtual void RegisterNode(IGUILayout* newLayout = 0)
    {
        if(Layout)
            UnRegisterNode();

        if(newLayout)
            newLayout->addNode(this);

        Layout = newLayout;
    }
    virtual void UnRegisterNode()
    {
        if(Layout == NULL)
            return;

        IGUILayout* oldLayout = Layout;
        Layout = NULL;

        oldLayout->removeNode(this);
    }
    virtual IGUILayout* getLayout()
    {
        return Layout;
    }
    //-------------------------------------------Render
    virtual void animate(f32 DeltaTime) = 0;
    virtual void render() = 0;

protected:

    IGUIManager* GUIManager;
    s32 NodeID;
    core::rects Location;
    u32         ZLay;
    bool Visible;
    bool Enabled;

    IGUILayout* Layout;

private:


};

}
}

#endif // IGUINODE_H
