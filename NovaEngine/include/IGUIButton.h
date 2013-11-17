#ifndef IGUIBUTTON_H
#define IGUIBUTTON_H

#include "IGUINode.h"

namespace novaengine
{
namespace gui
{
enum E_BUTTON_STATE
{
    EBS_NORMAL      = 0x1,
    EBS_HOVER       = 0x2,
    EBS_PRESSED     = 0x3,
    EBS_INACTIVE    = 0x4,
};

class IGUIButton : public IGUINode
{
public:
    IGUIButton(IGUIManager* guimgr,s32 id,core::rects Size):
        IGUINode(guimgr,id,Size) {}

    virtual bool OnEvent(SEvent event) = 0;

    virtual void setCaption(const char* caption) = 0;
    virtual const char* getCaption(const char* caption) = 0;

    virtual void setTexture(renderer::ITexture*,E_BUTTON_STATE forstate = EBS_NORMAL) = 0;
    virtual void setTexture(renderer::ITexture*,core::rectf Source,E_BUTTON_STATE forstate = EBS_NORMAL) = 0; //if you have more then one buttons type in one texture
    virtual renderer::ITexture* getTexture(E_BUTTON_STATE = EBS_NORMAL) = 0 ;
    virtual core::rectf getTextureRect(E_BUTTON_STATE forstate = EBS_NORMAL) = 0;

    virtual void setState(E_BUTTON_STATE state) = 0;
    virtual E_BUTTON_STATE getState() = 0;



protected:
private:
};
}
}
#endif // IGUIBUTTON_H
