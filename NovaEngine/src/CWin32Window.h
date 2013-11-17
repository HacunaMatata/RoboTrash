#ifndef CWIN32Window_H
#define CWIN32Window_H

#ifdef GD_WINDOW_WIN32

#include <windows.h>

#include "IWindow.h"
#include "SEngineParams.h"
#include "ERendererEnums.h"
#include "Logger.h"
#include "NovaEngine.h"
#include "CKeymap.h"
#include "EKeycodes.h"
#include "Types.h"

#ifdef GD_RENDERER_OPENGL
//#include "gl/gl.h"
//#include "wglext.h"
#endif

namespace novaengine
{
namespace window
{

//-------------------------------------------------
class CWin32Window : public IWindow
{
public:
    CWin32Window(SEngineParams params,INovaEngine* RootEngine);
    virtual ~CWin32Window();

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

    SEngineParams iparams;
    //---------------------------------
    renderer::E_RENDERER_TYPE RendererType;
    bool create_opengl_surface(SEngineParams params);
    void release_opengl_surface();
    //---------------------------------
    HGLRC hRC;
    HDC   hDC;
    HWND  hWnd;
    HINSTANCE hInstance;
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
#endif // CWIN32Window_H
