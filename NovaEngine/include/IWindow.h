#ifndef IWindow_H
#define IWindow_H

#include "Object.h"
#include "Types.h"
#include "EDeviceFlags.h"



namespace novaengine
{
namespace window
{



class IWindow : public Object
{
public:

    virtual bool update() = 0;
    //------------------------
    virtual void OnResize() = 0;
    virtual void setWindowSize(core::dimension2du WSize) = 0;
    virtual core::dimension2du getWindowSize() = 0;
    virtual core::dimension2du getRealWindowSize() = 0; // getWindowSize() - Window border and tool bar(where (_ [] X)  ^_^ ) getRealWindowSize() - return render surface size.
    //------------------------
    virtual void setCursorPos(core::vector2ds CPos) = 0;
    virtual core::vector2ds getCursorPos() = 0;
    virtual void setCursorVisible(bool visible) = 0;
    virtual bool isCursorVisible() = 0;
    //------------------------
    virtual void setResizable(bool resize) = 0;
    virtual bool isResizable() = 0;
    //------------------------
    virtual void setWindowCaption(const char* caption) = 0;
    //------------------------

    ///driver
    virtual void SwapBuffers() = 0;

};

}
}
#endif // IWindow_H
