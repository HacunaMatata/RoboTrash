#ifndef CRESOURCEMANAGER_H
#define CRESOURCEMANAGER_H

#include "INovaEngine.h"
#include "IFileSystem.h"
#include "IResourceManager.h"




namespace novaengine
{

class CResourceManager : public IResourceManager
{
public:
    CResourceManager(io::IFileSystem* FileSystem_param);
    virtual ~CResourceManager();

    //--Graphics
    renderer::IImage*     loadImage(const char* file);
    renderer::IImage*     loadImage(io::IFile*  file);

    bool saveImage(const char* file);
    //--Fonts
    gui::IFont* loadFont(const char* file);
    gui::IFont* loadFont(io::IFile*  file);
    //--Meshs
    scene::IMesh* loadMesh(const char* file);
    scene::IMesh* loadMesh(io::IFile*  file);


    void registerFontReader(IFontReader* newReader);
    void registerImageReader(IImageReader* newReader);
    void registerMeshReader(IMeshReader* newReader);

    void registerImageWriter();

protected:
private:
    io::IFileSystem* FileSys;

    //Images
    std::vector<IImageReader*>  ImageReaders;
    //Fonts
    std::vector<IFontReader*>   FontReaders;
    //Meshs
    std::vector<IMeshReader*>   MeshReaders;
};

}
#endif // CRESOURCEMANAGER_H
