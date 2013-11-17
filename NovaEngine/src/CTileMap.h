#ifndef CTILEMAP_H
#define CTILEMAP_H

#include "Logger.h"

#include "ITileMap.h"
#include "IVertexArray.h"
#include <vector>

namespace novaengine
{
namespace renderer
{
//----------------------------------------------------------------------------------------------------------
class CTileMap : public ITileMap
{
public:
    CTileMap(core::dimension2df ctr_TileResolution,core::dimension2du ctr_ChunkResolution,IVertexArray* ctr_Mesh,renderer::ITexture* ctr_TileSet):
        TileResolution(ctr_TileResolution),
        TileMapResolution(ctr_ChunkResolution),
        TileMap(ctr_Mesh)
    {
        TileMap->capture();

         Material = new CMaterial();
         Material->setMaterialTexture(ctr_TileSet);
    }
    virtual ~CTileMap()
    {
        TileMap->release();

        if(Material)
            Material->release();
    }

    core::dimension2df getTileResolution()
    {
        return TileResolution;
    }
    core::dimension2du getTileMapResolution()
    {
        return TileMapResolution;
    }

    STile getTile(core::vector2ds Coord)
    {
        //Need convert coord in vertex index
        u32 index = (Coord.y * TileMapResolution.width * 4) + Coord.x * 4;

        //If invalid coords - exit
        if(index >= TileMap->getVertexCount())
            return STile();

        //get right top and left bottom verticles
        SVertex* verticles = new SVertex[2];
        verticles[0] = *TileMap->getVertex(index + 0);
        verticles[1] = *TileMap->getVertex(index + 2);

        //calculate texture source rect
        STile Tile;
        Tile.Tile_TextureCoord.X1 = verticles[0].TexCoord.x;
        Tile.Tile_TextureCoord.Y1 = verticles[0].TexCoord.y;
        Tile.Tile_TextureCoord.X2 = verticles[1].TexCoord.x;
        Tile.Tile_TextureCoord.Y2 = verticles[1].TexCoord.y;

        Tile.Tile_Color           = verticles[0].VertexColor;

        delete[] verticles;

        return Tile;
    }
    void setTile(core::vector2ds Coord,STile Tile)
    {
        //Need convert coord in vertex index
        u32 index = (Coord.y * TileMapResolution.width * 4) + Coord.x * 4;

        //If invalid coords -> exit
        if(index >= TileMap->getVertexCount())
            return;

        //set new texture coords
        TileMap->getVertex(index + 0)->TexCoord = core::vector2df(Tile.Tile_TextureCoord.X1,Tile.Tile_TextureCoord.Y1);
        TileMap->getVertex(index + 1)->TexCoord = core::vector2df(Tile.Tile_TextureCoord.X1,Tile.Tile_TextureCoord.Y2);
        TileMap->getVertex(index + 2)->TexCoord = core::vector2df(Tile.Tile_TextureCoord.X2,Tile.Tile_TextureCoord.Y2);
        TileMap->getVertex(index + 3)->TexCoord = core::vector2df(Tile.Tile_TextureCoord.X2,Tile.Tile_TextureCoord.Y1);
        //set new color

        TileMap->getVertex(index + 0)->VertexColor = Tile.Tile_Color;
        TileMap->getVertex(index + 1)->VertexColor = Tile.Tile_Color;
        TileMap->getVertex(index + 2)->VertexColor = Tile.Tile_Color;
        TileMap->getVertex(index + 3)->VertexColor = Tile.Tile_Color;

        if(TileMap->get_vbo_pointer())
            TileMap->get_vbo_pointer()->request_rebuild();

    }
    void setAllTiles(STile Tile)
    {

        for(u32 x = 0; x < TileMapResolution.width;x++)
        {
            for(u32 y = 0; y < TileMapResolution.height;y++)
            {
                setTile(core::vector2ds(x,y),Tile);
            }
        }

    }
    void setTileMapMaterial(IMaterial* newMaterial)
    {
        if(newMaterial)
            newMaterial->capture();

        if(Material)
            Material->release();

        Material = newMaterial;
    }

    IMaterial* getTileMapMaterial()
    {
        return Material;
    }

    IVertexArray* getVertexArray()
    {
        return TileMap;
    }


protected:
private:
    IVertexArray* TileMap;
    IMaterial*    Material;

    core::dimension2df TileResolution;
    core::dimension2du TileMapResolution;


};

}
}
#endif // CTILEMAP_H
