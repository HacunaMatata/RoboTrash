#ifndef CTEXTUREMANAGER_H
#define CTEXTUREMANAGER_H

#include "NovaEngine.h"
#include "ITextureManager.h"
#include "Logger.h"
#include "IResourceManager.h"
#include "SPixelFormat.h"
#include "CImage.h"


#include <map>

namespace novaengine
{

class CTextureManager : public ITextureManager
{
public:
    CTextureManager(IResourceManager* ResourceManager_param,renderer::IRenderer* Renderer_param);
    virtual ~CTextureManager();

    renderer::IImage*   createEmptyImage(core::dimension2du size,renderer::E_PIXEL_FORMAT pf);
    renderer::ITexture* createEmptyTexture(core::dimension2du size,renderer::E_PIXEL_FORMAT pf);

    renderer::IImage*    createImageFromStream(renderer::E_PIXEL_FORMAT pf,core::dimension2du dim,u8* data);
    renderer::ITexture*  createTextureFromStream(renderer::E_PIXEL_FORMAT pf,core::dimension2du dim,u8* data);

    renderer::ITexture* getTexture(renderer::IImage* img);
    renderer::IImage*   getImage(renderer::ITexture* tex);

    renderer::ITexture* loadTexture(const char* file);
    renderer::IImage*   loadImage(const char* file);

protected:
private:

    std::vector<renderer::ITexture*> TextureArray;


    //------------------

    renderer::IRenderer* Renderer;
    IResourceManager* ResourceManager;
};

}

#endif // CTEXTUREMANAGER_H
