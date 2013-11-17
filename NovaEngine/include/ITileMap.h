#ifndef ITILEMAP_H
#define ITILEMAP_H


#include "Types.h"
#include "Object.h"
#include "IRenderer.h"
#include "IVertexArray.h"

namespace novaengine
{
namespace renderer
{

struct STile
{
    core::rectf   Tile_TextureCoord;
    core::color4u Tile_Color;
};
class ITileMap : public Object
{
    public:
    virtual core::dimension2df getTileResolution()    = 0;
    virtual core::dimension2du getTileMapResolution() = 0;

    virtual STile getTile(core::vector2ds Coord)      = 0;
    virtual void setTile(core::vector2ds Coord,STile) = 0;
    virtual void setAllTiles(STile) = 0;

    virtual void setTileMapMaterial(IMaterial*) = 0;
    virtual IMaterial* getTileMapMaterial()     = 0;

    virtual IVertexArray* getVertexArray() = 0;

protected:
private:
};

}
}

#endif // ITILEMAP_H
