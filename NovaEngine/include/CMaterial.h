#ifndef CMATERIAL_H
#define CMATERIAL_H

#include "Types.h"
#include "Object.h"
#include "IMaterial.h"

namespace novaengine
{
namespace renderer
{

class CMaterial : public IMaterial
{
    public:
        CMaterial():
        MaterialTexture(0),
        MaterialColor(255,255,255,255),
        MaterialWireframe(0)
        {}

        CMaterial(ITexture* tex,core::color4u color = core::color4u(255,255,255,255))
        {
            if(tex)
                tex->capture();

            MaterialTexture = tex;
            MaterialColor = color;
			MaterialWireframe = 0;
        }

        virtual ~CMaterial()
        {
            if(MaterialTexture)
                MaterialTexture->release();
        }

        virtual void setMaterialTexture(ITexture* texture)
        {
            if(texture)
                texture->capture();
            if(MaterialTexture)
                MaterialTexture->release();
            MaterialTexture = texture;
        }
        virtual void setMaterialColor(core::color4u color)
        {
            MaterialColor = color;
        }
        virtual void setMaterialWireframe(bool show_wireframe)
        {
            MaterialWireframe = show_wireframe;
        }

        virtual ITexture* getMaterialTexture()
        {
            return MaterialTexture;
        }
        virtual core::color4u getMaterialColor()
        {
            return MaterialColor;
        }
        virtual bool getMaterialWireframe()
        {
            return MaterialWireframe;
        }

    private:
    ITexture*     MaterialTexture;
    core::color4u MaterialColor;
    bool          MaterialWireframe;
};

}
}
#endif // CMaterial_H
