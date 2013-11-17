#ifndef ISCENE2DNODE_H
#define ISCENE2DNODE_H

#include "Object.h"
#include "Types.h"

#include "ISceneNode.h"


namespace novaengine
{
namespace scene
{

class IScene2DNode : public ISceneNode
{
public:
    IScene2DNode(ISceneManager* smgr,ISceneNode* parent = 0,s32 ID = -1,core::vector3df position = core::vector3df(0,0,0),core::vector3df rotation= core::vector3df(0,0,0),core::vector3df scale= core::vector3df(1,1,1)):
    ISceneNode(smgr,parent,ID,position,rotation,scale) {}

    virtual ~IScene2DNode() {}

    //----------------------------------Position
    virtual void set2dPosition(core::vector2ds v_position)
    {
        Position = core::vector3df(v_position.x,v_position.y,0);
        update_transform = true;
    }
    virtual core::vector2ds get2dPosition()
    {
        //return Position.to_vector2d();
        return core::vector2ds(Position.x,Position.y);
    }

    virtual core::vector2ds get2dAbsolutePosition()
    {
        if(Parent)
        {
            core::vector3df parent_absolute_pos = Parent->getAbsolutePosition();
            return (get2dPosition() + core::vector2ds(parent_absolute_pos.x,parent_absolute_pos.y));
        }
        return get2dPosition();
    }

    virtual void setScreenPosition(core::vector2df screen_pos)
    {
        core::dimension2du ScreenRes = SceneManager->getRenderer()->getViewport().getDimension();
        core::vector3df newPos;
        newPos.x = screen_pos.x * (ScreenRes.width/2);
        newPos.y = screen_pos.y * (ScreenRes.height/2);
        setPosition(newPos);
    }

    virtual core::vector2df getScreenPosition()
    {
        core::dimension2du ScreenRes = SceneManager->getRenderer()->getViewport().getDimension();
        core::vector2df Pos = getPosition().to_vector2d();
        Pos.x /= (ScreenRes.width/2);
        Pos.y /= (ScreenRes.height/2);
        return Pos;
    }


protected:
private:

};

typedef IScene2DNode* s2dNode;

}
}
#endif // ISCENE2DNODE_H
