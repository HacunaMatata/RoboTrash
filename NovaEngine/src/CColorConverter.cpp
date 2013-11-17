#include "CColorConverter.h"
#include <stdio.h>
namespace novaengine
{


void CColorConverter::flip_color_array(const void* input,void* output,u32 width,u32 height,u32 bytesinpixel,u32 pad,bool flip_x,bool flip_y)
{
    if(!input || !output)
        return;

    u8* in  = (u8*) input;
    u8* out = (u8*) output;

    u32 input_index   = 0;
    u32 output_index  = 0;

    for(u32 y = 0; y < height; y++)
    {
        for(u32 x = 0; x < width; x++)
        {
            input_index  = (x + (y*width)) * bytesinpixel + (pad * y);
            output_index = (x + (y*width)) * bytesinpixel;
            //-------------flip x
            if( flip_x && !flip_y)
                output_index  =   ((width-1) - x) + (y*width);
            //-------------flip y
            if(!flip_x &&  flip_y)
                output_index  =                x  + (((height - 1) - y)*width);
            //-------------flip x and y
            if( flip_x &&  flip_y)
                output_index  =   ((width-1) - x) + (((height - 1) - y)*width);

            if(flip_x || flip_y)
                output_index *= bytesinpixel;

            for(u32 c = 0; c < bytesinpixel; c++)
                out[output_index + c] = in[input_index + c];

        }
    }
}
//---------------------------------------------------------------------------------------------
void CColorConverter::flip_color_array(void* input,u32 width,u32 height,u32 bytesinpixel,u32 pad,bool flip_x,bool flip_y)
{
    if(!input)
        return;
    //Need speedup
    u32 size    = width * height * bytesinpixel;
    u8* output  = new u8[size];
    flip_color_array(input,output,width,height,bytesinpixel,pad,flip_x,flip_y);
    memcpy(input,output,size);
    delete[] output;

}
//---------------------------------------------------------------------------------------------
void CColorConverter::convert_B8G8R8_to_R8G8B8(const void* input,u32 size,void* output)
{
    if(!input || !output)
        return;

    u8* in  = (u8*) input;
    u8* out = (u8*) output;

    for(u32 i = 0; i < size; i+=3)
    {
        out[i+0] = in[i+2];
        out[i+1] = in[i+1];
        out[i+2] = in[i+0];
    }
}
//---------------------------------------------------------------------------------------------
void CColorConverter::convert_B8G8R8A8_to_R8G8B8A8(const void* input,u32 size,void* output)
{
    if(!input)
        return;

    u8* in  = (u8*) input;
    u8* out = (u8*) output;

    for(u32 i = 0; i < size; i+=4)
    {
        out[i+0] = in[i+2];
        out[i+1] = in[i+1];
        out[i+2] = in[i+0];
    }
}
//---------------------------------------------------------------------------------------------
void CColorConverter::convert_B8G8R8_to_R8G8B8(void* input,u32 size)
{

    u8* in  = (u8*) input;

    register u8 tmp;

    for(u32 i = 0; i < size; i+=3)
    {
        tmp     =   in[i+0];
        in[i+0] =   in[i+2];
        in[i+2] =   tmp;
    }

}
//---------------------------------------------------------------------------------------------
void CColorConverter::convert_B8G8R8A8_to_R8G8B8A8(void* input,u32 size)
{
    //i think this faster then code above

    u8* in  = (u8*) input;

    register u8 tmp;

    for(u32 i = 0; i < size; i+=4)
    {
        tmp     =   in[i+0];
        in[i+0] =   in[i+2];
        in[i+2] =   tmp;
    }

}
//---------------------------------------------------------------------------------------------
void CColorConverter::convert_24bit_to_32bit(const void* input,u32 input_size,void* output)
{
    u8* in  = (u8*) input;
    u8* out = (u8*) output;

    u32 o = 0;
    for(u32 i = 0; i < input_size; i+=3)
    {
        out[o + 0] = in[i + 0];
        out[o + 1] = in[i + 1];
        out[o + 2] = in[i + 2];
        out[o + 3] = 255;
        o+= 4;
    }
}
//---------------------------------------------------------------------------------------------
renderer::SPixelFormat CColorConverter::build_pixelformat_struct(renderer::E_PIXEL_FORMAT format)
{
    renderer::SPixelFormat pf;
    switch(format)
    {
    case renderer::EPF_R8G8B8:
        pf.BytesPerPixel = 3;
        pf.BitsPerPixel = 24;

        pf.RedBits = 8;
        pf.RedMask = 0xFF000000;
        pf.RedShift = 0;

        pf.GreenBits = 8;
        pf.GreenMask = 0x00FF0000;
        pf.GreenShift = 1;

        pf.BlueBits = 8;
        pf.BlueMask = 0x0000FF00;
        pf.BlueShift = 2;

        pf.AlphaBits = 0;
        pf.AlphaMask = 0;
        pf.AlphaShift = 0;

        pf.PixelFormat = renderer::EPF_R8G8B8;
        break;
    case renderer::EPF_B8G8R8:
        pf.BytesPerPixel = 3;
        pf.BitsPerPixel = 24;

        pf.RedBits = 8;
        pf.RedMask = 0x0000FF00;
        pf.RedShift = 2;

        pf.GreenBits = 8;
        pf.GreenMask = 0x00FF0000;
        pf.GreenShift = 1;

        pf.BlueBits = 8;
        pf.BlueMask = 0xFF000000;
        pf.BlueShift = 0;

        pf.AlphaBits = 0;
        pf.AlphaMask = 0;
        pf.AlphaShift = 0;

        pf.PixelFormat = renderer::EPF_B8G8R8;
        break;
    case renderer::EPF_R8G8B8A8:

        pf.BytesPerPixel = 4;
        pf.BitsPerPixel = 32;

        pf.RedBits = 8;
        pf.RedMask = 0xFF000000;
        pf.RedShift = 0;

        pf.GreenBits = 8;
        pf.GreenMask = 0x00FF0000;
        pf.GreenShift = 1;

        pf.BlueBits = 8;
        pf.BlueMask = 0x0000FF00;
        pf.BlueShift = 2;

        pf.AlphaBits = 8;
        pf.AlphaMask = 0x000000FF;
        pf.AlphaShift = 3;

        pf.PixelFormat = renderer::EPF_R8G8B8A8;
        break;
    case renderer::EPF_B8G8R8A8:
        pf.BytesPerPixel = 4;
        pf.BitsPerPixel = 32;

        pf.RedBits = 8;
        pf.RedMask = 0x0000FF00;
        pf.RedShift = 2;

        pf.GreenBits = 8;
        pf.GreenMask = 0x00FF0000;
        pf.GreenShift = 1;

        pf.BlueBits = 8;
        pf.BlueMask = 0xFF000000;
        pf.BlueShift = 0;

        pf.AlphaBits = 8;
        pf.AlphaMask = 0x000000FF;
        pf.AlphaShift = 3;

        pf.PixelFormat = renderer::EPF_B8G8R8A8;
        break;
    case renderer::EPF_DEPTH:

        pf.BytesPerPixel = 4;
        pf.BitsPerPixel = 32;

        pf.RedBits = 8;
        pf.RedMask = 0xFF000000;
        pf.RedShift = 0;

        pf.GreenBits = 8;
        pf.GreenMask = 0x00FF0000;
        pf.GreenShift = 1;

        pf.BlueBits = 8;
        pf.BlueMask = 0x0000FF00;
        pf.BlueShift = 2;

        pf.AlphaBits = 8;
        pf.AlphaMask = 0x000000FF;
        pf.AlphaShift = 3;

        pf.PixelFormat = renderer::EPF_DEPTH;
        break;
    }
return pf;
}
//---------------------------------------------------------------------------------------------
}
