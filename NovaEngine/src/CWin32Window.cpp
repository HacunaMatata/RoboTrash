#include "CWin32Window.h"

#ifdef GD_WINDOW_WIN32




WINGDIAPI BOOL WINAPI WIN32_SwapBuffers(HDC hdc)
{
    return SwapBuffers(hdc);
}

namespace novaengine
{
namespace window
{
//Vars for wndproc
bool        exp_Window_init;
INovaEngine *exp_Engine;
CWin32Window *exp_Window;

CKeymap<int,E_KEY_CODE>* exp_Keymap;
bool KeyPresed[256];

//Wndproc
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//CWin32Window
CWin32Window::CWin32Window(SEngineParams params,INovaEngine* RootEngine) :
    hRC(NULL),
    hDC(NULL),
    hWnd(NULL),
    hInstance(NULL)
{
    setObjectName("Win32Window");

    io::Log::println("Init. CWin32Window - begin.",ELL_DEBUG_ENGINE);

    still_alive = 1;


    //Set in zero all wndproc vars
    exp_Window_init   = 0;
    exp_Engine        = 0;
    exp_Window        = 0;
    exp_Keymap        = 0;

    //Win(Epic)
    Engine = RootEngine;
    iparams = params;
    WindowSize = params.WindowSize;
    Fullscreen = params.FullScreen;
    Bits       = params.Bits;

    hInstance = GetModuleHandle(0);

    if(params.WindowID == 0)
    {
        ExternalWindow = false;
        WNDCLASSEX wcex;
        /* register window class */
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_OWNDC;
        wcex.lpfnWndProc = WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = hInstance;
        wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
        wcex.lpszMenuName = NULL;
        wcex.lpszClassName = params.EngineCaption;
        wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


        u32 i = GetLastError();
        printf("%d\n",i);
        if (!RegisterClassEx(&wcex))
        {
            io::Log::println("Cannot register window class.",ELL_FATAL_ERROR);
            still_alive = false;
        }

        DWORD style = WS_POPUP;

        if(!params.FullScreen)
            style = WS_SYSMENU      |
                    WS_BORDER       |
                    WS_CAPTION      |
                    WS_CLIPCHILDREN |
                    WS_CLIPSIBLINGS ;

        //if something crash adobe we cant create window
        if(still_alive)
        {
            /* create main window */
            hWnd = CreateWindowEx(0,
                                  params.EngineCaption,
                                  "",
                                  style,
                                  CW_USEDEFAULT,
                                  CW_USEDEFAULT,
                                  params.WindowSize.width ,
                                  params.WindowSize.height ,
                                  NULL,
                                  NULL,
                                  hInstance,
                                  this);
            if(!hWnd)
            {
                io::Log::println("Cannot create window.",ELL_FATAL_ERROR);
                still_alive = false;
            }
            setWindowSize(params.WindowSize);
        }

    }
    else
    {
        ExternalWindow = true;
        io::Log::println("Using external window...",ELL_WARNING);
        hWnd = (HWND)params.WindowID;
    }

    //if windowclass still alive we continue initialization...
    if(still_alive)
    {
        ShowWindow(hWnd, SW_SHOW);
        UpdateWindow(hWnd);

        /* get the Window context (DC) */
        hDC = GetDC(hWnd);
        RendererType = params.Renderer;

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
    }

    //if windowclass still alive we continue initialization...
    if(still_alive)
    {
        SetActiveWindow(hWnd);
        SetForegroundWindow(hWnd);

        LoadKeymap();

        exp_Engine = Engine;
        exp_Window = this;
        exp_Keymap = &Keymap;

        /* And we enable fullscreen(if params.fullscreen = true) */
        toogleFullscreen(true);
    }

    io::Log::println("Init. CWin32Window - done.",ELL_DEBUG_ENGINE);
}
//--------------------------------------------------------------------------------------------------------
CWin32Window::~CWin32Window()
{
    toogleFullscreen(false);
    /* release render context */
    switch(RendererType)
    {
    case renderer::ERT_OPENGL:
        release_opengl_surface();
        break;
    }
    /* destroy the window explicitly */
    if(!ExternalWindow)
    {
        DestroyWindow(hWnd);

        WNDCLASSEX wcex_;
        if(!GetClassInfoEx(GetModuleHandle(0),iparams.EngineCaption,&wcex_))
        {
            io::Log::println("winclass already released");
        }
        else
        {
            if(!UnregisterClass(iparams.EngineCaption,hInstance))
                io::Log::println("Cannot release window class (its soo bad)",ELL_FATAL_ERROR);
        }

    }
}
//--------------------------------------------------------------------------------------------------------
bool CWin32Window::create_opengl_surface(SEngineParams params)
{
#ifdef GD_RENDERER_OPENGL
    PIXELFORMATDESCRIPTOR pfd;

    int pFormat;

    DWORD dwFlags = PFD_DRAW_TO_WINDOW;

    /* OpenGL context support */
    dwFlags |= PFD_SUPPORT_OPENGL;

    /* DoubleBuf */
    if(params.DoubleBuf)
        dwFlags |= PFD_DOUBLEBUFFER;


    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = dwFlags;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = params.Bits;
    pfd.cDepthBits = params.ZBufferBits;
    pfd.iLayerType = PFD_MAIN_PLANE;

    pFormat = ChoosePixelFormat(hDC, &pfd);

    if(!SetPixelFormat(hDC, pFormat, &pfd))
    {
        io::Log::println("Unable to set PixelFormatDescription.",ELL_FATAL_ERROR);
        return 0;
    }

    /* create and enable the render context (RC) */
    hRC = wglCreateContext(hDC);
    if(!hRC)
    {
        io::Log::println("Cannot create render context.",ELL_FATAL_ERROR);
        return 0;
    }

    wglMakeCurrent(hDC, hRC);

    //VSync

    typedef BOOL (APIENTRY * WGLSWAPINTERVALEXTFUNC)(int);
    WGLSWAPINTERVALEXTFUNC wglSwapIntervalEXT = WGLSWAPINTERVALEXTFUNC(wglGetProcAddress("wglSwapIntervalEXT"));

    if(wglSwapIntervalEXT)
    {
        if(params.VSync)
            wglSwapIntervalEXT(1);
        else
            wglSwapIntervalEXT(0);
    }
    else
    {
        io::Log::println("VSync not supported. (LOL)",ELL_ERROR);
    }

    return 1;
#else
    return 0;
#endif
}
//--------------------------------------------------------------------------------------------------------
void CWin32Window::release_opengl_surface()
{
#ifdef GD_RENDERER_OPENGL
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hWnd, hDC);
#endif
}
//---------------------------------------------------------------------------------------------------------
void CWin32Window::SwapBuffers()
{
    switch(RendererType)
    {
    case renderer::ERT_OPENGL:
        WIN32_SwapBuffers(hDC);
        break;
    }
}
//--------------------------------------------------------------------------------------------------------
void CWin32Window::toogleFullscreen(bool enable)
{
    //This func hide main window(if fullscreen enabled) if user change active window.
    if(Fullscreen)
    {
        if(enable)
        {
            DEVMODE dm;
            DEVMODE dmScreenSettings;

            memset (&dmScreenSettings, 0, sizeof (dmScreenSettings));
            dmScreenSettings.dmSize = sizeof (dmScreenSettings);
            dmScreenSettings.dmPelsWidth = WindowSize.width;
            dmScreenSettings.dmPelsHeight = WindowSize.height;
            dmScreenSettings.dmBitsPerPel = Bits;
            dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

            ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
        }
        else
        {
            ChangeDisplaySettings(NULL, 0);
        }

    }

}
//--------------------------------------------------------------------------------------------------------
void CWin32Window::OnResize()
{
    RECT r;
    GetClientRect(hWnd, &r);
    WindowSize = core::dimension2du(r.right,r.bottom);

//    io::Log::println("Resizing(%d,%d).",WindowSize.width,WindowSize.height);

    //Need to update window if fullscreen enabled
    toogleFullscreen(true);
}
//--------------------------------------------------------------------------------------------------------
void CWin32Window::setWindowSize(core::dimension2du WSize)
{
    RECT rcClient, rcWind;
    POINT ptDiff;
    GetClientRect(hWnd, &rcClient);
    GetWindowRect(hWnd, &rcWind);
    ptDiff.x = (rcWind.right - rcWind.left) - rcClient.right;
    ptDiff.y = (rcWind.bottom - rcWind.top) - rcClient.bottom;
    MoveWindow(hWnd,rcWind.left, rcWind.top, WSize.width + ptDiff.x, WSize.height + ptDiff.y, TRUE);

    toogleFullscreen(true);
}
//--------------------------------------------------------------------------------------------------------
core::dimension2du CWin32Window::getWindowSize()
{
    return WindowSize;
}
//--------------------------------------------------------------------------------------------------------
core::dimension2du CWin32Window::getRealWindowSize()
{
    RECT window_rect;
    GetClientRect(hWnd,&window_rect);
    return core::dimension2du(window_rect.right - window_rect.left,window_rect.bottom - window_rect.top);
}
//--------------------------------------------------------------------------------------------------------
void CWin32Window::setWindowCaption(const char* caption)
{
    SetWindowText(hWnd,caption);
}
//--------------------------------------------------------------------------------------------------------
void CWin32Window::setCursorPos(core::vector2ds CPos)
{
    POINT rp;
    rp.x = 0;
    rp.y = 0;
    ClientToScreen(hWnd, &rp);

    CPos.x += rp.x;
    CPos.y += rp.y;

    SetCursorPos(CPos.x,CPos.y);
}
//--------------------------------------------------------------------------------------------------------
core::vector2ds CWin32Window::getCursorPos()
{
    POINT point;
    POINT realpoint;

    point.x = 0;
    point.y = 0;

    realpoint.x = 0;
    realpoint.y = 0;

    ClientToScreen(hWnd, &realpoint);
    GetCursorPos(&point);

    int x = (int)point.x-(int)realpoint.x;
    int y = (int)point.y-(int)realpoint.y;

    return core::vector2ds(x,y);
}
//--------------------------------------------------------------------------------------------------------
void CWin32Window::setCursorVisible(bool visible)
{
    ShowCursor(visible);
    CursorVisibility = visible;
}
//--------------------------------------------------------------------------------------------------------
bool CWin32Window::isCursorVisible()
{
    return CursorVisibility;
}
//--------------------------------------------------------------------------------------------------------
void CWin32Window::setResizable(bool resize)
{
    if(resize != df_Resizable && !Fullscreen)
    {
        LONG_PTR style = WS_POPUP;

        if (!resize)
            style = WS_SYSMENU      |
                    WS_BORDER       |
                    WS_CAPTION      |
                    WS_CLIPCHILDREN |
                    WS_CLIPSIBLINGS ;
        else
            style = WS_THICKFRAME   |
                    WS_SYSMENU      |
                    WS_BORDER       |
                    WS_CAPTION      |
                    WS_CLIPCHILDREN |
                    WS_CLIPSIBLINGS |
                    WS_MAXIMIZEBOX  |
                    WS_MINIMIZEBOX;

        if (!SetWindowLong(hWnd, GWL_STYLE, style))
            io::Log::println("Cannot change window style.");

        RECT clientSize;
        clientSize.top = 0;
        clientSize.left = 0;
        clientSize.right = WindowSize.width;
        clientSize.bottom = WindowSize.height;

        AdjustWindowRect(&clientSize, style, FALSE);

        const s32 realWidth = clientSize.right - clientSize.left;
        const s32 realHeight = clientSize.bottom - clientSize.top;

        const s32 windowLeft = (GetSystemMetrics(SM_CXSCREEN) - realWidth) / 2;
        const s32 windowTop = (GetSystemMetrics(SM_CYSCREEN) - realHeight) / 2;


        SetWindowPos(hWnd,HWND_TOP,windowLeft,windowTop,realWidth,realHeight,SWP_FRAMECHANGED|SWP_NOMOVE|SWP_SHOWWINDOW);
        df_Resizable = resize;

    }
}
//--------------------------------------------------------------------------------------------------------
bool CWin32Window::isResizable()
{
    return df_Resizable;
}
//--------------------------------------------------------------------------------------------------------
bool CWin32Window::update()
{
    if(exp_Window_init == false && still_alive == true)
        exp_Window_init = true;

    pullEvents();

    if(still_alive)
    {
        wglMakeCurrent(hDC, hRC);
        return 1;
    }

    return 0;
}
//--------------------------------------------------------------------------------------------------------
void CWin32Window::pullEvents()
{
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {

        if (msg.message == WM_QUIT)
        {
            still_alive = false;
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

    }
}
//--------------------------------------------------------------------------------------------------------
void CWin32Window::LoadKeymap()
{

    Keymap.set(0,novaengine::KEY_UNKNOW);
    //---------------------------------------
    Keymap.set(VK_UP,novaengine::KEY_UP);
    Keymap.set(VK_DOWN,novaengine::KEY_DOWN);
    Keymap.set(VK_LEFT,novaengine::KEY_LEFT);
    Keymap.set(VK_RIGHT,novaengine::KEY_RIGHT);
    //---------------------------------------
    Keymap.set(VK_SHIFT,novaengine::KEY_SHIFT);
    Keymap.set(VK_CONTROL,novaengine::KEY_CTRL);
    Keymap.set(VK_MENU,novaengine::KEY_ALT);

    Keymap.set(0x30,novaengine::KEY_KEY_0);
    Keymap.set(0x31,novaengine::KEY_KEY_1);
    Keymap.set(0x32,novaengine::KEY_KEY_2);
    Keymap.set(0x33,novaengine::KEY_KEY_3);
    Keymap.set(0x34,novaengine::KEY_KEY_4);
    Keymap.set(0x35,novaengine::KEY_KEY_5);
    Keymap.set(0x36,novaengine::KEY_KEY_6);
    Keymap.set(0x37,novaengine::KEY_KEY_7);
    Keymap.set(0x38,novaengine::KEY_KEY_8);
    Keymap.set(0x39,novaengine::KEY_KEY_9);
    //--------------------------------------
    Keymap.set(0x41,novaengine::KEY_KEY_A);
    Keymap.set(0x42,novaengine::KEY_KEY_B);
    Keymap.set(0x43,novaengine::KEY_KEY_C);
    Keymap.set(0x44,novaengine::KEY_KEY_D);
    Keymap.set(0x45,novaengine::KEY_KEY_E);
    Keymap.set(0x46,novaengine::KEY_KEY_F);
    Keymap.set(0x47,novaengine::KEY_KEY_G);
    Keymap.set(0x48,novaengine::KEY_KEY_H);
    Keymap.set(0x49,novaengine::KEY_KEY_I);
    Keymap.set(0x4a,novaengine::KEY_KEY_J);
    Keymap.set(0x4b,novaengine::KEY_KEY_K);
    Keymap.set(0x4c,novaengine::KEY_KEY_L);
    Keymap.set(0x4d,novaengine::KEY_KEY_M);
    Keymap.set(0x4e,novaengine::KEY_KEY_N);
    Keymap.set(0x4f,novaengine::KEY_KEY_O);
    Keymap.set(0x50,novaengine::KEY_KEY_P);
    Keymap.set(0x51,novaengine::KEY_KEY_Q);
    Keymap.set(0x52,novaengine::KEY_KEY_R);
    Keymap.set(0x53,novaengine::KEY_KEY_S);
    Keymap.set(0x54,novaengine::KEY_KEY_T);
    Keymap.set(0x55,novaengine::KEY_KEY_U);
    Keymap.set(0x56,novaengine::KEY_KEY_V);
    Keymap.set(0x57,novaengine::KEY_KEY_W);
    Keymap.set(0x58,novaengine::KEY_KEY_X);
    Keymap.set(0x59,novaengine::KEY_KEY_Y);
    Keymap.set(0x5a,novaengine::KEY_KEY_Z);
    //--------------------------------------
    Keymap.set(VK_BACK      ,novaengine::KEY_BACKSPACE  );
    Keymap.set(VK_TAB       ,novaengine::KEY_TAB        );
    Keymap.set(VK_RETURN    ,novaengine::KEY_RETURN     );
    Keymap.set(VK_CAPITAL   ,novaengine::KEY_CAPSLOCK   );
    Keymap.set(VK_ESCAPE    ,novaengine::KEY_ESCAPE     );
    Keymap.set(VK_SPACE     ,novaengine::KEY_SPACE      );
    Keymap.set(VK_PRIOR     ,novaengine::KEY_PAGEUP     );
    Keymap.set(VK_NEXT      ,novaengine::KEY_PAGEDOWN   );
    Keymap.set(VK_END       ,novaengine::KEY_END        );
    Keymap.set(VK_HOME      ,novaengine::KEY_HOME       );
    Keymap.set(VK_PRINT     ,novaengine::KEY_PRINTSCREEN);
    Keymap.set(VK_INSERT    ,novaengine::KEY_INSERT     );
    Keymap.set(VK_DELETE    ,novaengine::KEY_DELETE     );
    Keymap.set(VK_LSHIFT    ,novaengine::KEY_LSHIFT     );
    Keymap.set(VK_RSHIFT    ,novaengine::KEY_RSHIFT     );
    Keymap.set(VK_LCONTROL  ,novaengine::KEY_LCTRL      );
    Keymap.set(VK_RCONTROL  ,novaengine::KEY_RCTRL      );
    Keymap.set(VK_SNAPSHOT  ,novaengine::KEY_PRINTSCREEN);
    Keymap.set(VK_PAUSE     ,novaengine::KEY_PAUSE      );

    Keymap.set(VK_F1,novaengine::KEY_F1);
    Keymap.set(VK_F2,novaengine::KEY_F2);
    Keymap.set(VK_F3,novaengine::KEY_F3);
    Keymap.set(VK_F4,novaengine::KEY_F4);
    Keymap.set(VK_F5,novaengine::KEY_F5);
    Keymap.set(VK_F6,novaengine::KEY_F6);
    Keymap.set(VK_F7,novaengine::KEY_F7);
    Keymap.set(VK_F8,novaengine::KEY_F8);
    Keymap.set(VK_F9,novaengine::KEY_F9);
    Keymap.set(VK_F10,novaengine::KEY_F10);
    Keymap.set(VK_F11,novaengine::KEY_F11);
    Keymap.set(VK_F12,novaengine::KEY_F12);
    Keymap.set(VK_F13,novaengine::KEY_F13);
    Keymap.set(VK_F14,novaengine::KEY_F14);
    Keymap.set(VK_F15,novaengine::KEY_F15);
    Keymap.set(VK_NUMLOCK,novaengine::KEY_NUMLOCK);
    Keymap.set(VK_NUMPAD0,novaengine::KEY_NUM_0);
    Keymap.set(VK_NUMPAD1,novaengine::KEY_NUM_1);
    Keymap.set(VK_NUMPAD2,novaengine::KEY_NUM_2);
    Keymap.set(VK_NUMPAD3,novaengine::KEY_NUM_3);
    Keymap.set(VK_NUMPAD4,novaengine::KEY_NUM_4);
    Keymap.set(VK_NUMPAD5,novaengine::KEY_NUM_5);
    Keymap.set(VK_NUMPAD6,novaengine::KEY_NUM_6);
    Keymap.set(VK_NUMPAD7,novaengine::KEY_NUM_7);
    Keymap.set(VK_NUMPAD8,novaengine::KEY_NUM_8);
    Keymap.set(VK_NUMPAD9,novaengine::KEY_NUM_9);
    Keymap.set(VK_MULTIPLY,novaengine::KEY_MULTIPLY);
    Keymap.set(VK_ADD,novaengine::KEY_PLUS);
    Keymap.set(VK_SUBTRACT,novaengine::KEY_MINUS);
    Keymap.set(VK_DECIMAL,novaengine::KEY_DECIMAL);
    Keymap.set(VK_DIVIDE,novaengine::KEY_DIVIDE);
}
//--------------------------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    SEvent event;

    switch (uMsg)
    {
    case WM_CLOSE:
        exp_Engine->closeEngine();
        break;

    case WM_DESTROY:
        //PostQuitMessage(0);
        return 0;

    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_MOUSEMOVE:
    case WM_MOUSEWHEEL:
        event.event_type = EET_MOUSE;
        event.mouse.event_type = EETM_MOVE;
        event.mouse.x = (short)LOWORD(lParam);
        event.mouse.y = (short)HIWORD(lParam);

        if(uMsg == WM_LBUTTONDOWN || uMsg == WM_RBUTTONDOWN || uMsg == WM_MBUTTONDOWN)
        {
            event.mouse.event_type = EETM_BUTTON;
            event.mouse.key_state = EKS_DOWN;
        }

        if(uMsg == WM_LBUTTONUP || uMsg == WM_RBUTTONUP || uMsg == WM_MBUTTONUP)
        {
            event.mouse.event_type = EETM_BUTTON;
            event.mouse.key_state = EKS_UP;
        }

        switch(uMsg)
        {
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
            event.mouse.key_code = KEY_MOUSE_LEFT;
            break;
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
            event.mouse.key_code = KEY_MOUSE_RIGHT;
            break;
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
            event.mouse.key_code = KEY_MOUSE_MIDDLE;
            break;
        }

        if(uMsg == WM_MOUSEWHEEL)
        {
            event.mouse.event_type = EETM_BUTTON;
            event.mouse.key_code = KEY_MOUSE_WHELL;

            /* get whell spin direction */
            short wheel_dir = (short)HIWORD(wParam) / 120;
            if(wheel_dir > 0)
                event.mouse.key_state = EKS_UP;
            else
                event.mouse.key_state = EKS_DOWN;

            /* converert pointer coords from screen to window */
            POINT rp;
            rp.x = 0;
            rp.y = 0;
            ClientToScreen(hwnd, &rp);

            event.mouse.x -= rp.x;
            event.mouse.y -= rp.y;
        }

        exp_Engine->pushEvent(event);
        break;

    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
    case WM_KEYUP:
    case WM_KEYDOWN:
        if(KeyPresed[wParam] != (uMsg == WM_KEYDOWN || uMsg == WM_SYSKEYDOWN))
        {
            KeyPresed[wParam] = (uMsg == WM_KEYDOWN || uMsg == WM_SYSKEYDOWN);

            event.event_type = EET_KEYBOARD;
            event.keyboard.key_code = exp_Keymap->get(wParam);
            event.keyboard.native_key_code = wParam;
            event.keyboard.key_state = (uMsg == WM_KEYDOWN || uMsg == WM_SYSKEYDOWN);

            if ( event.keyboard.key_code == KEY_SHIFT )
            {
                event.keyboard.key_code = (E_KEY_CODE)MapVirtualKey( ((lParam>>16) & 255),3);
                if (lParam & 0x1000000) event.keyboard.key_code = KEY_RSHIFT;
            }
            if ( event.keyboard.key_code == KEY_CTRL )
            {
                event.keyboard.key_code = (E_KEY_CODE)MapVirtualKey( ((lParam>>16) & 255), 3 );
                if (lParam & 0x1000000) event.keyboard.key_code = KEY_RCTRL;
            }
            if ( event.keyboard.key_code == KEY_ALT )
            {
                event.keyboard.key_code = (E_KEY_CODE)MapVirtualKey( ((lParam>>16) & 255), 3 );
                if (lParam & 0x1000000) event.keyboard.key_code = KEY_RALT;
            }

            u8 allKeys[256];
            GetKeyboardState(allKeys);
            event.keyboard.shift = ((allKeys[VK_SHIFT]  & 0x80)!=0);
            event.keyboard.ctrl  = ((allKeys[VK_CONTROL]& 0x80)!=0);
            event.keyboard.alt   = ((allKeys[VK_MENU]   & 0x80)!=0);

            WORD keyChars[2];
            UINT scanCode = HIWORD(lParam);
            int conversionResult = ToAsciiEx(wParam,scanCode,allKeys,keyChars,0,GetKeyboardLayout(0));
            if (conversionResult == 1)
            {
                WORD unicodeChar;
                MultiByteToWideChar(1251,MB_PRECOMPOSED,(LPCSTR)keyChars,sizeof(keyChars),(WCHAR*)&unicodeChar,1 );
                event.keyboard.unicode = unicodeChar;
            }
            else
                event.keyboard.unicode = 0;

            //Alt+F4
            if(allKeys[VK_MENU] && allKeys[VK_F4])
                exp_Engine->closeEngine();

            exp_Engine->pushEvent(event);

        }
    case WM_CHAR:
        break;
    case WM_ACTIVATE:
        if(exp_Window)
        {
            if(wParam == WA_INACTIVE)
            {
                //ShowWindow(hwnd, SW_MINIMIZE);
                //exp_Window->toogleFullscreen(false);
            }
            else
            {
                //ShowWindow(hwnd, SW_RESTORE);
                //exp_Window->toogleFullscreen(true);
            }

        }
        break;
    case WM_SIZE:

        if(exp_Window_init)
        {
            if(exp_Window != NULL)
                exp_Window->OnResize();

            if(exp_Engine->getRenderer() != NULL)
                exp_Engine->getRenderer()->OnResize();
        }

        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
//--------------------------------------------------------------------------------------------------------

}
}
#endif // GD_WINDOW_WIN32

