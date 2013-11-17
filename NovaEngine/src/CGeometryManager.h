#ifndef CGEOMETRYMANAGER_H
#define CGEOMETRYMANAGER_H

#include "Object.h"
#include "INovaEngine.h"
#include "IGeometryManager.h"


namespace novaengine
{

class CGeometryManager : public IGeometryManager
{
    public:
        CGeometryManager(IResourceManager* ResourceManager_param);
        virtual ~CGeometryManager();

        renderer::IVertexArray* createCubeMesh();
        renderer::IVertexArray* createSphereMesh(float Radius,unsigned int Resolution);
        renderer::IVertexArray* createGridMesh(core::dimension2df,core::dimension2du);

        renderer::ITileMap* buildTileMap(core::dimension2df CellSize,core::dimension2du CellCount,renderer::ITexture* TileSet);

    protected:
    private:
    IResourceManager* ResourceManager;
};

}
#endif // CGEOMETRYMANAGER_H
