#ifndef CSCENETILEMAP_H
#define CSCENETILEMAP_H

#include "ITileMap.h"
#include "ISceneTileMap.h"

namespace novaengine
{
namespace scene
{

class CSceneTileMap : public ISceneTileMap
{
    public:
    CSceneTileMap(ISceneManager* smgr,renderer::ITileMap* tilemap,ISceneNode* parent = 0,s32 ID = -1,core::vector3df position = core::vector3df(0,0,0),core::vector3df rotation= core::vector3df(0,0,0),core::vector3df scale= core::vector3df(1,1,1)):
    ISceneTileMap(smgr,tilemap,parent,ID,position,rotation,scale)
    {
        TileMap = tilemap;

        if(TileMap)
            TileMap->capture();

    }
    virtual ~CSceneTileMap()
    {

        if(TileMap)
            TileMap->release();

    }

    renderer::ITileMap* getTileMap()
    {
        return TileMap;
    }

     void setMaterial(renderer::IMaterial* newMaterial,u32 Material_index = 0)
    {
        TileMap->setTileMapMaterial(newMaterial);

    };
    renderer::IMaterial* getMaterial(u32 Material_index = 0)
    {
        return TileMap->getTileMapMaterial();
    };


    void render()
    {
        ISceneNode::render();

        renderer::IRenderer* Renderer = SceneManager->getRenderer();

        if(!isVisible())
            return;

        SceneManager->useProjectionMatrix(EPM_ORTHO);
        SceneManager->useViewMatrix(EVM_2D);

        Renderer->setTransform(getAbsoluteTransformation(),renderer::EMT_MODEL);

        //Renderer->setRenderState(renderer::ERS_ENABLE_DEPTH_TEST,0);
        Renderer->setActiveMaterial(TileMap->getTileMapMaterial());
        Renderer->drawVertexArray(TileMap->getVertexArray());
        //Renderer->setRenderState(renderer::ERS_ENABLE_DEPTH_TEST,1);
    }

    protected:
    private:

    renderer::ITileMap* TileMap;
};

}
}
#endif // CSCENETILEMAP_H
