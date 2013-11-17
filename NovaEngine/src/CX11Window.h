#ifndef CX11Window_H
#define CX11Window_H

#ifdef GD_WINDOW_X11

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>

#include "IWindow.h"
#include "SEngineParams.h"
#include "ERendererEnums.h"
#include "Logger.h"
#include "NovaEngine.h"
#include "CKeymap.h"
#include "EKeycodes.h"
#include "Types.h"

#ifdef GD_RENDERER_OPENGL
#include <GL/glx.h>
#endif

namespace novaengine
{
namespace window
{

//-------------------------------------------------
class CX11Window : public IWindow
{
public:
    CX11Window(SEngineParams params,INovaEngine* RootEngine);
    virtual ~CX11Window();

    //------------------------
    void OnResize();
    void setWindowSize(core::dimension2du WSize);
    core::dimension2du getWindowSize();
    core::dimension2du getRealWindowSize();
    //------------------------
    void setCursorPos(core::vector2ds CPos);
    core::vector2ds getCursorPos();
    void setCursorVisible(bool visible);
    bool isCursorVisible();
    //------------------------
    void setResizable(bool resize);
    bool isResizable();
    //------------------------

    //------------------------
    void setWindowCaption(const char* caption);
    //------------------------
    ///driver
    void SwapBuffers();

    bool update();

    void LoadKeymap();
    void pullEvents();

    void toogleFullscreen(bool = true);

protected:
private:

    //---------------------------------
    renderer::E_RENDERER_TYPE RendererType;
    bool create_opengl_surface(SEngineParams params);
    void release_opengl_surface();
    //---------------------------------
    //XWindow
    Display     *xDpy;
    Window       xWin;
    //XAtoms
    Atom  wm_protocols_atom;
    Atom  wm_delete_window_atom;
    Atom  wm_protocols_list[1];
    //GLX

#ifdef GD_RENDERER_OPENGL
    XVisualInfo *xVI;
    GLXContext   xCx;
#endif
    bool ExternalWindow;
    //---------------------------------flags
    bool df_Resizable;
    //---------------------------------HEALTH
    bool still_alive;
    //---------------------------------MOUSE
    core::vector2ds CursorPos;
    bool CursorVisibility;
    //---------------------------------Keymap
    CKeymap<int,E_KEY_CODE> Keymap;
    bool Keys[KEY_COUNT];
    //---------------------------------Engine
    INovaEngine* Engine;
    //---------------------------------WINDOW
    core::dimension2d_t<u32> WindowSize;
    bool Fullscreen;
    u32 Bits;





};


}
}

#endif
#endif // CX11Window_H
