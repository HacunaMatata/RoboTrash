#ifndef CIMAGEREADERTGA_H
#define CIMAGEREADERTGA_H

#include "IImageReader.h"
#include "IFileSystem.h"
#include "IFile.h"
#include "Logger.h"

namespace novaengine
{
//------------------------------
typedef struct
{
    unsigned char Header[12];
} TGAHeader;

typedef struct
{
    unsigned char header[6];
    unsigned int bytesPerPixel;
    unsigned int imageSize;
    unsigned int type;
    unsigned int Height;
    unsigned int Width;
    unsigned int Bpp;
} TGAInfo;
//------------------------------
class CImageReaderTGA : public IImageReader
{
public:
    CImageReaderTGA(io::IFileSystem* fs);
    virtual ~CImageReaderTGA();

    bool isSupported(const char* file_extension);
    bool isSupported(io::IFile* file);

    renderer::IImage* LoadImage(const char* path);
    renderer::IImage* LoadImage(io::IFile* file);

    renderer::IImage* LoadCompressedTGA(io::IFile* tgaFile);
    renderer::IImage* LoadUnCompressedTGA(io::IFile* tgaFile);

protected:
private:
    io::IFileSystem* FileSys;
};

}
#endif // CTGAIMAGEREADER_H
