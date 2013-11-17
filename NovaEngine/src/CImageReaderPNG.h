#ifndef CIMAGEREADERPNG_H
#define CIMAGEREADERPNG_H

#include "IImageReader.h"
#include "IFileSystem.h"
#include "IFile.h"
#include "Logger.h"

//#include "png.h"

namespace novaengine
{

class CImageReaderPNG : public IImageReader
{
public:
    CImageReaderPNG(io::IFileSystem* fs);
    virtual ~CImageReaderPNG();

    bool isSupported(const char* file_extension);
    bool isSupported(io::IFile* file);

    renderer::IImage* LoadImage(const char* path);
    renderer::IImage* LoadImage(io::IFile* file);

    renderer::IImage* LoadPNG(io::IFile* file);

protected:
private:
    io::IFileSystem* FileSys;
};

}
#endif // CIMAGEREADERPNG_H
