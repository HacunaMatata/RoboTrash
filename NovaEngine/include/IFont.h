#ifndef IFONT_H
#define IFONT_H

#include "Types.h"
#include "IRenderer.h"
#include "IImage.h"
#include "ITexture.h"
#include "IVertexArray.h"

namespace novaengine
{
namespace gui
{
struct SFontParams
{
        u32 Font_Size;
        u32 Font_MaxHeight;
        bool isMono;
        u32 MonoSize;
};

struct SGlyph
{
    u16         Glyph;
    u16         Glyph_width;
    u16         Glyph_height;
    u16         Glyph_x_offset;
    u16         Glyph_y_offset;
    core::rectf Glyph_location;
    renderer::SVertex glyph_verticles[4];
    core::vector3df verticles[4];
    core::vector2df texcoords[4];
};

class IFont : public Object
{
public:



    virtual renderer::ITexture* getFontTexture()                = 0;
    virtual void setFontTexture(renderer::ITexture* texture)    = 0;
    virtual renderer::IImage* getFontImage()                    = 0;
    virtual void setFontImage(renderer::IImage* img)            = 0;

    virtual s32  getFontMaxHeight()    = 0;
    virtual void setFontMaxHeight(s32) = 0;

    virtual SGlyph*             getGlyph(u8  sym)         = 0;
    virtual SGlyph*             getGlyph_w(u16 sym)       = 0;

    virtual core::dimension2du  calculate_text_size(const char* text)   = 0;
    virtual core::dimension2du  calculate_text_size(const wchar_t* text)  = 0;

    virtual void rebuild_glyphs() = 0;

protected:
private:
};

}
}

#endif // IFONT_H
