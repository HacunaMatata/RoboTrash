#ifndef IGUISTATICTEXT_H
#define IGUISTATICTEXT_H

#include "IGUINode.h"
#include "IFont.h"

namespace novaengine
{

namespace gui
{

class IGUIStaticText : public IGUINode
{
public:
        IGUIStaticText(IGUIManager* guimgr,s32 id,core::rects Location_):
            IGUINode(guimgr,id,Location_){}
        void setText(const char* text) = 0;
        const char* getText() = 0;

        void setFont(IFont* font) = 0;
        IFont* getFont() = 0;

protected:
private:
};

}

}

#endif // IGUISTATICTEXT_H
