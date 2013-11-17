#ifndef IGUIMANAGER_H
#define IGUIMANAGER_H

#include "Types.h"
#include "Object.h"

#include "IEventHandler.h"
#include "IVertexArray.h"
#include "IFont.h"

namespace novaengine
{
namespace gui
{

struct SGUIStringBuildParams
{
    bool or_not_bool;
};

enum E_TEXT_FORMAT_FLAGS
{
    ETFF_CLIP_TEXT                    = 1,
    ETFF_ALIGN_AT_CENTER_OF_RECT      = 2,
    ETFF_ALIGN_AT_RIGHT_SIDE_OF_RECT  = 4,
    ETFF_ALIGN_AT_LEFT_SIDE_OF_RECT   = 8,
};

class IGUILayout;
class IGUINode;
class IGUIButton;
class IGUIImage;
class IGUIStaticText;

class IGUIManager : public Object
{
public:
    virtual bool OnEvent(SEvent event) = 0;
    virtual void pushGUIEvent(s32 NodeID,s32 event_type,s32 var1) = 0;

    //----------------------------------------------------ManageLayouts
    virtual void setActiveLayout(IGUILayout* Layout = 0) = 0;
    virtual IGUILayout* getActiveLayout() = 0;

    virtual IGUILayout* getRootLayout() = 0;
    //-----------------------------------------------------------------

    //----------------------------------------------------ManageFonts
    virtual bool   initFont(IFont* font)      = 0;
    virtual void   setActiveFont(IFont* font) = 0;
    virtual IFont* getActiveFont()            = 0;
    virtual IFont* getDefaultFont()           = 0;
    //-----------------------------------------------------------------
    virtual IGUIButton* createGUIButton(s32 id,core::rects Location) = 0;
    virtual IGUIImage*  createGUIImage(renderer::ITexture* texture,core::rectf TextureSourceRect,s32 id ,core::rects Location)  = 0;
    //-----------------------------------------------------------------
    virtual renderer::IVertexArray* buildTextMesh(const char*    text,core::rects bounds_rect = core::rects(0,0,0,0), u32 clip_flags = 0) = 0;
    virtual renderer::IVertexArray* buildTextMesh(const wchar_t* text,core::rects bounds_rect = core::rects(0,0,0,0), u32 clip_flags = 0) = 0;

    virtual void useGUIOrthoProjection() = 0;

    //--------------------------------------------------------------draw
    virtual void drawText(const char*    text,core::rects bounds_rect = core::rects(0,0,0,0), u32 format_flags = 0) = 0;
    virtual void drawText(const wchar_t* text,core::rects bounds_rect = core::rects(0,0,0,0), u32 format_flags = 0) = 0;

    virtual void renderGUI() = 0;

    virtual renderer::IRenderer* getRenderer() = 0;

protected:
private:
};

}
}
#endif // IGUIMANAGER_H
