#ifndef CSCENECAMERA_H
#define CSCENECAMERA_H

#include "Types.h"
#include "ISceneCamera.h"

namespace novaengine
{
namespace scene
{
class CSceneCamera : public ISceneCamera
{
public:
    CSceneCamera(ISceneManager* smgr,f32 Far = 1000,f32 Near = 1,f32 FOV = 90,ISceneNode* parent = 0,s32 ID = -1,core::vector3df position = core::vector3df(0,0,0),core::vector3df rotation = core::vector3df(0,0,0)) :
        ISceneCamera(smgr,Far,Near,FOV,parent,ID,position,rotation)
    {
        NodeType = ENT_CAMERA;

        FieldOfView = FOV;
        zFar  = Far;
        zNear = Near;
        UpVector =  core::vector3df(0,1,0);
        Target   =  core::vector3df(0,0,-1);
        update_projection = true;
    }

    virtual void setFieldOfView(s32 fov = 90)
    {
        FieldOfView = fov;
        update_projection = true;
    }
    virtual s32  getFieldOfView()
    {
        return FieldOfView;
    }

    virtual void setZNear(f32 _znear = 1.0f)
    {
        zNear = _znear;
        update_projection = true;
    }
    virtual f32  getZNear()
    {
        return zNear;
    }

    virtual void setZFar(f32 _zfar = 1000)
    {
        zFar = _zfar;
        update_projection = true;
    }
    virtual f32  getZFar()
    {
        return zFar;
    }

    virtual void setTarget(core::vector3df _target)
    {
        Target = _target;
    }
    virtual core::vector3df getTarget()
    {
        return Target;
    }

    virtual void setUpVector(core::vector3df _upvector)
    {
        UpVector = _upvector;
    }
    virtual core::vector3df getUpVector()
    {
        return UpVector;
    }

    virtual void setActive()
    {
        if(Scene == NULL)
            return;

        Scene->setActiveCamera(this);
    }
    virtual bool isActive()
    {
        if(Scene == NULL)
            return false;

        return (Scene->getActiveCamera() == this);
    }

    virtual core::matrix4f getOrthographicProjectionMatrix()
    {
        check_update_projection_matrix();
        return opm;
    }
    virtual void useOrthographicProjectionMatrix()
    {
        SceneManager->getRenderer()->setTransform(getOrthographicProjectionMatrix(),renderer::EMT_PROJECTION);
    }
    virtual core::matrix4f getPerspectiveProjectionMatrix()
    {
        check_update_projection_matrix();
        return ppm;
    }
    virtual void usePerspectiveProjectionMatrix()
    {
        SceneManager->getRenderer()->setTransform(getPerspectiveProjectionMatrix(),renderer::EMT_PROJECTION);
    }

    virtual core::matrix4f get2DViewMatrix()
    {
        core::matrix4f view;
        view.setTranslate(-getAbsolutePosition());
        return view;
    }
    virtual void use2DViewMatrix()
    {
        SceneManager->getRenderer()->setTransform(get2DViewMatrix(),renderer::EMT_VIEW);
    }

    virtual core::matrix4f get3DViewMatrix()
    {
        core::matrix4f view;
        view.buildLookAtMatrix(getAbsolutePosition(),getAbsolutePosition() + Target,UpVector);
        return view;
    }
    virtual void use3DViewMatrix()
    {
        SceneManager->getRenderer()->setTransform(get3DViewMatrix(),renderer::EMT_VIEW);
    }

    core::vector2ds getSceneCoordFromCursorCoord(core::vector2ds CursorPos)
    {
        if(SceneManager->getRenderGridResolution().getArea() == 0)
        {
            core::vector2ds ScenePos = core::vector2ds(getAbsolutePosition().x,getAbsolutePosition().y);
            ScenePos.x +=  (CursorPos.x - (float)(ViewPort.width  / 2));
            ScenePos.y += -(CursorPos.y - (float)(ViewPort.height / 2));
            return ScenePos;
        }
        else
        {
            core::vector2ds ScenePos = core::vector2ds(getAbsolutePosition().x,getAbsolutePosition().y);
            core::dimension2du RendererViewPort = SceneManager->getRenderer()->getViewport().getDimension();

            f32 modif_x = f32(RendererViewPort.width)  / f32(ViewPort.width  );
            f32 modif_y = f32(RendererViewPort.height) / f32(ViewPort.height );

            ScenePos.x +=  (CursorPos.x - (float)(RendererViewPort.width  / 2)) / modif_x;
            ScenePos.y += -(CursorPos.y - (float)(RendererViewPort.height / 2)) / modif_y;
            return ScenePos;
        }
    }
    core::vector2ds getCursorCoordFromSceneCoord(core::vector3df ScenePos) {};

    virtual void update()
    {
        ISceneNode::update();
    }
    virtual void animate()
    {
        ISceneNode::animate();
    }
    virtual void render()
    {
        ISceneNode::render();
    }


protected:

    void check_update_projection_matrix()
    {
        core::dimension2du RenderViewPort;

        if(SceneManager->getRenderGridResolution().getArea() != 0)
            RenderViewPort = SceneManager->getRenderGridResolution();
        else
            RenderViewPort = SceneManager->getRenderer()->getViewport().getDimension();

        if(ViewPort != RenderViewPort || update_projection)
        {
            ViewPort = RenderViewPort;
            update_all_projection_matrix();
        }
    }
    void update_all_projection_matrix()
    {

        update_projection = false;
        opm.makeIndetify();
        opm.buildOrthographicProjectionMatrix(-((float)ViewPort.width/2),((float)ViewPort.width/2),-((float)ViewPort.height/2),((float)ViewPort.height/2),-zFar,zFar);

        ppm.makeIndetify();
        ppm.buildPerspectiveProjectionMatrix(FieldOfView,(float)ViewPort.width/(float)ViewPort.height,zNear,zFar);

    }


    float FieldOfView;
    float zFar;
    float zNear;

    core::vector3df UpVector;
    core::vector3df Target;

    core::matrix4f opm; //ortho
    core::matrix4f ppm; //perspective

    bool update_projection;
    core::dimension2du ViewPort;



};
}
}


#endif // CSCENECAMERA_H
