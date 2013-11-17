#ifndef CFONT_H
#define CFONT_H

#include "Types.h"
#include "CVertexArray.h"
#include "IFont.h"

#include <map>
#include <unordered_map>

namespace novaengine
{
namespace gui
{

class CFont : public IFont
{
public:
    CFont(renderer::IImage* font_image,SFontParams p_font_params,SGlyph* p_glyphs,u32 p_glyphs_count):
        FontImage(NULL),
        FontTexture(NULL)
    {
        if(font_image)
        {
            FontImage = font_image;
            FontImage->capture();
        }

        FontParams = p_font_params;

        if(p_glyphs)
        {
            /* insert all glyphs in map-array  */
            for(u32 i = 0; i < p_glyphs_count; i ++ )
            {
                Glyphs[p_glyphs[i].Glyph] = p_glyphs[i];
            }
            rebuild_glyphs();

        }
    }

    virtual ~CFont()
    {
        if(FontImage)
            FontImage->release();
        if(FontTexture)
            FontTexture->release();
    }

    renderer::ITexture* getFontTexture()
    {
        return FontTexture;
    }

    void setFontTexture(renderer::ITexture* texture)
    {
        if(texture)
            texture->capture();
        if(FontTexture)
            FontTexture->release();

        FontTexture = texture;
    }

    renderer::IImage* getFontImage()
    {
        return FontImage;
    }

    void setFontImage(renderer::IImage* image)
    {
        if(image)
            image->capture();
        if(FontImage)
            FontImage->release();

        FontImage = image;
    }

    s32  getFontMaxHeight()
    {
        return FontParams.Font_MaxHeight;
    }
    void setFontMaxHeight(s32 newHeight)
    {
        FontParams.Font_MaxHeight = newHeight;
    }

    SGlyph* getGlyph(u8 sym)
    {
        return &(Glyphs[sym]);
    }

    SGlyph* getGlyph_w(u16 sym)
    {
        return &(Glyphs[sym]);
    }

    core::dimension2du calculate_text_size(const char* text)
    {
        u32 sym_text_len = strlen(text);

        core::dimension2du text_size(0,FontParams.Font_MaxHeight);
        u32 str_len = 0;
        for(u32 i = 0; i < sym_text_len; i++)
        {
            if(text[i] == '\n')
            {
                if(str_len > text_size.width)
                    text_size.width = str_len;
                text_size.height += FontParams.Font_MaxHeight;
                str_len = 0;
                continue;
            }

            str_len += getGlyph(text[i])->Glyph_width;
        }


        if(str_len > text_size.width)
            text_size.width = str_len;

        return text_size;
    }
    core::dimension2du calculate_text_size(const wchar_t* text)
    {
        u32 sym_text_len = strlen((char*)text);

        core::dimension2du text_size;
        u32 str_len = 0;
        for(u32 i = 0; i < sym_text_len; i++)
        {
            if(text[i] == '\n')
            {
                text_size.width   = str_len;
                text_size.height += FontParams.Font_MaxHeight;
                str_len = 0;
            }
            str_len += getGlyph(text[i])->Glyph_width;
        }

        return text_size;
    }
    void rebuild_glyphs()
    {

        for(std::unordered_map<wchar_t,SGlyph>::iterator it = Glyphs.begin(),end = Glyphs.end(); it!=end; ++it)
        {

            s32 x_left_off    = (*it).second.Glyph_x_offset;
            s32 x_right_off   = (*it).second.Glyph_width+(*it).second.Glyph_x_offset;

            s32 y_top_off   = (*it).second.Glyph_y_offset;
            s32 y_bot_off   = ((*it).second.Glyph_y_offset + (*it).second.Glyph_height);

            (*it).second.glyph_verticles[0].Position = core::vector3df( x_left_off,    y_bot_off,0);
            (*it).second.glyph_verticles[1].Position = core::vector3df(x_right_off,    y_bot_off,0);
            (*it).second.glyph_verticles[2].Position = core::vector3df(x_right_off,    y_top_off,0);
            (*it).second.glyph_verticles[3].Position = core::vector3df( x_left_off,    y_top_off,0);

            core::rectf loc = (*it).second.Glyph_location;
            (*it).second.glyph_verticles[0].TexCoord = core::vector2df(loc.X1,loc.Y2);
            (*it).second.glyph_verticles[1].TexCoord = core::vector2df(loc.X2,loc.Y2);
            (*it).second.glyph_verticles[2].TexCoord = core::vector2df(loc.X2,loc.Y1);
            (*it).second.glyph_verticles[3].TexCoord = core::vector2df(loc.X1,loc.Y1);
            (*it).second.Glyph_width+=(*it).second.Glyph_x_offset;

            (*it).second.verticles[0] = core::vector3df( x_left_off,    y_bot_off,0);
            (*it).second.verticles[1] = core::vector3df(x_right_off,    y_bot_off,0);
            (*it).second.verticles[2] = core::vector3df(x_right_off,    y_top_off,0);
            (*it).second.verticles[3] = core::vector3df( x_left_off,    y_top_off,0);

            (*it).second.texcoords[0] = core::vector2df(loc.X1,loc.Y2);
            (*it).second.texcoords[1] = core::vector2df(loc.X2,loc.Y2);
            (*it).second.texcoords[2] = core::vector2df(loc.X2,loc.Y1);
            (*it).second.texcoords[3] = core::vector2df(loc.X1,loc.Y1);
        }

    }
protected:
private:
    renderer::IImage*   FontImage;
    renderer::ITexture* FontTexture;

    SFontParams         FontParams;
    std::unordered_map<wchar_t,SGlyph> Glyphs;

};


}
}


#endif // CFONT_H
