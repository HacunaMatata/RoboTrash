#ifndef ISCENECAMERA_H
#define ISCENECAMERA_H

#include "ISceneNode.h"
#include "Types.h"

namespace novaengine
{
namespace scene
{

class ISceneCamera : public ISceneNode
{
public:
    ISceneCamera(ISceneManager* smgr,f32 zFar = 1000,f32 zNear = 0.1f,f32 FOV = 90,ISceneNode* parent = 0,s32 ID = -1,core::vector3df position = core::vector3df(0,0,0),core::vector3df rotation = core::vector3df(0,0,0)) :
    ISceneNode(smgr,parent,ID,position,rotation) {}


    virtual void setFieldOfView(s32 fov = 90) = 0;
    virtual s32  getFieldOfView() = 0;

    virtual void setZNear(f32 znear = 1.0f) = 0;
    virtual f32  getZNear() = 0;

    virtual void setZFar(f32 zfar = 1000) = 0;
    virtual f32  getZFar() = 0;

    virtual void setTarget(core::vector3df TargetCoord) = 0;
    virtual core::vector3df getTarget() = 0;

    virtual void setUpVector(core::vector3df) = 0;
    virtual core::vector3df getUpVector() = 0;

    virtual void setActive() = 0;
    virtual bool isActive() = 0;

    virtual core::matrix4f getPerspectiveProjectionMatrix()  = 0;
    virtual void usePerspectiveProjectionMatrix() = 0;

    virtual core::matrix4f getOrthographicProjectionMatrix() = 0;
    virtual void useOrthographicProjectionMatrix() = 0;

    virtual core::matrix4f get2DViewMatrix() = 0;
    virtual void use2DViewMatrix()           = 0;

    virtual core::matrix4f get3DViewMatrix() = 0;
    virtual void use3DViewMatrix()           = 0;

    virtual core::vector2ds getSceneCoordFromCursorCoord(core::vector2ds CursorPos) = 0;
    virtual core::vector2ds getCursorCoordFromSceneCoord(core::vector3df ScenePos)  = 0;


protected:
private:
};

typedef ISceneCamera* snCamera;

}
}


#endif // ICAMERASCENENODE_H
