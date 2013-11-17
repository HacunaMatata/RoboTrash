#ifndef COPENGLTEXTURE_H
#define COPENGLTEXTURE_H

#include "ITexture.h"
#include "ITextureManager.h"
#include "Types.h"

#include "CImage.h"

#include <GL/gl.h>

namespace novaengine
{
namespace renderer
{

class COpenGLTexture : public ITexture
{
public:
    COpenGLTexture(core::dimension2du size,unsigned int glpointer)
    {
        TextureDimension = size;
        OpenGlTexturePointer = glpointer;
        TextureImg = NULL;
    }
    virtual ~COpenGLTexture()
    {
        glDeleteTextures(1,&OpenGlTexturePointer);

        if(TextureImg)
            TextureImg->anihilate();
    }

    core::dimension2du getTextureDimension()
    {
        return TextureDimension;
    }

    void* getRendererTexture()
    {
        return (void*)&OpenGlTexturePointer;
    }

    IImage* lock()
    {
        if(TextureImg != NULL)
            return TextureImg;

        u8* pixels = new u8[TextureDimension.width * TextureDimension.width * 4]; //!< 4 - because we using RGBA format 1 byte per color,include alpha....

        glBindTexture(GL_TEXTURE_2D,OpenGlTexturePointer);
        glGetTexImage(GL_TEXTURE_2D,0,GL_RGBA,GL_UNSIGNED_BYTE,pixels);

        TextureImg = new CImage(EPF_R8G8B8A8,TextureDimension,pixels);

        return TextureImg;
    }

    void unlock()
    {
        if(TextureImg == NULL)
            return;

        glTexSubImage2D(GL_TEXTURE_2D,0,0,0,TextureDimension.width,TextureDimension.height,GL_RGBA,GL_UNSIGNED_BYTE,TextureImg->lock());

        TextureImg->anihilate();
        TextureImg = NULL;
    }
protected:
private:
    core::dimension2du TextureDimension;
    unsigned int OpenGlTexturePointer;

    IImage* TextureImg; //!< Fills by using lock(), need to get pixles pixels of the current texture.Will be delete after call unlock().
};

}
}



#endif // COPENGLTEXTURE_H
