#ifndef CSCENESPRITE_H
#define CSCENESPRITE_H

#include "ISceneManager.h"
#include "ISceneSprite.h"

namespace novaengine
{
namespace scene
{

class CSceneSprite : public ISceneSprite
{
public:

    CSceneSprite(ISceneManager* smgr,renderer::ITexture* SpriteTexture,core::rectf Source = core::rectf(0,0,1,1),ISceneNode* parent = 0,s32 ID = -1,core::vector3df position = core::vector3df(0,0,0),core::vector3df rotation= core::vector3df(0,0,0),core::vector3df scale= core::vector3df(1,1,1)):
        ISceneSprite(smgr,SpriteTexture,Source,parent, ID , position, rotation, scale),
        Material(0),
        TextureSourceRect(Source)
    {

        setTexture(SpriteTexture);
    }
    virtual ~CSceneSprite()
    {}

    void setTexture(renderer::ITexture* texture)
    {
        if(Material)
        {
            Material->setMaterialTexture(texture);
        }
        else
        {
            Material = new renderer::CMaterial();
            Material->setMaterialTexture(texture);
        }
    }
    renderer::ITexture* getTexture()
    {
        if(Material)
        {
            return Material->getMaterialTexture();
        }
        else
        {
            return 0;
        }
    }

    void setTextureSourceRect(core::rectf rect)
    {
        TextureSourceRect = rect;
    }
    core::rectf getTextureSourceRect()
    {
        return TextureSourceRect;
    }

    virtual void setMaterial(renderer::IMaterial* newMaterial,u32 Material_index = 0)
    {
        if(Material)
            Material->release();

        if(newMaterial)
            newMaterial->capture();

        Material = newMaterial;

    };
    virtual renderer::IMaterial* getMaterial(u32 Material_index = 0)
    {
        return Material;
    };

    void render()
    {
        ISceneNode::render();
        renderer::IRenderer* Renderer = SceneManager->getRenderer();

        if(!isVisible())
            return;

        SceneManager->useProjectionMatrix(EPM_ORTHO);
        SceneManager->useViewMatrix(EVM_2D);

        Renderer->setTransform(getAbsoluteTransformation(),renderer::EMT_MODEL);
        Renderer->setActiveMaterial(Material);

        core::vector2ds lb_p;
        core::vector2ds rt_p;

        rt_p.x = (Material->getMaterialTexture()->getTextureDimension().width * TextureSourceRect.getDimension().width)/2;
        rt_p.y = (Material->getMaterialTexture()->getTextureDimension().height * TextureSourceRect.getDimension().height)/2;
        lb_p = -rt_p;

        Renderer->draw2dRectangle(lb_p,rt_p,TextureSourceRect);
    }

protected:
private:
    renderer::IMaterial* Material;

    core::rectf TextureSourceRect;


};

}
}


#endif // CSCENESPRITE_H
