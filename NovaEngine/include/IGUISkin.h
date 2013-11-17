#ifndef IGUISKIN_H
#define IGUISKIN_H

#include "Types.h"

namespace novaengine
{
namespace gui
{

class IGUISkin
{
public:
        virtual void drawGUIButton(core::rects Location,core::color4u color,renderer::ITexture* texture) = 0;
protected:
private:
};

}
}
#endif // IGUISKIN_H
