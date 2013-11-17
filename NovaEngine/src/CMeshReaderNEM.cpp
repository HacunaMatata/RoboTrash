#include "CMeshReaderNEM.h"

#include "CVertexArray.h"
#include "CMesh.h"

namespace novaengine
{
CMeshReaderNEM::CMeshReaderNEM(io::IFileSystem* fs)
{
    FileSys = fs;
}
//--------------------------------------------------------------------------------------------------------
CMeshReaderNEM::~CMeshReaderNEM()
{
    //dtor
}
//--------------------------------------------------------------------------------------------------------
bool CMeshReaderNEM::isSupported(const char* file_extension)
{
    if(strcmp(file_extension,".nem") == 0)
        return 1;
    return 0;
}
//--------------------------------------------------------------------------------------------------------
bool CMeshReaderNEM::isSupported(io::IFile* file)
{
    SNEMFileHeader header;
    file->read(&header,sizeof(SNEMFileHeader));
    file->seek(file->getLastPos());
    if(header.magic == 0x4d454e13)
        return true;
    return false;
}
//--------------------------------------------------------------------------------------------------------
scene::IMesh* CMeshReaderNEM::LoadMesh(const char* path)
{
    io::IFile* nem_file = FileSys->open_file(path);

    if(!nem_file)
        return NULL;

    scene::IMesh* mesh = LoadMesh(nem_file);

    nem_file->release();

    if(!mesh)
        return NULL;

    return mesh;
}
//--------------------------------------------------------------------------------------------------------
scene::IMesh* CMeshReaderNEM::LoadMesh(io::IFile* file)
{
    u32 FileStart = file->getPos();

    scene::IMesh* mesh  = LoadNEM(file);

    file->seek(FileStart);

    return mesh;
}
//--------------------------------------------------------------------------------------------------------
scene::IMesh* CMeshReaderNEM::LoadNEM(io::IFile* file)
{
    SNEMFileHeader header;

    file->read(&header,sizeof(SNEMFileHeader));
    if(header.magic != 0x4d454e13)
    {
        io::Log::println("Failed to load mesh - corrupted data[not nem]",ELL_DEBUG_APP);
    }

    //----------------------------------------------------------------------------------
    scene::IMesh* Mesh = new scene::CMesh();
    u32 LoadedVertexGroups = 0;
    //----------------------------------------------------------------------------------
    if(header.version = 0x00010000)
    {
        SNEMDataHeaderV1 dheader;
        file->read(&dheader,sizeof(SNEMDataHeaderV1));

        renderer::SVertex* verticles = new renderer::SVertex[dheader.vertex_count];
        file->read(verticles,sizeof(renderer::SVertex) * dheader.vertex_count);

        u32 VertexFormat = 0;
        if(dheader.vertex_struct & 1)
            VertexFormat |= renderer::EVF_VERTEX;
        if(dheader.vertex_struct & 2)
            VertexFormat |= renderer::EVF_TEXCOORD;
        if(dheader.vertex_struct & 4)
            VertexFormat |= renderer::EVF_NORMAL;

        renderer::IVertexArray* VertexArray = new renderer::CVertexArray(verticles,dheader.vertex_count,renderer::EPT_TRIANGLES,VertexFormat);
        Mesh->addVertexArray(VertexArray);
        LoadedVertexGroups++;
    }

    if(LoadedVertexGroups)
    {
        return Mesh;
    }
    else
    {
        Mesh->release();
        return NULL;
    }
}
//--------------------------------------------------------------------------------------------------------
}
