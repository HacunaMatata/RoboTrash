#include "CTextureManager.h"





namespace novaengine
{

CTextureManager::CTextureManager(IResourceManager* ResourceManager_param,renderer::IRenderer* Renderer_param):
    ResourceManager(ResourceManager_param),
    Renderer(Renderer_param)
{

}
//--------------------------------------------------------------------------------------------------------
CTextureManager::~CTextureManager()
{

}
//--------------------------------------------------------------------------------------------------------
renderer::IImage* CTextureManager::createEmptyImage(core::dimension2du size,renderer::E_PIXEL_FORMAT pf)
{
    u8* PixelArray = new u8[size.width * size.height * 4];
    return new renderer::CImage(pf,size,PixelArray);
}
//--------------------------------------------------------------------------------------------------------
renderer::ITexture* CTextureManager::createEmptyTexture(core::dimension2du size,renderer::E_PIXEL_FORMAT pf)
{
    renderer::IImage* img = createEmptyImage(size,pf);
    renderer::ITexture* tex = getTexture(img);
    img->release();
    return tex;
}
//--------------------------------------------------------------------------------------------------------
renderer::IImage*    CTextureManager::createImageFromStream(renderer::E_PIXEL_FORMAT pf,core::dimension2du dim,u8* data)
{
    return new renderer::CImage(pf,dim,data);
}
//--------------------------------------------------------------------------------------------------------
renderer::ITexture*    CTextureManager::createTextureFromStream(renderer::E_PIXEL_FORMAT pf,core::dimension2du dim,u8* data)
{
    renderer::IImage* img = new renderer::CImage(pf,dim,data);
    renderer::ITexture* tex = getTexture(img);
    img->release();
    return tex;
}
//--------------------------------------------------------------------------------------------------------
renderer::ITexture* CTextureManager::getTexture(renderer::IImage* img)
{
    renderer::ITexture* tex = Renderer->GenTexture(img);
    if(!tex)
    {
        io::Log::println("Cannot build texture.");
        return NULL;
    }
    TextureArray.push_back(tex);
    return tex;
}
//--------------------------------------------------------------------------------------------------------
renderer::IImage* CTextureManager::getImage(renderer::ITexture* tex)
{
    renderer::IImage* img = Renderer->GenImage(tex);
    if(!img)
    {
        io::Log::println("Cannot build image.");
        return NULL;
    }
    return img;
}
//--------------------------------------------------------------------------------------------------------
renderer::ITexture*  CTextureManager::loadTexture(const char* file)
{
    renderer::IImage* img = 0;
    img = ResourceManager->loadImage(file);
    if(img)
    {
        renderer::ITexture* tex = getTexture(img);
        img->release();
        return tex;
    }
    else
    {
        return NULL;
    }
}
//--------------------------------------------------------------------------------------------------------
renderer::IImage* CTextureManager::loadImage(const char* file)
{
    return ResourceManager->loadImage(file);
}
//--------------------------------------------------------------------------------------------------------
}
