#include "CImageReaderTGA.h"
#include "CColorConverter.h"
#include "CImage.h"
namespace novaengine
{

CImageReaderTGA::CImageReaderTGA(io::IFileSystem* fs)
{
    FileSys = fs;
}
//--------------------------------------------------------------------------------------------------------
CImageReaderTGA::~CImageReaderTGA()
{
    //dtor
}
//--------------------------------------------------------------------------------------------------------
bool CImageReaderTGA::isSupported(const char* file_extension)
{
    if(strcmp(file_extension,".tga") == 0)
        return 1;
    return 0;
}
//--------------------------------------------------------------------------------------------------------
bool CImageReaderTGA::isSupported(io::IFile* file)
{

    TGAHeader header;

    unsigned char uTGAcompare[12] = {0,0, 2,0,0,0,0,0,0,0,0,0};
    unsigned char cTGAcompare[12] = {0,0,10,0,0,0,0,0,0,0,0,0};

    file->read(&header,sizeof(TGAHeader));
    file->seek(0);
    if(memcmp(uTGAcompare, &header, sizeof(header)) == 0 || memcmp(cTGAcompare, &header, sizeof(header)) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//--------------------------------------------------------------------------------------------------------
renderer::IImage* CImageReaderTGA::LoadImage(const char* path)
{
    io::IFile* tga_file = FileSys->open_file(path);

    if(!tga_file)
        return NULL;

    renderer::IImage* image = LoadImage(tga_file);

    tga_file->release();

    if(!image)
        return NULL;

    return image;
}
//--------------------------------------------------------------------------------------------------------
renderer::IImage* CImageReaderTGA::LoadImage(io::IFile* file)
{
    u32 FileStart = file->getPos();

    TGAHeader header;

    unsigned char uTGAcompare[12] = {0,0, 2,0,0,0,0,0,0,0,0,0};
    unsigned char cTGAcompare[12] = {0,0,10,0,0,0,0,0,0,0,0,0};

    file->read(&header,sizeof(TGAHeader));
    if(memcmp(uTGAcompare, &header, sizeof(header)) == 0)
    {
        renderer::IImage* img = LoadUnCompressedTGA(file);
        file->seek(FileStart);
        return img;
    }
    else if(memcmp(cTGAcompare, &header, sizeof(header)) == 0)
    {
        renderer::IImage* img = LoadCompressedTGA(file);
        file->seek(FileStart);
        return img;
    }
    else
    {
        io::Log::println("Failed to load image - corrupted data[UnknowHeader]",ELL_DEBUG_APP);
        file->seek(FileStart);
        return NULL;
    }

}
//--------------------------------------------------------------------------------------------------------
renderer::IImage* CImageReaderTGA::LoadUnCompressedTGA(io::IFile* file)
{


    TGAInfo  tga;
    file->read(&tga.header,sizeof(tga.header));

    u32 width  = tga.header[1] * 256 + tga.header[0];
    u32 height = tga.header[3] * 256 + tga.header[2];
    u32 bpp = tga.header[4];

    tga.Width = width;
    tga.Height = height;
    tga.Bpp = bpp;

    if((width <= 0) || (height <= 0) || ((bpp != 24) && (bpp !=32)))
    {
        file->release();
        io::Log::println("Failed to load image - corrupted data[InvalidImagePrm]",ELL_DEBUG_APP);
        return NULL;
    }
    renderer::E_PIXEL_FORMAT PixelFormat;
    core::dimension2du imgsize;
    u8* imgdata;

    imgsize.width = width;
    imgsize.height = height;

    tga.bytesPerPixel = bpp / 8;
    tga.imageSize = (tga.Width*tga.Height*tga.bytesPerPixel);


    if(bpp == 24)
        PixelFormat = renderer::EPF_B8G8R8;
    else
        PixelFormat = renderer::EPF_B8G8R8A8;

    //---------------------------------
    u32 fix = 0;
    if((tga.Width*tga.bytesPerPixel)%2)
        fix = tga.bytesPerPixel;
    //---------------------------------

    imgdata = new u8[tga.imageSize + (tga.Width * fix *tga.bytesPerPixel)];

    for(u32 line = 0; line < tga.Height;line++)
    {
        file->read(imgdata+(((tga.Width * line)*tga.bytesPerPixel) + (fix * line)),tga.Width*tga.bytesPerPixel);
    }
    //------------------------------------------------------------------------------

    //Converting fist point - Left Bottom to Left Top
    //CColorConverter::flip_color_array(imgdata,tga.Width,tga.Height,tga.bytesPerPixel,0,false,false);

    //Converting BGR(A) to RGB(A)
    if(PixelFormat == renderer::EPF_B8G8R8)
    {
        CColorConverter::convert_B8G8R8_to_R8G8B8(imgdata,tga.imageSize);
        PixelFormat = renderer::EPF_R8G8B8;
    }
    else
    {
        CColorConverter::convert_B8G8R8A8_to_R8G8B8A8(imgdata,tga.imageSize);
        PixelFormat = renderer::EPF_R8G8B8A8;
    }

    return new renderer::CImage(PixelFormat,imgsize,imgdata);

}
//--------------------------------------------------------------------------------------------------------
renderer::IImage* CImageReaderTGA::LoadCompressedTGA(io::IFile* tgaFile)
{
    io::Log::println("Failed to load image - RLE compression not supported.",ELL_DEBUG_APP);
}
}
