#ifndef ISCENETILEMAP_H
#define ISCENETILEMAP_H

#include "IScene2DNode.h"
#include "ITileMap.h"


namespace novaengine
{
namespace scene
{

class ISceneTileMap : public IScene2DNode
{
    public:
        ISceneTileMap(ISceneManager* smgr,renderer::ITileMap* tilemap,ISceneNode* parent = 0,s32 ID = -1,core::vector3df position = core::vector3df(0,0,0),core::vector3df rotation= core::vector3df(0,0,0),core::vector3df scale= core::vector3df(1,1,1)):
        IScene2DNode(smgr,parent,ID,position,rotation,scale) {}

        virtual renderer::ITileMap* getTileMap() = 0;

    protected:
    private:
};
typedef ISceneTileMap* snTileMap;
}
}
#endif // ISCENETILEMAP_H
