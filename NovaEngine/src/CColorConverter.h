#ifndef CCOLORCONVERTER_H
#define CCOLORCONVERTER_H

#include "Types.h"
#include "SPixelFormat.h"

namespace novaengine
{

class CColorConverter
{
    public:

        static void flip_color_array(const void* input,void* output,u32 width,u32 height,u32 bytesinpixel,u32 pad,bool flip_x,bool flip_y);
        static void flip_color_array(void* input,u32 width,u32 height,u32 bytesinpixel,u32 pad,bool flip_x,bool flip_y);

        static void convert_B8G8R8_to_R8G8B8(const void* input,u32 input_size,void* output);
        static void convert_B8G8R8A8_to_R8G8B8A8(const void* input,u32 input_size,void* output);

        static void convert_B8G8R8_to_R8G8B8(void* input,u32 input_size);
        static void convert_B8G8R8A8_to_R8G8B8A8(void* input,u32 input_size);

        static void convert_24bit_to_32bit(const void* input,u32 input_size,void* output);

        static renderer::SPixelFormat build_pixelformat_struct(renderer::E_PIXEL_FORMAT format);

    protected:
    private:
};

}
#endif // CCOLORCONVERTER_H
