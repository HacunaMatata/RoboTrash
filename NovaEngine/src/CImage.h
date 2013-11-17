#ifndef CIMAGE_H
#define CIMAGE_H

#include "Types.h"
#include "IImage.h"
#include "Logger.h"
#include "SPixelFormat.h"

#include "CColorConverter.h"

namespace novaengine
{
namespace renderer
{

class CImage : public IImage
{
public:
    CImage(renderer::E_PIXEL_FORMAT pf,core::dimension2du dim,u8* data)
    {
        PixelFormat = pf;
        ImageDimension = dim;

        u32 DataSize = ImageDimension.width * ImageDimension.height * CColorConverter::build_pixelformat_struct(pf).BytesPerPixel;

        PixelsData = new u8[DataSize];
        memcpy(PixelsData,data,DataSize);
    }

    virtual ~CImage()
    {
        if(PixelsData)
            delete[] PixelsData;
    }

    virtual renderer::E_PIXEL_FORMAT getPixelFormat()
    {
        return PixelFormat;
    }

    virtual renderer::SPixelFormat getPixelFormatStruct()
    {
        return CColorConverter::build_pixelformat_struct(PixelFormat);
    }

    virtual bool isValid()
    {
        return !(ImageDimension.width == 0 || ImageDimension.height == 0 || (!PixelsData));
    }

    virtual core::dimension2du getImageDimension()
    {
        return ImageDimension;
    }

    virtual core::color4u getPixel(u32 x,u32 y)
    {
        SPixelFormat PixelStruct = getPixelFormatStruct();

        if(isValid())
        {
            if(x >= 0 && x < ImageDimension.width && y >= 0 && y < ImageDimension.height)
            {
                core::color4u color;
                unsigned int Index = (ImageDimension.width * y + x)*PixelStruct.BytesPerPixel;
                color.Red   = PixelsData[Index+PixelStruct.RedShift];
                color.Green = PixelsData[Index+PixelStruct.GreenShift];
                color.Blue  = PixelsData[Index+PixelStruct.BlueShift];
                if(PixelStruct.AlphaBits != 0)
                    color.Alpha = PixelsData[Index+PixelStruct.AlphaShift];
                return color;
            }
        }
    }

    virtual void drawPixel(u32 x,u32 y,core::color4u color)
    {
        SPixelFormat PixelStruct = getPixelFormatStruct();

        if(isValid())
        {
            if(x >= 0 && x < ImageDimension.width && y >= 0 && y < ImageDimension.height)
            {
                unsigned int Index = (ImageDimension.width * y + x)*PixelStruct.BytesPerPixel;
                PixelsData[Index + PixelStruct.RedShift] = color.Red;
                PixelsData[Index + PixelStruct.GreenShift] = color.Green;
                PixelsData[Index + PixelStruct.BlueShift] = color.Blue;
                if(PixelStruct.AlphaBits != 0)
                    PixelsData[Index + PixelStruct.AlphaShift] = color.Alpha;
            }
        }
    }

    virtual void fill(core::color4u color)
    {
        if(isValid())
        {
            SPixelFormat PixelStruct = getPixelFormatStruct();
            u32 ImgSize =  ImageDimension.width * ImageDimension.height * PixelStruct.BytesPerPixel;

            for(u32 index = 0; index < ImgSize; index+=PixelStruct.BytesPerPixel)
            {
                PixelsData[index + PixelStruct.RedShift] = color.Red;
                PixelsData[index + PixelStruct.GreenShift] = color.Green;
                PixelsData[index + PixelStruct.BlueShift] = color.Blue;
                if(PixelStruct.AlphaBits != 0)
                    PixelsData[index + PixelStruct.AlphaShift] = color.Alpha;
            }
        }
    }
    virtual void flip(bool flip_x,bool flip_y)
    {
        if(isValid())
        {
            CColorConverter::flip_color_array(PixelsData,ImageDimension.width,ImageDimension.height,getPixelFormatStruct().BytesPerPixel,0,flip_x,flip_y);
        }
    }

    virtual void* lock()
    {
        return PixelsData;
    }
    virtual void  unlock()
    {

    }

protected:
private:

    renderer::E_PIXEL_FORMAT PixelFormat;
    core::dimension2du ImageDimension;
    u8* PixelsData;

};

}
}


#endif // CIMAGE_H
