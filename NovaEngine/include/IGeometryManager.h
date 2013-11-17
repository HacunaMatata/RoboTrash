#ifndef IGEOMETRYMANAGER_H
#define IGEOMETRYMANAGER_H

#include "Object.h"
#include "Types.h"

#include "ITileMap.h"

namespace novaengine
{

namespace renderer
{
class IVertexArray;
}

/// \brief Provides work with geometry (create simple geometry) also use ResourceManager to load mesh files
class IGeometryManager : public Object
{
    public:

        virtual renderer::IVertexArray* createCubeMesh()    = 0;
        virtual renderer::IVertexArray* createSphereMesh(float Radius,unsigned int Resolution)  = 0;
        virtual renderer::IVertexArray* createGridMesh(core::dimension2df CellSize,core::dimension2du CellCount) = 0;

        //for small tilemaps
        virtual renderer::ITileMap* buildTileMap(core::dimension2df CellSize,core::dimension2du CellCount,renderer::ITexture* TileSet) = 0;

    protected:
    private:
};

}

#endif // IGEOMETRYMANAGER_H
