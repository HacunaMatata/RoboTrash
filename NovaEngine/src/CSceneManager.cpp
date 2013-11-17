#include "CSceneManager.h"

//Scene
#include "CScene.h"
//Nodes
#include "CSceneSprite.h"
#include "CSceneTileMap.h"
#include "CSceneCamera.h"

namespace novaengine
{
namespace scene
{

CSceneManager::CSceneManager(INovaEngine* rootengine)
{
    Engine = rootengine;
    Renderer = rootengine->getRenderer();

	ActiveScene = NULL;
	
    RootScene = new CScene(this);
    RootScene->setActive();
}
//--------------------------------------------------------------------------------------------
CSceneManager::~CSceneManager()
{
    RootScene->release();
}
//--------------------------------------------------------------------------------------------
renderer::IRenderer* CSceneManager::getRenderer()
{
    return Renderer;
}
//--------------------------------------------------------------------------------------------
ISceneSprite* CSceneManager::createSceneSprite(renderer::ITexture* SpriteTexture,core::rectf Source,ISceneNode* parent,s32 ID,core::vector3df position,core::vector3df rotation,core::vector3df scale)
{
    ISceneSprite* sn_sprite = new CSceneSprite(this,SpriteTexture,Source,parent,ID,position,rotation,scale);

    if(ActiveScene)
        ActiveScene->RegisterNode(sn_sprite);

    return sn_sprite;
}
//--------------------------------------------------------------------------------------------
ISceneTileMap* CSceneManager::createSceneTileMap(renderer::ITileMap* tilemap,ISceneNode* parent,s32 ID,core::vector3df position,core::vector3df rotation,core::vector3df scale)
{
    ISceneTileMap* sn_tilemap = new CSceneTileMap(this,tilemap,parent,ID,position,rotation,scale);

    if(ActiveScene)
        ActiveScene->RegisterNode(sn_tilemap);

    return sn_tilemap;
}
//--------------------------------------------------------------------------------------------
ISceneCamera* CSceneManager::createSceneCamera(f32 Far,f32 Near,f32 FOV,ISceneNode* parent,s32 ID,core::vector3df position,core::vector3df rotation)
{
    ISceneCamera* sn_camera = new CSceneCamera(this,Far,Near,FOV,parent,ID,position,rotation);

    if(ActiveScene)
    {
        ActiveScene->RegisterNode(sn_camera);

        if(ActiveScene->getActiveCamera() == NULL)
            ActiveScene->setActiveCamera(sn_camera);

    }
    return sn_camera;
}
//--------------------------------------------------------------------------------------------
void CSceneManager::setRenderGridResolution(core::dimension2du grid_resolution)
{
    RenderGridResolution = grid_resolution;
}
//--------------------------------------------------------------------------------------------
core::dimension2du  CSceneManager::getRenderGridResolution()
{
    return RenderGridResolution;
}
//--------------------------------------------------------------------------------------------
void CSceneManager::useProjectionMatrix(E_PROJECTION_MATRIX prj)
{
    ISceneCamera* Cam = ActiveScene->getActiveCamera();
    core::matrix4f  newProjection;

    switch(prj)
    {
    case EPM_ORTHO:
        //--------------------------------
        if(Cam)
            OrthographicProjection = ActiveScene->getActiveCamera()->getOrthographicProjectionMatrix();

        Renderer->setTransform(OrthographicProjection,renderer::EMT_PROJECTION);
        //--------------------------------
        break;

    case EPM_PERSPECTIVE:
        //--------------------------------
        if(Cam)
            PerspectiveProjection = Cam->getPerspectiveProjectionMatrix();

        Renderer->setTransform(PerspectiveProjection,renderer::EMT_PROJECTION);
        //--------------------------------
        break;
    case EPM_UNDEFINED:
        PerspectiveProjection = core::matrix4f();
        break;
    default:
        io::Log::println("Unknow projection matrix type",ELL_ERROR);
    }
}
//--------------------------------------------------------------------------------------------
void CSceneManager::useViewMatrix(E_VIEW_MATRIX view)
{
    ISceneCamera* Cam = ActiveScene->getActiveCamera();
    core::matrix4f newViewMatrix;

    switch(view)
    {
    case EVM_2D:
        //--------------------------------
        if(Cam)
            ViewMatrix_2d = Cam->get2DViewMatrix();

        Renderer->setTransform(ViewMatrix_2d,renderer::EMT_VIEW);
        //--------------------------------
        break;

    case EVM_3D:
        //--------------------------------
        if(Cam)
            ViewMatrix_3d = Cam->get3DViewMatrix();
        Renderer->setTransform(ViewMatrix_3d,renderer::EMT_VIEW);
        //--------------------------------
        break;
    case EVM_UNDEFINED:
        ViewMatrix_2d = core::matrix4f();
        ViewMatrix_3d = core::matrix4f();
        break;
    default:
        io::Log::println("Unknow view matrix type",ELL_ERROR);
    }
}
//--------------------------------------------------------------------------------------------
void CSceneManager::setActiveScene(IScene* Scene)
{
    if(Scene)
        ActiveScene = Scene;
    else
        ActiveScene = RootScene;
}
//--------------------------------------------------------------------------------------------
IScene* CSceneManager::getActiveScene()
{
    return ActiveScene;
}
//--------------------------------------------------------------------------------------------
void CSceneManager::renderScene()
{
    ActiveScene->update();
    ActiveScene->animate();
    ActiveScene->render();
}
//--------------------------------------------------------------------------------------------
}
}


