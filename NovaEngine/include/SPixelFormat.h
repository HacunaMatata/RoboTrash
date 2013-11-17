
#ifndef SPIXELFORMAT_H
#define SPIXELFORMAT_H


#include "Types.h"

namespace novaengine
{
namespace renderer
{

enum E_PIXEL_FORMAT
{
    EPF_UNKNOW   = 0x0,
    EPF_R8G8B8   = 0x1,
    EPF_R8G8B8A8 = 0x2,
    EPF_B8G8R8   = 0x3,
    EPF_B8G8R8A8 = 0x4,
    EPF_DEPTH    = 0x5,
};

struct SPixelFormat
{
    SPixelFormat() :
        RedMask(0),
        RedBits(0),
        RedShift(0),
        GreenMask(0),
        GreenBits(0),
        GreenShift(0),
        BlueMask(0),
        BlueBits(0),
        BlueShift(0),
        AlphaMask(0),
        AlphaBits(0),
        AlphaShift(0),
        BitsPerPixel(0),
        BytesPerPixel(0),
        PixelFormat(EPF_UNKNOW)
    {

    }

    u32 RedMask;
    u32 RedBits;
    s32 RedShift;

    u32 GreenMask;
    u32 GreenBits;
    s32 GreenShift;

    u32 BlueMask;
    u32 BlueBits;
    s32 BlueShift;

    u32 AlphaMask;
    u32 AlphaBits;
    s32 AlphaShift;

    u32 BitsPerPixel;
    u32 BytesPerPixel;

    u32 PixelFormat;
};

}
}

#endif // SPIXELFORMAT_H
