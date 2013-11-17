#ifndef IMATERIAL_H
#define IMATERIAL_H

#include "Object.h"
#include "Types.h"
#include "ITexture.h"

namespace novaengine
{
namespace renderer
{
class IMaterial : public Object
{
    public:
        virtual void setMaterialTexture(ITexture* texture)=0;
        virtual void setMaterialColor(core::color4u color)=0;
        virtual void setMaterialWireframe(bool show_wireframe)=0;

        virtual ITexture* getMaterialTexture()=0;
        virtual core::color4u getMaterialColor()=0;
        virtual bool getMaterialWireframe()=0;
};
}
}
#endif // IMATERIAL_H
