#ifndef CGUIMANAGER_H
#define CGUIMANAGER_H

#include "Types.h"
#include "INovaEngine.h"
#include "IRenderer.h"

#include "IGUIManager.h"

#include "IGUILayout.h"
#include "IGUIButton.h"
#include "IGUIImage.h"


namespace novaengine
{
namespace gui
{

class CGUIManager : public IGUIManager
{
public:
    CGUIManager(INovaEngine* rootengine);
    virtual ~CGUIManager();

    renderer::IRenderer* getRenderer();

    bool OnEvent(SEvent event);
    void pushGUIEvent(s32 NodeID,s32 event_type,s32 var1);

    //----------------------------------------------------ManageLayouts
    void setActiveLayout(IGUILayout* Layout = 0);
    IGUILayout* getActiveLayout();

    IGUILayout* getRootLayout();
    //-----------------------------------------------------------------

    //----------------------------------------------------ManageFonts
    bool initFont(IFont* font);

    void drawText(const char*    text,core::rects bounds_rect = core::rects(0,0,0,0), u32 clip_flags = 0);
    void drawText(const wchar_t* text,core::rects bounds_rect = core::rects(0,0,0,0), u32 clip_flags = 0);


    void   setActiveFont(IFont* font);
    IFont* getActiveFont();
    IFont* getDefaultFont();
    //-----------------------------------------------------------------
    IGUIButton* createGUIButton(s32 id,core::rects Location);
    IGUIImage*  createGUIImage(renderer::ITexture* texture,core::rectf TextureSourceRect,s32 id ,core::rects Location);

    renderer::IVertexArray* buildTextMesh(const char*    text,core::rects bounds_rect = core::rects(0,0,0,0), u32 clip_flags = 0);
    renderer::IVertexArray* buildTextMesh(const wchar_t* text,core::rects bounds_rect = core::rects(0,0,0,0), u32 clip_flags = 0);

    void useGUIOrthoProjection();
    void renderGUI();


protected:
private:

    void resize_arrays(u32 v,u32 i);
    std::vector<core::vector3df> verticles;
    std::vector<core::vector2df> texcoords;
    std::vector<u32> indices;

    IGUILayout* ActiveLayout;
    IGUILayout* RootLayout;

    core::matrix4f GUIOrthoProjection;      // Prebuilded ortho projection
    core::dimension2du lastViewPortSize;    // If it changed -then we rebuild GUIOthoProjection

    //fonts
    IFont* ActiveFont;
    IFont* DefaultFont;

    INovaEngine* Engine;
    renderer::IRenderer* Renderer;
};

}
}

#endif // CGUIMANAGER_H
