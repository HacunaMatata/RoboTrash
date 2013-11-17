#include "CNovaEngine.h"

#ifdef GD_WINDOW_SDL
//#include "CSDLDevice.h"
#endif // GD_WINDOW_SDL

#ifdef GD_WINDOW_WIN32
#include "CWin32Window.h"
#endif // GD_WINDOW_WIN32

#ifdef GD_WINDOW_X11
#include "CX11Window.h"
#endif // GD_WINDOW_X11

#ifdef GD_RENDERER_OPENGL
#include "COpenGLRenderer.h"
#endif // GD_RENDERER_OPENGL


#include "CFileSystem.h"
#include "CResourceManager.h"

#include "CTextureManager.h"
#include "CGeometryManager.h"

#include "CSceneManager.h"
#include "CGUIManager.h"

#include "version.h"
#include "NovaEngine.h"


namespace novaengine
{


CNovaEngine::CNovaEngine(SEngineParams params):
    Window(0),
    Renderer(0),
    UserEventHandler(0),
    still_alive(1)
{
    setObjectName("EngineRootClass");

    io::Log::println("Init:CNovaEngine - begin.",ELL_DEBUG_ENGINE);

    u32 time = Timer::getTime();


    //--------------------------------------------
    char buf[256];
    sprintf(buf,"NovaEngine v.%ld.%ld.%ld [%ld] %s build",NOVAENGINE_MAJOR,NOVAENGINE_MINOR,NOVAENGINE_BUILD,NOVAENGINE_BUILDS_COUNT,NOVAENGINE_STATUS);
    io::Log::println(buf,ELL_INFO);
    //--------------------------------------------

//-----------------------------------------------
//Load window
#ifdef GD_WINDOW_SDL
    Window = new window::CSDLWindow(params,this);
#endif

#ifdef GD_WINDOW_X11
    Window = new window::CX11Window(params,this);
#endif

#ifdef GD_WINDOW_WIN32
    Window = new window::CWin32Window(params,this);
#endif

//-----------------------------------------------
    if(!Window)
    {
        io::Log::println("Cannot create window...",ELL_FATAL_ERROR);
        closeEngine();
    }

    //Load renderer
    if(still_alive)
    {
        switch(params.Renderer)
        {
            ///------------------------------------------------------------------------
        case renderer::ERT_OPENGL:

#ifdef GD_RENDERER_OPENGL
            Renderer = new renderer::COpenGLRenderer(params,this);
#else
            io::Log::println("OpenGL renderer was not compiled into this build.",ELL_FATAL_ERROR);
            still_alive = false;
#endif

            break;
            ///-----------------------------------------------------------------------
        case renderer::ERT_NULL:
            io::Log::println("Selected renderer cannot render any graphics.",ELL_FATAL_ERROR);
            still_alive = false;
            break;
            ///-----------------------------------------------------------------------
        default:
            io::Log::println("Unknow renderer.",ELL_FATAL_ERROR);
            still_alive = false;
            break;
        }

        if(!Renderer)
        {
            io::Log::println("Cannot load renderer...",ELL_FATAL_ERROR);
            closeEngine();
        }
    }

    if(still_alive)
    {
        if(Renderer)
        {
            Renderer->OnResize();
        }

        //Load sub-systems
        FileSys         = new io::CFileSystem();
        ResourceManager = new CResourceManager(FileSys);
        TextureManager  = new CTextureManager(ResourceManager,Renderer);
        GeometryManager = new CGeometryManager(ResourceManager);

        SceneManager    = new scene::CSceneManager(this);
        GUIManager      = new gui::CGUIManager(this);

        //Use EventHandler from params if they != 0 else use NULL to pointer
        if(params.EventHandler == NULL)
        {
            UserEventHandler = 0;
        }
        else
        {
            UserEventHandler = params.EventHandler;
            UserEventHandler->capture();
        }
        io::Log::println("Init:CNovaEngine - done.",ELL_DEEP_DEBUG);

        sprintf(buf,"Engine loading time %lu ms.",Timer::getTime() - time);
        io::Log::println(buf);
    }
}
//--------------------------------------------------------------------------------------------------------
CNovaEngine::~CNovaEngine()
{
    io::Log::println("Releasing engine root classes...",ELL_INFO);


    //EXTARMINATE ALL CLASSES !!!!
    io::Log::println("Releasing SceneManager class...",ELL_DEEP_DEBUG);
    if(SceneManager)
        SceneManager->release();
    io::Log::println("Releasing GUIManager class...",ELL_DEEP_DEBUG);
    if(GUIManager)
        GUIManager->release();

    io::Log::println("Releasing TextureManager class...",ELL_DEEP_DEBUG);
    if(TextureManager)
        TextureManager->release();

    io::Log::println("Releasing GeometryManager class...",ELL_DEEP_DEBUG);
    if(GeometryManager)
        GeometryManager->release();

    io::Log::println("Releasing ResourceManager class...",ELL_DEEP_DEBUG);
    if(ResourceManager)
        ResourceManager->release();
    io::Log::println("Releasing FileSys class...",ELL_DEEP_DEBUG);
    if(FileSys)
        FileSys->release();

    io::Log::println("Releasing Renderer class...",ELL_DEEP_DEBUG);
    if(Renderer)
        Renderer->release();
    io::Log::println("Releasing Window class...",ELL_DEEP_DEBUG);
    if(Window)
        Window->release();

    io::Log::println("Releasing UserEventHandler class...",ELL_DEEP_DEBUG);
    if(UserEventHandler)
        UserEventHandler->release();

}
//--------------------------------------------------------------------------------------------------------
void CNovaEngine::closeEngine()
{
    still_alive = false;

    //------------------------------------
    //Send exit event
    SEvent event;
    event.event_type = EET_WINDOW;
    event.Window.event_type = EETW_CLOSED;
    this->pushEvent(event);
    //------------------------------------

    io::Log::println("Exit command receivered...",ELL_INFO);
}
//--------------------------------------------------------------------------------------------------------
void CNovaEngine::registerEventHandler(IEventHandler* NewHandler)
{
    //grab new Handler and release old (if need)
    if(NewHandler)
        NewHandler->capture();
    if(UserEventHandler)
        UserEventHandler->release();

    UserEventHandler = NewHandler;
}
//-------------------------------------------------------------------------------------------------------
bool CNovaEngine::pushEvent(SEvent event)
{
    if(UserEventHandler)
    {
        if(UserEventHandler->OnEvent(event))
            return 1;
    }
    if(GUIManager)
    {
        if(GUIManager->OnEvent(event))
            return 1;
    }
}
//--------------------------------------------------------------------------------------------------------
bool CNovaEngine::update()
{
    if(!still_alive)
        return 0;

    //Check main engine systems
    bool win_sa = Window->update();
    bool rdr_sa = Renderer->update();

    if(!win_sa)
        io::Log::println("Error occurred in window class!",ELL_FATAL_ERROR);

    if(!rdr_sa)
        io::Log::println("Error occurred in renderer class!",ELL_FATAL_ERROR);

    //Return one if Window and renderer still alive else return zero
    if(win_sa && rdr_sa)
        return 1;
    else
        return 0;
}
//--------------------------------------------------------------------------------------------------------
bool CNovaEngine::run()
{
    return update();
}
//--------------------------------------------------------------------------------------------------------
}
