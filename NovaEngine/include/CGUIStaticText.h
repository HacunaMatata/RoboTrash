#ifndef CGUISTATICTEXT_H
#define CGUISTATICTEXT_H

#include "IGUIStaticText.h"

namespace novaengine
{

namespace gui
{

class CGUIStaticText : public IGUIStaticText
{
public:
    CGUIStaticText(IGUIManager* guimgr,s32 id,core::rects Location_):
        IGUIStaticText(guimgr,id,Location_)
    {

    }

    void setText(const char* text) = 0;
    const char* getText() = 0;

    void setFont(IFont* font) = 0;
    IFont* getFont() = 0;

protected:
private:
};
}
}
#endif // CGUISTATICTEXT_H
