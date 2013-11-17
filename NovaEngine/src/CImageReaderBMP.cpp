#include "CImageReaderBMP.h"
#include "CColorConverter.h"
#include "CImage.h"
namespace novaengine
{
CImageReaderBMP::CImageReaderBMP(io::IFileSystem* fs)
{
    FileSys = fs;
}
//--------------------------------------------------------------------------------------------------------
CImageReaderBMP::~CImageReaderBMP()
{

}
//--------------------------------------------------------------------------------------------------------
bool CImageReaderBMP::isSupported(const char* file_extension)
{
    if(strcmp(file_extension,".bmp") == 0)
        return 1;
    return 0;
}
//--------------------------------------------------------------------------------------------------------
bool CImageReaderBMP::isSupported(io::IFile* file)
{
    BITMAPFILEHEADER header;
    file->read(&header,14);
    file->seek(file->getLastPos());
    if(memcmp(&header.Type,"BF",sizeof(header.Type)))
        return true;
    return false;
}
//--------------------------------------------------------------------------------------------------------
renderer::IImage* CImageReaderBMP::LoadImage(const char* path)
{
    io::IFile* bmp_file = FileSys->open_file(path);

    if(!bmp_file)
        return NULL;

    renderer::IImage* image = LoadImage(bmp_file);

    bmp_file->release();

    if(!image)
        return NULL;

    return image;
}
//--------------------------------------------------------------------------------------------------------
renderer::IImage* CImageReaderBMP::LoadImage(io::IFile* file)
{
    BITMAPFILEHEADER header;
    file->read(&header.Type,sizeof(u16));
    if(!memcmp(&header.Type,"BF",sizeof(header.Type)))
    {
        io::Log::println("Failed to load image - corrupted data[not bmp]",ELL_DEBUG_APP);
    }
    u32 FileStart = file->getPos();
    renderer::IImage* bmp = LoadBMP(file);
    file->seek(FileStart);
    return bmp;
}
//--------------------------------------------------------------------------------------------------------
renderer::IImage* CImageReaderBMP::LoadBMP(io::IFile* file)
{


    BITMAPFILEHEADER fileheader;
    BITMAPINFOHEADER infoheader;

    file->read(&fileheader.Type,sizeof(u16));
    file->read(&fileheader.Size,sizeof(u32));
    file->read(&fileheader.Reserved1,sizeof(u16));
    file->read(&fileheader.Reserved2,sizeof(u16));
    file->read(&fileheader.OffBits,sizeof(u32));

    file->read(&infoheader,sizeof(BITMAPINFOHEADER));

    renderer::E_PIXEL_FORMAT PixelFormat;
    core::dimension2du imgresolution;
    u8* imgdata;

    if(infoheader.SizeImage == 0)
    {
        infoheader.SizeImage = static_cast<u32>(file->getSize() - fileheader.OffBits);
    }

    imgresolution.width  = infoheader.Width;
    imgresolution.height = infoheader.Height;
    u32 bpp              = infoheader.BitCount;

    if(bpp == 24)
    {
        PixelFormat = renderer::EPF_R8G8B8;
    }
    else
    {printf("%u\n",bpp);
        io::Log::println("Failed to load image - corrupted data[BitCount not equal 24]",ELL_DEBUG_APP);
        return NULL;
    }

    imgdata = new u8[infoheader.SizeImage];

    file->read(imgdata,infoheader.SizeImage);

    //Converting fist point - Left Bottom to Left Top
    CColorConverter::flip_color_array(imgdata,infoheader.Width,infoheader.Height,bpp/8,0,false,false);
    //Converting BGR to RGB
    CColorConverter::convert_B8G8R8_to_R8G8B8(imgdata,infoheader.SizeImage);

    return new renderer::CImage(PixelFormat,imgresolution,imgdata);
}

}
