#ifndef IENGINE_H
#define IENGINE_H


#include "Types.h"
#include "Object.h"

#include "IWindow.h"
#include "IRenderer.h"

#include "ISceneManager.h"
#include "IGUIManager.h"

#include "ITextureManager.h"
#include "IGeometryManager.h"

#include "IResourceManager.h"

#include "IFileSystem.h"

#include "IEventHandler.h"
#include "SEvent.h"



namespace novaengine
{

class INovaEngine : public novaengine::Object
{
    public:
            virtual window::IWindow*        getWindow() = 0;
            virtual renderer::IRenderer*      getRenderer() = 0;

            virtual io::IFileSystem* getFileSystem() =0;
            virtual IResourceManager* getResourceManager() = 0;

            virtual ITextureManager*  getTextureManager() = 0;
            virtual IGeometryManager* getGeometryManager() = 0;

            virtual scene::ISceneManager*   getSceneManager() = 0;
            virtual gui::IGUIManager*       getGUIManager() = 0;

            virtual bool pushEvent(SEvent event) = 0;
            virtual void registerEventHandler(IEventHandler* NewHandler) = 0;

            virtual u64 getTime() = 0;

            virtual bool update() = 0;
            virtual bool run()    = 0; //!< same as update()

            virtual void closeEngine() = 0;

    protected:
    private:
};

}

#endif // IENGINE_H
