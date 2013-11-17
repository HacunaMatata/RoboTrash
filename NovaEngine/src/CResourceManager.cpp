#include "CResourceManager.h"
#include "Logger.h"
#include "Timer.h"

//Image readers
#include "CImageReaderTGA.h"
#include "CImageReaderPNG.h"
#include "CImageReaderBMP.h"
//Font readers
#include "CFontReaderSNF.h"
#include "CFontReaderFNT.h"
//Mesh readers
#include "CMeshReaderNEM.h"

namespace novaengine
{

CResourceManager::CResourceManager(io::IFileSystem* FileSystem_param):
    FileSys(FileSystem_param)
{

    registerImageReader((new CImageReaderTGA(FileSys)));
    registerImageReader((new CImageReaderPNG(FileSys)));
    registerImageReader((new CImageReaderBMP(FileSys)));

    registerFontReader((new CFontReaderSNF(FileSys,this)));
    registerFontReader((new CFontReaderFNT(FileSys,this)));

    registerMeshReader((new CMeshReaderNEM(FileSys)));

}
//---------------------------------------------------------------------------------------------
CResourceManager::~CResourceManager()
{
    for(int irl = 0; irl < ImageReaders.size(); irl++)
    {
        if(ImageReaders[irl])
            ImageReaders[irl]->release();
    }

    for(int irl = 0; irl < FontReaders.size(); irl++)
    {
        if(FontReaders[irl])
            FontReaders[irl]->release();
    }

        for(int mrl = 0; mrl < MeshReaders.size(); mrl++)
    {
        if(MeshReaders[mrl])
            MeshReaders[mrl]->release();
    }
}
//---------------------------------------------------------------------------------------------
renderer::IImage* CResourceManager::loadImage(const char* file)
{
    core::cstring path = file;
    core::cstring ext = path.substr(path.find_last_of("."),path.length() - path.find_last_of("."));

    for(int irl = 0; irl < ImageReaders.size(); irl++)
    {
        if(ImageReaders[irl]->isSupported(ext.c_str()))
        {
            u32 time = Timer::getTime();
            renderer::IImage* img = ImageReaders[irl]->LoadImage(file);
            if(img)
            {
                char str[256];
                sprintf(str,"Texture loaded : %s [%d ms]\n",file,Timer::getTime() - time);
                io::Log::print(str,ELL_INFO);
                return img;
            }
            io::Log::println("Texture not loaded",path.c_str(),ELL_ERROR);
            return NULL;
        }
    }
    io::Log::println("Unknow image format",ext.c_str(),ELL_ERROR);
    return NULL;
}
//---------------------------------------------------------------------------------------------
renderer::IImage* CResourceManager::loadImage(io::IFile*  file)
{
    for(int irl = 0; irl < ImageReaders.size(); irl++)
    {
        if(ImageReaders[irl]->isSupported(file))
        {
            u32 time = Timer::getTime();
            renderer::IImage* img = ImageReaders[irl]->LoadImage(file);
            if(img)
            {
                char str[256];
                sprintf(str,"Texture from stream(%s) loaded [%d ms]\n",file->getName(),Timer::getTime() - time);
                io::Log::print(str,ELL_INFO);
                return img;
            }
            io::Log::println("Texture from stream not loaded",ELL_ERROR);
            return NULL;
        }
    }
    io::Log::println("Unknow image format",ELL_ERROR);
    return NULL;
}
//---------------------------------------------------------------------------------------------
bool CResourceManager::saveImage(const char* file)
{
    return false;
}
//---------------------------------------------------------------------------------------------
gui::IFont* CResourceManager::loadFont(const char* file)
{
    core::cstring path = file;
    core::cstring ext = path.substr(path.find_last_of("."),path.length() - path.find_last_of("."));

    for(int frl = 0; frl < FontReaders.size(); frl++)
    {
        if(FontReaders[frl]->isSupported(ext.c_str()))
        {
            u32 time = Timer::getTime();
            gui::IFont* font = 0;
            font = FontReaders[frl]->LoadFont(file);
            if(font)
            {
                char str[256];
                sprintf(str,"Font loaded : %s [%d ms]\n",file,Timer::getTime() - time);
                io::Log::print(str,ELL_INFO);
                return font;
            }
            io::Log::println("Font not loaded",path.c_str(),ELL_ERROR);
            return NULL;
        }
    }
    io::Log::println("Unknow font format",ext.c_str(),ELL_ERROR);
    return NULL;
}
//---------------------------------------------------------------------------------------------
gui::IFont* CResourceManager::loadFont(io::IFile*  file)
{
    for(int frl = 0; frl < FontReaders.size(); frl++)
    {
        if(FontReaders[frl]->isSupported(file))
        {
            u32 time = Timer::getTime();
            gui::IFont* font = FontReaders[frl]->LoadFont(file);
            if(font)
            {
                char str[256];
                sprintf(str,"Font from stream(%s) loaded [%d ms]\n",file->getName(),Timer::getTime() - time);
                io::Log::print(str,ELL_INFO);
                return font;
            }
            io::Log::println("Font from stream not loaded",ELL_ERROR);
            return NULL;
        }
    }
    io::Log::println("Unknow font format",ELL_ERROR);
    return NULL;
}
//---------------------------------------------------------------------------------------------
scene::IMesh* CResourceManager::loadMesh(const char* file)
{
    core::cstring path = file;
    core::cstring ext = path.substr(path.find_last_of("."),path.length() - path.find_last_of("."));

    for(int mrl = 0; mrl < MeshReaders.size(); mrl++)
    {
        if(MeshReaders[mrl]->isSupported(ext.c_str()))
        {
            u32 time = Timer::getTime();
            scene::IMesh* mesh = MeshReaders[mrl]->LoadMesh(file);
            if(mesh)
            {
                char str[256];
                sprintf(str,"Mesh loaded : %s [%d ms]\n",file,Timer::getTime() - time);
                io::Log::print(str,ELL_INFO);
                return mesh;
            }
            io::Log::println("Mesh not loaded",path.c_str(),ELL_ERROR);
            return NULL;
        }
    }
    io::Log::println("Unknow mesh format",ext.c_str(),ELL_ERROR);
    return NULL;
}
//---------------------------------------------------------------------------------------------
scene::IMesh* CResourceManager::loadMesh(io::IFile*  file)
{
    for(int mrl = 0; mrl < MeshReaders.size(); mrl++)
    {
        if(MeshReaders[mrl]->isSupported(file))
        {
            u32 time = Timer::getTime();
            scene::IMesh* mesh = MeshReaders[mrl]->LoadMesh(file);
            if(mesh)
            {
                char str[256];
                sprintf(str,"Mesh mesh stream(%s) loaded [%d ms]\n",file->getName(),Timer::getTime() - time);
                io::Log::print(str,ELL_INFO);
                return mesh;
            }
            io::Log::println("Mesh mesh stream not loaded",ELL_ERROR);
            return NULL;
        }
    }
    io::Log::println("Unknow mesh format",ELL_ERROR);
    return NULL;
}
//---------------------------------------------------------------------------------------------
void CResourceManager::registerFontReader(IFontReader* newReader)
{
    if(newReader)
    {
        FontReaders.push_back(newReader);
    }
}
//---------------------------------------------------------------------------------------------
void CResourceManager::registerImageReader(IImageReader* newReader)
{
    if(newReader)
    {
        ImageReaders.push_back(newReader);
    }
}
//---------------------------------------------------------------------------------------------
void CResourceManager::registerMeshReader(IMeshReader* newReader)
{
    if(newReader)
    {
        MeshReaders.push_back(newReader);
    }
}
//---------------------------------------------------------------------------------------------
void CResourceManager::registerImageWriter()
{

}
//---------------------------------------------------------------------------------------------
}
