#ifndef IIMAGE_H
#define IIMAGE_H

#include "Object.h"
#include "Types.h"

#include "SPixelFormat.h"

namespace novaengine
{
namespace renderer
{

class IImage : public Object
{
public:

    //virtual bool isValid()=0;
    virtual renderer::E_PIXEL_FORMAT getPixelFormat() = 0;

    virtual renderer::SPixelFormat getPixelFormatStruct() = 0;
    virtual core::dimension2du getImageDimension()=0;

    virtual core::color4u getPixel(u32 x,u32 y) = 0;
    virtual void drawPixel(u32 x,u32 y,core::color4u color) = 0;
    virtual void fill(core::color4u color) = 0;
    virtual void flip(bool flip_x,bool flip_y) = 0;

    //Return pixel array
    virtual void* lock()   = 0;
    virtual void  unlock() = 0;

protected:
private:


};

}
}


#endif // IIMAGE_H
