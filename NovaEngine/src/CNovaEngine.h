#ifndef CENGINE_H
#define CENGINE_H






#include "INovaEngine.h"
#include "SEngineParams.h"
#include "Logger.h"
#include "Timer.h"
#include "IEventHandler.h"

#include "IWindow.h"
#include "IRenderer.h"

#include "ITextureManager.h"
#include "IGeometryManager.h"

#include "ISceneManager.h"
#include "IGUIManager.h"

#include "Logger.h"

#include "GL/glew.h"

namespace novaengine
{

class CNovaEngine : public INovaEngine
{
public:
    CNovaEngine(SEngineParams params);
    ~CNovaEngine();



    bool update();
    bool run();

    void registerEventHandler(IEventHandler* NewHandler);

    bool pushEvent(SEvent event);

    inline u64 getTime(){return Timer::getTime();};

    void closeEngine();

    //--------------------------
    window::IWindow* getWindow()
    {
        return Window;
    }

    renderer::IRenderer* getRenderer()
    {
        return Renderer;
    }

    io::IFileSystem* getFileSystem()
    {
        return FileSys;
    }

    IResourceManager* getResourceManager()
    {
        return ResourceManager;
    }

    ITextureManager* getTextureManager()
    {
        return TextureManager;
    }

    IGeometryManager* getGeometryManager()
    {
        return GeometryManager;
    }

    scene::ISceneManager* getSceneManager()
    {
        return SceneManager;
    }

    gui::IGUIManager*     getGUIManager()
    {
        return GUIManager;
    }


protected:
private:

    window::IWindow* Window;
    renderer::IRenderer*    Renderer;

    io::IFileSystem*        FileSys;
    IResourceManager*       ResourceManager;

    ITextureManager*        TextureManager;
    IGeometryManager*       GeometryManager;

    scene::ISceneManager*   SceneManager;
    gui::IGUIManager*       GUIManager;




    bool still_alive;

    //----------------------EventHandlers
    IEventHandler* UserEventHandler;
};

}
#endif // CENGINE_H
