#ifndef IRESOURCEMANAGER_H
#define IRESOURCEMANAGER_H

#include "Object.h"
#include "IFont.h"
#include "IImageReader.h"
#include "IFontReader.h"
#include "IMeshReader.h"



namespace novaengine
{
/// \brief Provides loading all resource files like a image,mesh,fonts ect...
class IResourceManager : public Object
{
    public:
        //--Graphics
        virtual renderer::IImage*   loadImage(const char* file) = 0;
        virtual renderer::IImage*   loadImage(io::IFile*  file) = 0;

        virtual bool                saveImage(const char* file) = 0;
        //--Fonts
        virtual gui::IFont* loadFont(const char* file) = 0;
        virtual gui::IFont* loadFont(io::IFile*  file) = 0;
        //--Meshs
        virtual scene::IMesh* loadMesh(const char* file) = 0;
        virtual scene::IMesh* loadMesh(io::IFile*  file) = 0;

        //--Readers/writers

        //--For Fonts
        virtual void registerFontReader(IFontReader* newReader) = 0;
        //--For Images
        virtual void registerImageReader(IImageReader* newReader) = 0;
        virtual void registerImageWriter() = 0;
        //--For Meshs
        virtual void registerMeshReader(IMeshReader* newReader) = 0;



    protected:
    private:
};

}
#endif // IRESOURCEMANAGER_H
