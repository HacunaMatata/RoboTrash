#ifndef ITEXTURE_H
#define ITEXTURE_H

#include "Types.h"
#include "Object.h"
#include "IImage.h"

namespace novaengine
{
namespace renderer
{

class ITexture : public Object
{
public:

    virtual core::dimension2du getTextureDimension() = 0;
    virtual void* getRendererTexture() = 0;

    virtual IImage* lock() = 0;
    virtual void unlock()  = 0;


protected:
private:
};

}
}


#endif // ITEXTURE_H
