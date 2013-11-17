#ifndef CIMAGEREADERBMP_H
#define CIMAGEREADERBMP_H

#include "IImageReader.h"
#include "IFileSystem.h"
#include "IFile.h"
#include "Logger.h"

namespace novaengine
{
typedef struct
{
    u16 Type;
    u32 Size;
    u16 Reserved1;
    u16 Reserved2;
    u32 OffBits;
} BITMAPFILEHEADER;

typedef struct
{
    u32  Size;
    s32  Width;
    s32  Height;
    u16  Planes;
    u16  BitCount;
    u32  Compression;
    u32  SizeImage;
    s32  XPelsPerMeter;
    s32  YPelsPerMeter;
    u32  ClrUsed;
    u32  ClrImportant;
} BITMAPINFOHEADER;

class CImageReaderBMP : public IImageReader
{
public:
    CImageReaderBMP(io::IFileSystem* fs);
    virtual ~CImageReaderBMP();

    bool isSupported(const char* file_extension);
    bool isSupported(io::IFile* file);

    renderer::IImage* LoadImage(const char* path);
    renderer::IImage* LoadImage(io::IFile* file);

    renderer::IImage* LoadBMP(io::IFile* file);


protected:
private:
    io::IFileSystem* FileSys;
};

}

#endif // CBMPIMAGEREADER_H
