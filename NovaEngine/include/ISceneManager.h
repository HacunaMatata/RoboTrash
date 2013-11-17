#ifndef ISceneManager_H
#define ISceneManager_H

#include "Object.h"
#include "Types.h"

#include "ITexture.h"
#include "ITileMap.h"

namespace novaengine
{
namespace scene
{

enum E_PROJECTION_MATRIX
{
    EPM_UNDEFINED    = 0x0,
    EPM_ORTHO        = 0x1,
    EPM_PERSPECTIVE  = 0x2,
};
enum E_VIEW_MATRIX
{
    EVM_UNDEFINED = 0x0,
    EVM_2D        = 0x1,
    EVM_3D        = 0x2,
};

enum E_NODE_TYPE
{
    ENT_UNKNOW          = 0x0,
    ENT_SPRITE          = 0x1,
    ENT_MESH            = 0x2,
    ENT_ANIMATED_MESH   = 0x3,
    ENT_CAMERA          = 0x4,
    ENT_LIGHT           = 0x5,
};

class IScene;
class ISceneNode;
class ISceneSprite;
class ISceneTileMap;
class ISceneCamera;

class ISceneManager : public Object
{
public:


    //----------------------------------------------------ManageScenes

    //!Need fix drawing rootscene, before add this.
    /*
    virtual IScene* createScene(s32 SceneID = -1) = 0;

    virtual void deleteScene(IScene* Scene) = 0;
    virtual void deleteScene(s32 SceneID  ) = 0;

    virtual u32     getSceneCount() = 0;
    virtual IScene* getSceneList()  = 0;

    virtual IScene* getSceneByID(s32 SceneID) = 0;
    */

    //----------------------------------------------------SceneNodes
    virtual ISceneSprite*  createSceneSprite(renderer::ITexture* SpriteTexture,core::rectf Sourse = core::rectf(0,0,1,1),ISceneNode* parent = 0,s32 ID = -1,core::vector3df position = core::vector3df(0,0,0),core::vector3df rotation= core::vector3df(0,0,0),core::vector3df scale= core::vector3df(1,1,1)) = 0;
    virtual ISceneTileMap* createSceneTileMap(renderer::ITileMap* tilemap,ISceneNode* parent = 0,s32 ID = -1,core::vector3df position = core::vector3df(0,0,0),core::vector3df rotation= core::vector3df(0,0,0),core::vector3df scale= core::vector3df(1,1,1)) = 0;
    virtual ISceneCamera*  createSceneCamera(f32 Far = 1000,f32 Near = 1,f32 FOV = 90,ISceneNode* parent = 0,s32 ID = -1,core::vector3df position = core::vector3df(0,0,0),core::vector3df rotation = core::vector3df(0,0,0)) = 0;
    //--------------------------------------------------------------
    virtual void setRenderGridResolution(core::dimension2du grid_resolution) = 0;
    virtual core::dimension2du  getRenderGridResolution() = 0;

    //ActiveProjection
    virtual void useProjectionMatrix(E_PROJECTION_MATRIX)  = 0;
    virtual void useViewMatrix(E_VIEW_MATRIX) = 0;


    virtual void setActiveScene(IScene* Scene = 0) = 0;
    virtual IScene* getActiveScene()               = 0;

    virtual void renderScene() = 0;

    virtual IScene* getRootScene()             = 0;

    virtual renderer::IRenderer* getRenderer() = 0;

protected:
private:
};

}
}


#endif // ISceneManager_H
