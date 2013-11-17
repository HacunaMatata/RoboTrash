#include "CGUIManager.h"


#include "CGUILayout.h"
#include "CGUIButton.h"
#include "CGUIImage.h"

#include "CVertexArray.h"

#include "Logger.h"

#include "defaultfont.h"

namespace novaengine
{
namespace gui
{
CGUIManager::CGUIManager(INovaEngine* rootengine):
    RootLayout(NULL),
    ActiveFont(NULL),
    DefaultFont(NULL)
{
    Engine = rootengine;
    Renderer = rootengine->getRenderer();

    RootLayout = new CGUILayout(this);
    RootLayout->setActive();

    io::IFile* font_stream = Engine->getFileSystem()->open_stream("@integrated_defaultfont\0",file_defaultfont_data,file_defaultfont_lenght);
    DefaultFont = Engine->getResourceManager()->loadFont(font_stream);
    font_stream->release();
    if(DefaultFont == NULL)
    {
        io::Log::println("Cannot load default gui font...",ELL_ERROR);
    }
    else
    {
        setActiveFont(DefaultFont);
    }
}
//--------------------------------------------------------------------------------------------
CGUIManager::~CGUIManager()
{
    if(ActiveFont)
        ActiveFont->release();

    if(DefaultFont)
        DefaultFont->release();

    RootLayout->release();
}
//--------------------------------------------------------------------------------------------
renderer::IRenderer* CGUIManager::getRenderer()
{
    return Renderer;
}
//--------------------------------------------------------------------------------------------
bool CGUIManager::OnEvent(SEvent event)
{
    getActiveLayout()->OnEvent(event);
}
//--------------------------------------------------------------------------------------------
void CGUIManager::pushGUIEvent(s32 NodeID,s32 event_type,s32 var1)
{
    SEvent event;

    event.event_type = EET_GUI;
    event.GUI.NodeID = NodeID;
    event.GUI.event_type = event_type;
    event.GUI.value = var1;

    Engine->pushEvent(event);
}
//--------------------------------------------------------------------------------------------
bool CGUIManager::initFont(IFont* font)
{
    if(font->getFontTexture() == NULL)
    {
        if(font->getFontImage() == NULL)
        {
            io::Log::println("Font init filed - font have not glyph image",ELL_ERROR);
            return false;
        }
        renderer::STextureGenParams tbp;
        tbp.Texture_mag_filter = renderer::ETBF_NEAREST;
        tbp.Texture_min_filter = renderer::ETBF_NEAREST;
        tbp.Texture_wrap_w     = renderer::ETBF_NOT_REPEAT;
        tbp.Texture_wrap_u     = renderer::ETBF_NOT_REPEAT;
        renderer::ITexture* font_texture = Renderer->GenTexture(font->getFontImage(),&tbp);
        font->setFontTexture(font_texture);
        font_texture->release();
    }
    return true;

}
//--------------------------------------------------------------------------------------------
void CGUIManager::drawText(const char* text,core::rects bounds_rect, u32 clip_flags)
{

    if(!text)
        return;

    useGUIOrthoProjection();

    Renderer->setActiveTexture(ActiveFont->getFontTexture());

    u32 text_len = strlen(text);
    //-------------------------------------------------------------------
    resize_arrays(text_len * 4,text_len * 6);
    //-------------------------------------------------------------------
    s32 strideX = bounds_rect.X1;
    s32 strideY = bounds_rect.Y1;

    s32 max_strideX = (bounds_rect.X2 - bounds_rect.X1) + bounds_rect.X1;
    s32 max_strideY = (bounds_rect.Y2 - bounds_rect.Y1) + bounds_rect.Y1;
    //-------------------------------------------------------------------
    bool clip_text = (clip_flags &= ETFF_CLIP_TEXT && bounds_rect.getArea() != 0);
    //-------------------------------------------------------------------

    u32 index_index  = 0;
    u32 vertex_index = 0;

    for(unsigned int i = 0; text[i] != '\0'; i++)
    {

        //-------------------------------------------------------
        if(text[i] == '\n')
        {
            strideY+=ActiveFont->getFontMaxHeight();
            strideX=bounds_rect.X1;
            continue;
        }
        //-----------------------------------------------
        if(clip_text && (strideX  >= max_strideX || strideY  >= max_strideY))
            continue;
        //-----------------------------------------------
        gui::SGlyph* Glyph = ActiveFont->getGlyph(text[i]);
        //-----------------------------------------------
        if(clip_text &&  (strideX + Glyph->Glyph_width  >= max_strideX || strideY + ActiveFont->getFontMaxHeight()  >= max_strideY))
            continue;
        //-----------------------------------------------
        verticles[vertex_index  ] = Glyph->verticles[0].get_add(strideX,strideY,0);
        verticles[vertex_index+1] = Glyph->verticles[1].get_add(strideX,strideY,0);
        verticles[vertex_index+2] = Glyph->verticles[2].get_add(strideX,strideY,0);
        verticles[vertex_index+3] = Glyph->verticles[3].get_add(strideX,strideY,0);

        texcoords[vertex_index  ].set(Glyph->texcoords[0]);
        texcoords[vertex_index+1].set(Glyph->texcoords[1]);
        texcoords[vertex_index+2].set(Glyph->texcoords[2]);
        texcoords[vertex_index+3].set(Glyph->texcoords[3]);
        //-----------------------------------------------------
        strideX += Glyph->Glyph_width;
        //-----------------------------------------------
        vertex_index += 4;
        //-----------------------------------------------
    }

    index_index = (vertex_index >> 2) * 6;
    getRenderer()->drawArrays(index_index,vertex_index,indices.data(),verticles.data(),texcoords.data(),NULL,NULL,renderer::EPT_TRIANGLES);
}
//--------------------------------------------------------------------------------------------

void CGUIManager::drawText(const wchar_t* text,core::rects bounds_rect, u32 clip_flags)
{

    if(!text)
        return;

    useGUIOrthoProjection();

    Renderer->setActiveTexture(ActiveFont->getFontTexture());

    u32 text_len = wcslen(text);
    //-------------------------------------------------------------------
    resize_arrays(text_len * 4,text_len * 6);
    //-------------------------------------------------------------------
    s32 strideX = bounds_rect.X1;
    s32 strideY = bounds_rect.Y1;

    s32 max_strideX = (bounds_rect.X2 - bounds_rect.X1) + bounds_rect.X1;
    s32 max_strideY = (bounds_rect.Y2 - bounds_rect.Y1) + bounds_rect.Y1;
    //-------------------------------------------------------------------
    bool clip_text = (clip_flags &= ETFF_CLIP_TEXT && bounds_rect.getArea() != 0);
    //-------------------------------------------------------------------

    u32 index_index  = 0;
    u32 vertex_index = 0;
    for(unsigned int i = 0; text[i] != '\0'; i++)
    {
        //-------------------------------------------------------
        if(text[i] == '\n')
        {
            strideY+=ActiveFont->getFontMaxHeight();
            strideX=bounds_rect.X1;
            continue;
        }
        //-----------------------------------------------
        if(clip_text && (strideX  >= max_strideX || strideY  >= max_strideY))
            continue;
        //-----------------------------------------------
        gui::SGlyph* Glyph = ActiveFont->getGlyph_w(text[i]);
        //-----------------------------------------------
        if(clip_text &&  (strideX + Glyph->Glyph_width  >= max_strideX || strideY + ActiveFont->getFontMaxHeight()  >= max_strideY))
            continue;
        //-----------------------------------------------
        verticles[vertex_index  ] = Glyph->verticles[0].get_add(strideX,strideY,0);
        verticles[vertex_index+1] = Glyph->verticles[1].get_add(strideX,strideY,0);
        verticles[vertex_index+2] = Glyph->verticles[2].get_add(strideX,strideY,0);
        verticles[vertex_index+3] = Glyph->verticles[3].get_add(strideX,strideY,0);

        texcoords[vertex_index  ].set(Glyph->texcoords[0]);
        texcoords[vertex_index+1].set(Glyph->texcoords[1]);
        texcoords[vertex_index+2].set(Glyph->texcoords[2]);
        texcoords[vertex_index+3].set(Glyph->texcoords[3]);
        //-----------------------------------------------------
        strideX += Glyph->Glyph_width;
        //-----------------------------------------------
        vertex_index += 4;
        //-----------------------------------------------
    }

    index_index = (vertex_index >> 2) * 6;
    getRenderer()->drawArrays(index_index,vertex_index,indices.data(),verticles.data(),texcoords.data(),NULL,NULL,renderer::EPT_TRIANGLES);
}
//--------------------------------------------------------------------------------------------
void CGUIManager::setActiveFont(IFont* font)
{
    if(font)
        font->capture();
    if(ActiveFont)
        ActiveFont->release();

    if(font->getFontTexture() == NULL)
        initFont(font);

    ActiveFont = font;
}
//--------------------------------------------------------------------------------------------
IFont* CGUIManager::getActiveFont()
{
    return ActiveFont;
}
//--------------------------------------------------------------------------------------------
IFont* CGUIManager::getDefaultFont()
{
    return DefaultFont;
}
//--------------------------------------------------------------------------------------------
IGUIButton* CGUIManager::createGUIButton(s32 id,core::rects rect)
{
    IGUIButton* GUIBtn = new CGUIButton(this,id,rect);

    getActiveLayout()->addNode(GUIBtn);
    return GUIBtn;
}
//--------------------------------------------------------------------------------------------
IGUIImage*  CGUIManager::createGUIImage(renderer::ITexture* t,core::rectf r,s32 id,core::rects rect)
{
    IGUIImage* guiImg = new CGUIImage(this,t,r,id,rect);
    getActiveLayout()->addNode(guiImg);
    return guiImg;
}
//--------------------------------------------------------------------------------------------
renderer::IVertexArray* CGUIManager::buildTextMesh(const char*    text,core::rects bounds_rect, u32 clip_flags)
{

}
//--------------------------------------------------------------------------------------------
renderer::IVertexArray* CGUIManager::buildTextMesh(const wchar_t* text,core::rects clip_rect, u32 clip_flags)
{
    return NULL;
}
//--------------------------------------------------------------------------------------------
IGUILayout* CGUIManager::getRootLayout()
{
    return RootLayout;
}
//--------------------------------------------------------------------------------------------
void CGUIManager::setActiveLayout(IGUILayout* Layout)
{
    if(Layout)
        ActiveLayout = Layout;
    else
        ActiveLayout = RootLayout;
}
//--------------------------------------------------------------------------------------------
IGUILayout* CGUIManager::getActiveLayout()
{
    return ActiveLayout;
}
//--------------------------------------------------------------------------------------------
void CGUIManager::useGUIOrthoProjection()
{
    core::dimension2du currentViewPortSize = Renderer->getViewport().getDimension();

    if(currentViewPortSize != lastViewPortSize)
    {
        GUIOrthoProjection.buildOrthographicProjectionMatrix(0,currentViewPortSize.width,currentViewPortSize.height,0,-1,1);
        lastViewPortSize = currentViewPortSize;
    }
    Renderer->setTransform(GUIOrthoProjection ,renderer::EMT_PROJECTION);
    Renderer->setTransform(core::matrix4f()   ,renderer::EMT_VIEW      );
    Renderer->setTransform(core::matrix4f()   ,renderer::EMT_MODEL     );
}
//--------------------------------------------------------------------------------------------
void CGUIManager::renderGUI()
{

    //-----------------------------------------------------------
    ActiveLayout->update();
    ActiveLayout->animate();
    ActiveLayout->render();
    //-----------------------------------------------------------
}
//--------------------------------------------------------------------------------------------
void CGUIManager::resize_arrays(u32 v,u32 i)
{
    if(verticles.size() < v)
        verticles.resize(v);
    if(texcoords.size() < v)
        texcoords.resize(v);

    u32 last_indices_size = indices.size();
    u32 cur_indices_size = i;

    if(last_indices_size < cur_indices_size)
    {
        indices.resize(cur_indices_size);
        u32 vertex_index = (last_indices_size / 6) * 4;

        for(u32 i = last_indices_size; i < cur_indices_size; i += 6)
        {
            indices[i    ] = vertex_index + 0;
            indices[i + 1] = vertex_index + 1;
            indices[i + 2] = vertex_index + 2;
            indices[i + 3] = vertex_index + 2;
            indices[i + 4] = vertex_index + 3;
            indices[i + 5] = vertex_index + 0;

            vertex_index += 4;
        }
    }

}
//--------------------------------------------------------------------------------------------
}
}
