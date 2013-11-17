#ifndef CGUIIMAGE_H
#define CGUIIMAGE_H

#include "IMaterial.h"
#include "IGUIImage.h"

namespace novaengine
{
namespace gui
{
class CGUIImage : public IGUIImage
{
public:
    CGUIImage(IGUIManager* guimgr,renderer::ITexture* texture,core::rectf SourceRect,s32 id,core::rects Size):
        IGUIImage(guimgr,texture,SourceRect,id,Size)
    {
        Material = new renderer::CMaterial();
        Material->setMaterialTexture(texture);
        TextureSourceRect = SourceRect;
    }
    virtual ~CGUIImage()
    {
        if(Material)
            Material->release();
    }

    void setMaterial(renderer::IMaterial* newMaterial)
    {
        if(Material)
            Material->release();

        if(newMaterial)
            newMaterial->capture();

        Material = newMaterial;

    }
    renderer::IMaterial* getMaterial()
    {
        return Material;
    }

    void animate(f32 DeltaTime)
    {

    }
    void render()
    {
        renderer::IRenderer* Renderer = GUIManager->getRenderer();

        GUIManager->useGUIOrthoProjection();

        core::vector2ds p1(Location.X1,Location.Y2),p2(Location.X2,Location.Y1);

        Renderer->setActiveMaterial(Material);
        Renderer->draw2dRectangle(p1,p2,TextureSourceRect);
    }

protected:
private:
    core::rectf TextureSourceRect;
    renderer::IMaterial* Material;
};
}
}
#endif // CGUIIMAGE_H
