#ifndef CSceneManager_H
#define CSceneManager_H

#include "Object.h"
#include "Types.h"

#include "NovaEngine.h"
#include "IRenderer.h"

#include "ISceneManager.h"

#include "ISceneNode.h"
#include "ISceneSprite.h"
#include "ISceneCamera.h"

#include "Logger.h"




namespace novaengine
{
namespace scene
{


class CSceneManager : public ISceneManager
{
public:
    CSceneManager(INovaEngine* rootengine);
    virtual ~CSceneManager();

    //----------------------------------------------------ManageScenes
    IScene* getRootScene()
    {
        return RootScene;
    };

    //!Need fix drawing rootscene, before add this.
    /*
    IScene* createScene(s32 SceneID = -1) = 0;

    void deleteScene(IScene* Scene) = 0;
    void deleteScene(s32 SceneID  ) = 0;

    u32     getSceneCount() = 0;
    IScene* getSceneList()  = 0;

    IScene* getSceneByID(s32 SceneID) = 0;
    */

    //----------------------------------------------------SceneNodes
    virtual ISceneSprite* createSceneSprite(renderer::ITexture* SpriteTexture,core::rectf Sourse = core::rectf(0,0,1,1),ISceneNode* parent = 0,s32 ID = -1,core::vector3df position = core::vector3df(0,0,0),core::vector3df rotation= core::vector3df(0,0,0),core::vector3df scale= core::vector3df(1,1,1));
    virtual ISceneTileMap* createSceneTileMap(renderer::ITileMap* tilemap,ISceneNode* parent = 0,s32 ID = -1,core::vector3df position = core::vector3df(0,0,0),core::vector3df rotation= core::vector3df(0,0,0),core::vector3df scale= core::vector3df(1,1,1));
    virtual ISceneCamera* createSceneCamera(f32 Far = 1000,f32 Near = 1,f32 FOV = 90,ISceneNode* parent = 0,s32 ID = -1,core::vector3df position = core::vector3df(0,0,0),core::vector3df rotation = core::vector3df(0,0,0));
    //--------------------------------------------------------------
    virtual void setRenderGridResolution(core::dimension2du grid_resolution);
    virtual core::dimension2du  getRenderGridResolution();
    //ActiveProjection
    virtual void useProjectionMatrix(E_PROJECTION_MATRIX);
    virtual void useViewMatrix(E_VIEW_MATRIX);

    void setActiveScene(IScene* Scene = 0);
    IScene* getActiveScene();
    void renderScene();

    renderer::IRenderer* getRenderer();

protected:
private:

    IScene*      ActiveScene;
    IScene*      RootScene;


    core::dimension2du RenderGridResolution;
    //Projections
    core::matrix4f PerspectiveProjection;
    core::matrix4f OrthographicProjection;
    //LookAtMatrix
    core::matrix4f ViewMatrix_2d;
    core::matrix4f ViewMatrix_3d;


    INovaEngine* Engine;
    renderer::IRenderer* Renderer;

};

}
}

#endif // CSceneManager_H
