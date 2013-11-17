#ifndef ITEXTUREMANAGER_H
#define ITEXTUREMANAGER_H

#include "Types.h"
#include "Object.h"
#include "IImage.h"
#include "ITexture.h"


namespace novaengine
{
/// \brief Provides work with image and texture(convert img->tex and tex->img) also use ResourceManager to load Image files
class ITextureManager : public Object
{
    public:

        virtual renderer::IImage*    createEmptyImage(core::dimension2du size,renderer::E_PIXEL_FORMAT pf) = 0;
        virtual renderer::ITexture*  createEmptyTexture(core::dimension2du size,renderer::E_PIXEL_FORMAT pf) = 0;

        virtual renderer::IImage*    createImageFromStream(renderer::E_PIXEL_FORMAT pf,core::dimension2du dim,u8* data) = 0;
        virtual renderer::ITexture*  createTextureFromStream(renderer::E_PIXEL_FORMAT pf,core::dimension2du dim,u8* data) = 0;

        virtual renderer::ITexture*  getTexture(renderer::IImage* img) = 0;
        virtual renderer::IImage*    getImage(renderer::ITexture* tex) = 0;

        virtual renderer::ITexture*  loadTexture(const char* file) = 0;
        virtual renderer::IImage*    loadImage(const char* file) = 0;


    protected:
    private:
};

}
#endif // ITEXTUREMANAGER_H
