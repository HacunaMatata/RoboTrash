#include "CX11Window.h"

#ifdef GD_WINDOW_X11

namespace novaengine
{
namespace window
{


CKeymap<int,E_KEY_CODE>* exp_Keymap;
bool KeyPresed[256];

//CX11Window
CX11Window::CX11Window(SEngineParams params,INovaEngine* RootEngine) :
    xDpy(0),
    xWin(0)
{
    setObjectName("X11Window");

    io::Log::println("Init. CX11Window - begin.",ELL_DEBUG_ENGINE);

    still_alive = true;

    Engine       = RootEngine;
    RendererType = params.Renderer;
    WindowSize   = params.WindowSize;
    Fullscreen   = params.FullScreen;
    Bits         = params.Bits;

    int dummy;


    xDpy = XOpenDisplay(NULL);
    if(xDpy == NULL)
    {
        io::Log::println("Cannot open X display.",ELL_FATAL_ERROR);
        still_alive = false;
    }

//-----------------------------------------------------------------------------------------------
    switch(RendererType)
    {
    case renderer::ERT_OPENGL:
#ifdef GD_RENDERER_OPENGL
        if(!create_opengl_surface(params))
        {
            io::Log::println("Cannot create OpenGL surface.");
            still_alive = false;
        }
#else
        io::Log::println("Cannot create OpenGL surface - OpenGL not includded.",ELL_FATAL_ERROR);
#endif

        break;
    }
//----------------------------------------------------------------------------------------------

    //  create an X window with the selected visual
    Colormap cmap = XCreateColormap(xDpy, RootWindow(xDpy, xVI->screen), xVI->visual, AllocNone);

    XSetWindowAttributes winattrib;
    winattrib.colormap = cmap;
    winattrib.border_pixel = 0;
    winattrib.event_mask =  KeyPressMask        |
                            KeyReleaseMask      |
                            ButtonPressMask     |
                            ButtonReleaseMask   |
                            PointerMotionMask   |
                            ExposureMask        |
                            StructureNotifyMask;

    xWin = XCreateWindow(xDpy,
                         RootWindow(xDpy, xVI->screen),
                         0,
                         0,
                         params.WindowSize.width,
                         params.WindowSize.height,
                         0,
                         xVI->depth,
                         InputOutput,
                         xVI->visual,
                         CWBorderPixel | CWColormap | CWEventMask,
                         &winattrib);

    XSetStandardProperties(xDpy,
                           xWin,
                           "novaengine",
                           "novaengine",
                           None,
                           0,
                           0,
                           NULL);



    // request the X window to be displayed on the screen
    if(RendererType == renderer::ERT_OPENGL)
    {
#ifdef GD_RENDERER_OPENGL
        glXMakeCurrent(xDpy, xWin, xCx);
#endif
    }

    // atoms
    wm_protocols_atom       = XInternAtom(xDpy, "WM_PROTOCOLS"      , True);

    wm_delete_window_atom   = XInternAtom(xDpy, "WM_DELETE_WINDOW"  , True);

    XSetWMProtocols(xDpy,xWin,&wm_delete_window_atom,1);
    XSelectInput(xDpy, DefaultRootWindow(xDpy), KeyPressMask | KeyReleaseMask);
    //Vsync
    if(params.VSync)
    {
        int r = glXGetVideoSyncSGI(0);
        if(r == GLX_BAD_CONTEXT)
            io::Log::println("glx bad context");
        if(r == GLX_BAD_VALUE)
            io::Log::println("glx bad value");

    }

    // bind the rendering context to the window
    XMapWindow(xDpy, xWin);

    XAutoRepeatOff(xDpy);
    LoadKeymap();
    io::Log::println("Init. CX11Window - done.",ELL_DEBUG_ENGINE);
}
//--------------------------------------------------------------------------------------------------------
CX11Window::~CX11Window()
{
    XAutoRepeatOn(xDpy);
    XDestroyWindow(xDpy,xWin);
    XKillClient(xDpy,0);
}
//--------------------------------------------------------------------------------------------------------
bool CX11Window::create_opengl_surface(SEngineParams params)
{
#ifdef GD_RENDERER_OPENGL
    int dblBuf[]  = {GLX_RGBA, GLX_DEPTH_SIZE, 16, GLX_DOUBLEBUFFER, None};
    int snglBuf[] = {GLX_RGBA, GLX_DEPTH_SIZE, 16, None};

    int dummy;

    if(!glXQueryExtension(xDpy, &dummy, &dummy))
    {
        io::Log::println("X server has no OpenGL GLX extension",ELL_FATAL_ERROR);
        return 0;
    }

    if(params.DoubleBuf)
    {
        xVI = glXChooseVisual(xDpy, DefaultScreen(xDpy), dblBuf);

        if (xVI == NULL)
        {
            io::Log::println("Cannot init dblBuf, trying snglBuf...",ELL_ERROR);
            xVI = glXChooseVisual(xDpy, DefaultScreen(xDpy), snglBuf);

            if (xVI == NULL)
            {
                io::Log::println("no RGB visual with depth buffer",ELL_FATAL_ERROR);
                return 0;
            }
        }
    }
    else
    {
        xVI = glXChooseVisual(xDpy, DefaultScreen(xDpy), snglBuf);

        if (xVI == NULL)
        {
            io::Log::println("no RGB visual with depth buffer",ELL_FATAL_ERROR);
            return 0;
        }
    }

    //  create an OpenGL rendering context

    xCx = glXCreateContext(xDpy, xVI,None, GL_TRUE);

    if (xCx == NULL)
    {
        io::Log::println("Could not create rendering context",ELL_FATAL_ERROR);
        return 0;
    }



    return 1;
#else
    return 0;
#endif
}
//--------------------------------------------------------------------------------------------------------
void CX11Window::release_opengl_surface()
{
#ifdef GD_RENDERER_OPENGL

#endif
}
//---------------------------------------------------------------------------------------------------------
void CX11Window::SwapBuffers()
{
    switch(RendererType)
    {
    case renderer::ERT_OPENGL:
        glXSwapBuffers(xDpy, xWin);
        break;
    }
}
//--------------------------------------------------------------------------------------------------------
void CX11Window::toogleFullscreen(bool enable)
{
    //This func hide main window(if fullscreen enabled) if user change active window.
    if(Fullscreen)
    {
        if(enable)
        {

        }
        else
        {

        }

    }

}
//--------------------------------------------------------------------------------------------------------
void CX11Window::OnResize()
{

}
//--------------------------------------------------------------------------------------------------------
void CX11Window::setWindowSize(core::dimension2du WSize)
{

}
//--------------------------------------------------------------------------------------------------------
core::dimension2du CX11Window::getWindowSize()
{
    return WindowSize;
}
//--------------------------------------------------------------------------------------------------------
core::dimension2du CX11Window::getRealWindowSize()
{
    return WindowSize;
}
//--------------------------------------------------------------------------------------------------------
void CX11Window::setWindowCaption(const char* caption)
{
    if(!still_alive)return;
    XStoreName(xDpy, xWin, caption);
}
//--------------------------------------------------------------------------------------------------------
void CX11Window::setCursorPos(core::vector2ds CPos)
{

}
//--------------------------------------------------------------------------------------------------------
core::vector2ds CX11Window::getCursorPos()
{

}
//--------------------------------------------------------------------------------------------------------
void CX11Window::setCursorVisible(bool visible)
{

}
//--------------------------------------------------------------------------------------------------------
bool CX11Window::isCursorVisible()
{
    return CursorVisibility;
}
//--------------------------------------------------------------------------------------------------------
void CX11Window::setResizable(bool resize)
{

}
//--------------------------------------------------------------------------------------------------------
bool CX11Window::isResizable()
{
    return df_Resizable;
}
//--------------------------------------------------------------------------------------------------------
bool CX11Window::update()
{

    if(still_alive)
    {
        pullEvents();
        return 1;
    }

    return 0;
}
//--------------------------------------------------------------------------------------------------------
void CX11Window::pullEvents()
{
    XEvent xevent;

    while(XPending(xDpy))
    {
        XNextEvent(xDpy, &xevent);

        SEvent event;

        switch(xevent.type)
        {
            //!------------------------------------------------------------------------------
        case ButtonPress:
        case ButtonRelease:
        case MotionNotify:

            event.event_type = EET_MOUSE;

            if(xevent.type == ButtonPress || xevent.type == ButtonRelease)
            {
                event.mouse.event_type = EETM_BUTTON;

                if(xevent.type == ButtonPress)
                    event.mouse.key_state = EKS_DOWN;

                if(xevent.type == ButtonRelease)
                    event.mouse.key_state = EKS_UP;


                switch(xevent.xbutton.button)
                {
                case 1:
                    event.mouse.key_code  = KEY_MOUSE_LEFT;
                    break;
                case 2:
                    event.mouse.key_code = KEY_MOUSE_MIDDLE;
                    break;
                case 3:
                    event.mouse.key_code = KEY_MOUSE_RIGHT;
                    break;
                case 4:
                    event.mouse.key_code = KEY_MOUSE_WHELL;
                    event.mouse.key_state = EKS_UP;
                    break;
                case 5:
                    event.mouse.key_code = KEY_MOUSE_WHELL;
                    event.mouse.key_state = EKS_DOWN;
                    break;
                default:
                    event.mouse.key_code = KEY_MOUSE_UNKNOW;
                    break;
                }
            }
            else
                event.mouse.event_type = EETM_MOVE;

            event.mouse.x = xevent.xbutton.x;
            event.mouse.y = xevent.xbutton.y;

            Engine->pushEvent(event);
            break;
            //!------------------------------------------------------------------------------
        case KeyPress:
        case KeyRelease:
            event.event_type = EET_KEYBOARD;
            event.keyboard.key_code         = Keymap.get(xevent.xkey.keycode);
            event.keyboard.native_key_code  =  xevent.xkey.keycode;
            event.keyboard.key_state        = (xevent.type == KeyPress);

            Engine->pushEvent(event);
            break;

        case ClientMessage:

            if ( xevent.xclient.message_type == wm_protocols_atom && xevent.xclient.data.l[0] == wm_delete_window_atom)
            {
                //still_alive = false;
                Engine->closeEngine();
                break;
            }

            break;
            //!------------------------------------------------------------------------------
        default:
            break;
        }
    }
}
//--------------------------------------------------------------------------------------------------------
void CX11Window::LoadKeymap()
{

    Keymap.set(0,novaengine::KEY_UNKNOW);
    //---------------------------------------
    Keymap.set(0x6f,novaengine::KEY_UP);
    Keymap.set(0x74,novaengine::KEY_DOWN);
    Keymap.set(0x71,novaengine::KEY_LEFT);
    Keymap.set(0x72,novaengine::KEY_RIGHT);
    //---------------------------------------
    Keymap.set(0x32,novaengine::KEY_SHIFT);
    Keymap.set(0x25,novaengine::KEY_CTRL);
    Keymap.set(0x40,novaengine::KEY_ALT);

    Keymap.set(10,novaengine::KEY_KEY_1);
    Keymap.set(11,novaengine::KEY_KEY_2);
    Keymap.set(12,novaengine::KEY_KEY_3);
    Keymap.set(13,novaengine::KEY_KEY_4);
    Keymap.set(14,novaengine::KEY_KEY_5);
    Keymap.set(15,novaengine::KEY_KEY_6);
    Keymap.set(16,novaengine::KEY_KEY_7);
    Keymap.set(17,novaengine::KEY_KEY_8);
    Keymap.set(18,novaengine::KEY_KEY_9);
    Keymap.set(19,novaengine::KEY_KEY_0);
    //--------------------------------------
    Keymap.set(38,novaengine::KEY_KEY_A);
    Keymap.set(56,novaengine::KEY_KEY_B);
    Keymap.set(54,novaengine::KEY_KEY_C);
    Keymap.set(40,novaengine::KEY_KEY_D);
    Keymap.set(26,novaengine::KEY_KEY_E);
    Keymap.set(41,novaengine::KEY_KEY_F);
    Keymap.set(42,novaengine::KEY_KEY_G);
    Keymap.set(43,novaengine::KEY_KEY_H);
    Keymap.set(31,novaengine::KEY_KEY_I);
    Keymap.set(44,novaengine::KEY_KEY_J);
    Keymap.set(45,novaengine::KEY_KEY_K);
    Keymap.set(46,novaengine::KEY_KEY_L);
    Keymap.set(58,novaengine::KEY_KEY_M);
    Keymap.set(57,novaengine::KEY_KEY_N);
    Keymap.set(32,novaengine::KEY_KEY_O);
    Keymap.set(33,novaengine::KEY_KEY_P);
    Keymap.set(24,novaengine::KEY_KEY_Q);
    Keymap.set(27,novaengine::KEY_KEY_R);
    Keymap.set(39,novaengine::KEY_KEY_S);
    Keymap.set(28,novaengine::KEY_KEY_T);
    Keymap.set(23,novaengine::KEY_KEY_U);
    Keymap.set(55,novaengine::KEY_KEY_V);
    Keymap.set(25,novaengine::KEY_KEY_W);
    Keymap.set(53,novaengine::KEY_KEY_X);
    Keymap.set(29,novaengine::KEY_KEY_Y);
    Keymap.set(52,novaengine::KEY_KEY_Z);
    //--------------------------------------
    Keymap.set(0x16,novaengine::KEY_BACKSPACE);
    Keymap.set(0x17,novaengine::KEY_TAB);
    Keymap.set(0x24,novaengine::KEY_RETURN);
    Keymap.set(0x42,novaengine::KEY_CAPSLOCK);
    Keymap.set(0x09,novaengine::KEY_ESCAPE);
    Keymap.set(0x41,novaengine::KEY_SPACE);
    Keymap.set(0x70,novaengine::KEY_PAGEUP);
    Keymap.set(0x75,novaengine::KEY_PAGEDOWN);
    Keymap.set(0x73,novaengine::KEY_END);
    Keymap.set(0x6e,novaengine::KEY_HOME);
    Keymap.set(0x6b,novaengine::KEY_PRINTSCREEN);
    Keymap.set(0x76,novaengine::KEY_INSERT);
    Keymap.set(0x77,novaengine::KEY_DELETE);
    //Keymap.set(VK_LSHIFT,novaengine::KEY_LSHIFT);
    //Keymap.set(VK_RSHIFT,novaengine::KEY_RSHIFT);
    //Keymap.set(VK_LCONTROL,novaengine::KEY_LCTRL);
    //Keymap.set(VK_RCONTROL,novaengine::KEY_RCTRL);
    //Keymap.set(0x6b,novaengine::KEY_PRINTSCREEN);

    //Keymap.set(0x,novaengine::KEY_PAUSE);

    Keymap.set(0x43,novaengine::KEY_F1);
    Keymap.set(0x44,novaengine::KEY_F2);
    Keymap.set(0x45,novaengine::KEY_F3);
    Keymap.set(0x46,novaengine::KEY_F4);
    Keymap.set(0x47,novaengine::KEY_F5);
    Keymap.set(0x48,novaengine::KEY_F6);
    Keymap.set(0x49,novaengine::KEY_F7);
    Keymap.set(0x4a,novaengine::KEY_F8);
    Keymap.set(0x4b,novaengine::KEY_F9);
    Keymap.set(0x4c,novaengine::KEY_F10);
    Keymap.set(0x5f,novaengine::KEY_F11);
    Keymap.set(0x60,novaengine::KEY_F12);
    //Keymap.set(VK_F13,novaengine::KEY_F13);
    //Keymap.set(VK_F14,novaengine::KEY_F14);
    //Keymap.set(VK_F15,novaengine::KEY_F15);
    Keymap.set(0x4d,novaengine::KEY_NUMLOCK);
    Keymap.set(0x5a,novaengine::KEY_NUM_0);
    Keymap.set(0x57,novaengine::KEY_NUM_1);
    Keymap.set(0x58,novaengine::KEY_NUM_2);
    Keymap.set(0x59,novaengine::KEY_NUM_3);
    Keymap.set(0x53,novaengine::KEY_NUM_4);
    Keymap.set(0x54,novaengine::KEY_NUM_5);
    Keymap.set(0x55,novaengine::KEY_NUM_6);
    Keymap.set(0x4f,novaengine::KEY_NUM_7);
    Keymap.set(0x50,novaengine::KEY_NUM_8);
    Keymap.set(0x51,novaengine::KEY_NUM_9);
    Keymap.set(0x3f,novaengine::KEY_MULTIPLY);
    Keymap.set(0x56,novaengine::KEY_PLUS);
    Keymap.set(0x52,novaengine::KEY_MINUS);
    Keymap.set(0x5b,novaengine::KEY_DECIMAL);
    Keymap.set(0x6a,novaengine::KEY_DIVIDE);

}
//--------------------------------------------------------------------------------------------------------

}
}
#endif
