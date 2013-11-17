#ifndef IGUIIMAGE_H
#define IGUIIMAGE_H

#include "IGUINode.h"
#include "ITexture.h"
#include "IMaterial.h"

namespace novaengine
{
namespace gui
{
class IGUIImage : public IGUINode
{
public:
    IGUIImage(IGUIManager* guimgr,renderer::ITexture* texture,core::rectf SourceRect,s32 id,core::rects Size):
        IGUINode(guimgr,id,Size) {}

    virtual void setMaterial(renderer::IMaterial*) = 0;
    virtual renderer::IMaterial* getMaterial()     = 0;

protected:
private:
};
}
}
#endif // IGUIIMAGE_H
