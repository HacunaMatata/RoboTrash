#ifndef ISPRITESCENENODE_H
#define ISPRITESCENENODE_H

#include "Types.h"
#include "IScene2DNode.h"

namespace novaengine
{
namespace scene
{
class ISceneSprite : public IScene2DNode
{
public:
    ISceneSprite(ISceneManager* smgr,renderer::ITexture* SpriteTexture,core::rectf Sourse = core::rectf(0,0,1,1),ISceneNode* parent = 0,s32 ID = -1,core::vector3df position = core::vector3df(0,0,0),core::vector3df rotation= core::vector3df(0,0,0),core::vector3df scale= core::vector3df(1,1,1)):
    IScene2DNode(smgr,parent,ID,position,rotation,scale){}

    virtual void setTexture(renderer::ITexture* texture) = 0;
    virtual renderer::ITexture* getTexture() = 0;

    virtual void setTextureSourceRect(core::rectf) = 0;
    virtual core::rectf getTextureSourceRect() = 0;






protected:
private:
};
typedef ISceneSprite* snSprite;
}
}


#endif // ISPRITESCENENODE_H
