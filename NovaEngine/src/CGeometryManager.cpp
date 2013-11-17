#include "CGeometryManager.h"

#include "CVertexArray.h"
#include "CTileMap.h"

namespace novaengine
{

CGeometryManager::CGeometryManager(IResourceManager* ResourceManager_param):
    ResourceManager(ResourceManager_param)
{

}
//--------------------------------------------------------------------------------------------------------
CGeometryManager::~CGeometryManager()
{
    //dtor
}
//--------------------------------------------------------------------------------------------------------
renderer::IVertexArray* CGeometryManager::createCubeMesh()
{

    renderer::SVertex* verticles = new renderer::SVertex[36];
    //front
    verticles[0].Position = core::vector3df( 1, 1,1);
    verticles[1].Position = core::vector3df(-1, 1,1);
    verticles[2].Position = core::vector3df(-1,-1,1);
    verticles[3].Position = core::vector3df(-1,-1,1);
    verticles[4].Position = core::vector3df( 1,-1,1);
    verticles[5].Position = core::vector3df( 1, 1,1);

    verticles[0].TexCoord = core::vector2df(1,0);
    verticles[1].TexCoord = core::vector2df(0,0);
    verticles[2].TexCoord = core::vector2df(0,1);
    verticles[3].TexCoord = core::vector2df(0,1);
    verticles[4].TexCoord = core::vector2df(1,1);
    verticles[5].TexCoord = core::vector2df(1,0);
    //back
    verticles[6].Position  = core::vector3df( 1,-1,-1);
    verticles[7].Position  = core::vector3df(-1,-1,-1);
    verticles[8].Position  = core::vector3df(-1, 1,-1);
    verticles[9].Position  = core::vector3df(-1, 1,-1);
    verticles[10].Position = core::vector3df( 1, 1,-1);
    verticles[11].Position = core::vector3df( 1,-1,-1);

    verticles[6].TexCoord = core::vector2df(0,1);
    verticles[7].TexCoord = core::vector2df(1,1);
    verticles[8].TexCoord = core::vector2df(1,0);
    verticles[9].TexCoord = core::vector2df(1,0);
    verticles[10].TexCoord = core::vector2df(0,0);
    verticles[11].TexCoord = core::vector2df(0,1);
    //right
    verticles[12].Position = core::vector3df(1, 1,-1);
    verticles[13].Position = core::vector3df(1, 1, 1);
    verticles[14].Position = core::vector3df(1,-1, 1);
    verticles[15].Position = core::vector3df(1,-1, 1);
    verticles[16].Position = core::vector3df(1,-1,-1);
    verticles[17].Position = core::vector3df(1, 1,-1);

    verticles[12].TexCoord = core::vector2df(1,0);
    verticles[13].TexCoord = core::vector2df(0,0);
    verticles[14].TexCoord = core::vector2df(0,1);
    verticles[15].TexCoord = core::vector2df(0,1);
    verticles[16].TexCoord = core::vector2df(1,1);
    verticles[17].TexCoord = core::vector2df(1,0);
    //left
    verticles[18].Position  = core::vector3df(-1,-1,-1);
    verticles[19].Position  = core::vector3df(-1,-1, 1);
    verticles[20].Position  = core::vector3df(-1, 1, 1);
    verticles[21].Position  = core::vector3df(-1, 1, 1);
    verticles[22].Position  = core::vector3df(-1, 1,-1);
    verticles[23].Position  = core::vector3df(-1,-1,-1);

    verticles[18].TexCoord = core::vector2df(0,1);
    verticles[19].TexCoord = core::vector2df(1,1);
    verticles[20].TexCoord = core::vector2df(1,0);
    verticles[21].TexCoord = core::vector2df(1,0);
    verticles[22].TexCoord = core::vector2df(0,0);
    verticles[23].TexCoord = core::vector2df(0,1);
    //top
    verticles[24].Position = core::vector3df( 1,1,-1);
    verticles[25].Position = core::vector3df(-1,1,-1);
    verticles[26].Position = core::vector3df(-1,1, 1);
    verticles[27].Position = core::vector3df(-1,1, 1);
    verticles[28].Position = core::vector3df( 1,1, 1);
    verticles[29].Position = core::vector3df( 1,1,-1);

    verticles[24].TexCoord = core::vector2df(1,0);
    verticles[25].TexCoord = core::vector2df(0,0);
    verticles[26].TexCoord = core::vector2df(0,1);
    verticles[27].TexCoord = core::vector2df(0,1);
    verticles[28].TexCoord = core::vector2df(1,1);
    verticles[29].TexCoord = core::vector2df(1,0);
    //bottom
    verticles[30].Position = core::vector3df( 1,-1, 1);
    verticles[31].Position = core::vector3df(-1,-1, 1);
    verticles[32].Position = core::vector3df(-1,-1,-1);
    verticles[33].Position = core::vector3df(-1,-1,-1);
    verticles[34].Position = core::vector3df( 1,-1,-1);
    verticles[35].Position = core::vector3df( 1,-1, 1);

    verticles[30].TexCoord = core::vector2df(0,1);
    verticles[31].TexCoord = core::vector2df(1,1);
    verticles[32].TexCoord = core::vector2df(1,0);
    verticles[33].TexCoord = core::vector2df(1,0);
    verticles[34].TexCoord = core::vector2df(0,0);
    verticles[35].TexCoord = core::vector2df(0,1);

    renderer::IVertexArray* buf = new renderer::CVertexArray(verticles,36,renderer::EPT_TRIANGLES,renderer::EVF_VERTEX | renderer::EVF_TEXCOORD);
    delete verticles;
    return buf;
}
//--------------------------------------------------------------------------------------------------------
renderer::IVertexArray* CGeometryManager::createGridMesh(core::dimension2df CellSize,core::dimension2du CellCount)
{
    //----------------------------
    renderer::IVertexArray* Mesh = new renderer::CVertexArray();
    if(Mesh == NULL)
        return NULL;
    //----------------------------
    Mesh->reserve_vertex_space(CellCount.width * CellCount.height * 4);


    u32 indices[CellCount.width * CellCount.height * 6];

    u32 vp = 0;
    u32 ip = 0;

    for(u32 y_tile = 0; y_tile < CellCount.height; y_tile++)
    {
        for(u32 x_tile = 0; x_tile < CellCount.width; x_tile++)
        {
            renderer::SVertex Quad[4];

            Quad[0].Position = core::vector3df((x_tile * CellSize.width),(y_tile * CellSize.height)+CellSize.height,0);
            Quad[1].Position = core::vector3df((x_tile * CellSize.width),(y_tile * CellSize.height),0);
            Quad[2].Position = core::vector3df((x_tile * CellSize.width)+CellSize.width,(y_tile * CellSize.height),0);
            Quad[3].Position = core::vector3df((x_tile * CellSize.width)+CellSize.width,(y_tile * CellSize.height)+CellSize.height,0);

            Quad[0].TexCoord = core::vector2df(0,0);
            Quad[1].TexCoord = core::vector2df(0,1);
            Quad[2].TexCoord = core::vector2df(1,1);
            Quad[3].TexCoord = core::vector2df(1,0);


            Mesh->addVerticles(Quad,4);

            indices[ip + 0] = vp + 0;
            indices[ip + 1] = vp + 1;
            indices[ip + 2] = vp + 2;
            indices[ip + 3] = vp + 2;
            indices[ip + 4] = vp + 3;
            indices[ip + 5] = vp + 0;

            vp+=4;
            ip+=6;
        }
    }

    Mesh->setIndices(indices,ip);
    Mesh->setPrimitiveType(renderer::EPT_TRIANGLES);
    Mesh->setVertexFormat(renderer::EVF_VERTEX | renderer::EVF_TEXCOORD | renderer::EVF_VERTEX_COLOR);

    Mesh->moveVerticles(core::vector3df(-(CellSize.width*CellCount.width)/2,-(CellSize.height*CellCount.height)/2,0));

    Mesh->setArrayType(renderer::EVAT_RAWDATA);
    return Mesh;
}
//--------------------------------------------------------------------------------------------------------
renderer::IVertexArray* CGeometryManager::createSphereMesh(float Radius,unsigned int Resolution)
{
    if(Resolution < 4)
        Resolution = 4;


    u32 VCount = (Resolution+1) * (Resolution+1);
    u32 ICount = (Resolution*Resolution) * 6;

    renderer::SVertex* vertex = new renderer::SVertex[VCount];
    u32* Indices              = new u32[ICount];

    //(x, y, z) = (sin(Pi * m/M) cos(2Pi * n/N), sin(Pi * m/M) sin(2Pi * n/N), cos(Pi * m/M))

    u32 v = 0;

    for(u32 x = 0; x < Resolution+1; x++)
    {
        f32 AngleX = 2 * core::PI64 * x / Resolution;

        for(u32 y = 0; y < Resolution+1; y++)
        {

            float  AngleY = core::PI64 * y / Resolution;

            core::vector3df result_vertex(sinf(AngleY) * cosf(AngleX) * Radius, cosf(AngleY)* Radius, sinf(AngleX) * sinf(AngleY)* Radius);
            vertex[v].Position = result_vertex;
            vertex[v].TexCoord = core::vector2df(float(x) / Resolution,float(y) / Resolution);
            v++;
        }
    }

    v = 0;

    for(u32 x = 0; x < Resolution; x++)
    {
        for(u32 y = 0; y < Resolution; y++)
        {
            u32 vertex_num = x + (y*(Resolution+1));
            Indices[v]   = vertex_num;
            Indices[v+1] = vertex_num+(Resolution+1);
            Indices[v+2] = vertex_num+(Resolution+2);
            Indices[v+3] = vertex_num+(Resolution+2);
            Indices[v+4] = vertex_num+1;
            Indices[v+5] = vertex_num;
            v+=6;
        }
    }

    /*
    for(u32 i = 0; i < VCount; i++)
    {
        Indices[v]   = i;
        Indices[v+1] = i+(Resolution+1);
        Indices[v+2] = i+(Resolution+2);
        Indices[v+3] = i+(Resolution+2);
        Indices[v+4] = i+1;
        Indices[v+5] = i;


        if(i >= (VCount-1) - Resolution)
        {
            Indices[v+1]-=VCount;
            Indices[v+2]-=VCount;
            Indices[v+3]-=VCount;
        }

        for(u32 z = 0; z < 6;z++)
        {
            printf("%u (%.2f,%.2f,%.2f) > \n",Indices[v+z],vertex[Indices[v+z]].Position.x,vertex[Indices[v+z]].Position.y,vertex[Indices[v+z]].Position.z);
        }
        printf("\n");

        v+=6;
    }
    */



    renderer::IVertexArray* va = new renderer::CVertexArray();

    va->addVerticles(vertex,VCount);
    va->setIndices(Indices,ICount);


    va->setArrayType(renderer::EVAT_RAWDATA);
    va->setVertexFormat(renderer::EVF_VERTEX | renderer::EVF_TEXCOORD);
    va->setPrimitiveType(renderer::EPT_TRIANGLES);

    delete[] vertex;
    delete[] Indices;

    return va;
}
//--------------------------------------------------------------------------------------------------------
renderer::ITileMap* CGeometryManager::buildTileMap(core::dimension2df CellSize,core::dimension2du CellCount,renderer::ITexture* TileSet)
{
    renderer::IVertexArray* grid = createGridMesh(CellSize,CellCount);
    renderer::ITileMap* tilemap = new renderer::CTileMap(CellSize,CellCount,grid,TileSet);
    grid->release();
    return tilemap;
}
//--------------------------------------------------------------------------------------------------------
}
