#ifndef COPENGLDRIVER_H
#define COPENGLDRIVER_H

#include "GL/glew.h"


#include <GL/gl.h>


#include "COpenGLTexture.h"
#include "COpenGLVertexBufferObject.h"

#include "NovaEngine.h"
#include "IRenderer.h"
#include "Types.h"
#include "SEngineParams.h"
#include "Logger.h"

#include "CFPSCounter.h"

#include <map>

namespace novaengine
{
namespace renderer
{
//-------------------------
enum R_CLIENT_STATES_LIST
{
    RCSL_VERTEX_ARRAY  = 0,
    RCSL_TEXCORD_ARRAY = 1,
    RCSL_NORMAL_ARRAY  = 2,
    RCSL_COLOR_ARRAY   = 3,
    RCSL_STATES_COUNT  = 4,
};
//-------------------------

class COpenGLRenderer : public IRenderer
{
public:
    COpenGLRenderer(SEngineParams params,INovaEngine* RootEngine);
    ~COpenGLRenderer();

    //--------------------------------------------------------------------------
    bool update();
    //--------------------------------------------------------------------------
    void OnResize();
    void setViewport(core::rectu);
    core::rectu getViewport();
    //--------------------------------------------------------------------------
    void begin_frame(bool clear_viewport=true,core::color4f Color = core::color4f(0,0,0,0));
    void end_frame();
    //--------------------------------------------------------------------------
    const char* getVendorName();
    const char* getVersionName();
    const char* getRendererName();
    //--------------------------------------------------------------------------
    void setTextureGenParams(STextureGenParams);
    STextureGenParams getTextureGenParams();
    ITexture* GenTexture(IImage*,STextureGenParams*);
    IImage*   GenImage(ITexture*);
    //--------------------------------------------------------------------------
    void setTransform(const core::matrix4f&,E_MATRIX_TYPE);
    const core::matrix4f& getTransform(E_MATRIX_TYPE);
    //--------------------------------------------------------------------------
    void setActiveTexture(ITexture*);
    ITexture* getActiveTexture();

    void setActiveMaterial(IMaterial* material);
    IMaterial* getActiveMaterial();
    //--------------------------------------------------------------------------
    void setRenderState(int flag,int value);
    int getRenderState(int flag);
    //--------------------------------------------------------------------------
    bool isSupported(E_RENDERER_FUTURES future);
    //--------------------------------------------------------------------------
    f32 getFPS();       //!<  Frame per second
    f32 getMPF();       //!<  Miliseconds per frame
    u32 getPPD();       //!<  Primitives per draw
    u32 getVPD();       //!<  Vertex per draw
    //--------------------------------------------------------------------------
    void initFrameBuffers();
    void setRenderTarget(int target_type,ITexture* target_texture);
    //--------------------------------------------------------------------------
    void buildVertexBufferObject(IVertexArray*);
    void rebuildVertexBufferObject(IVertexArray*);
    void drawVertexBufferObject(IVertexArray*);
    //--------------------------------------------------------------------------

    ///Render   HL
    void drawPrimitiveList(const SVertex*,u32 VertexCount,E_PRIMITIVE_TYPE,u32 VertexFormat);
    void drawIndexedPrimitiveList(const u32* Index,u32 IndexCount,const SVertex*,u32 VertexCount,E_PRIMITIVE_TYPE,u32 VertexFormat);
    void drawArrays(u32 indices_count,u32 vertex_count,const u32* indices,const core::vector3df* verticles,const core::vector2df* texverts,const core::vector3df* normals,const core::color4u* colors,E_PRIMITIVE_TYPE);

    void drawVertexArray(IVertexArray*);
    ///Render   LL
    void draw3dRectangle(const core::vector3df& p1,const core::vector3df& p2,const core::vector3df& p3,const core::vector3df& p,core::rectf TexCord = core::rectf(0,0,1,1));
    void draw3dTriangle(const core::vector3df& p1,const core::vector3df& p2,const core::vector3df& p3);
    void draw3dLine(const core::vector3df& start,const core::vector3df& end,u32 LineWidth = 1);
    void draw3dPoint(const core::vector3df& position,u32 PointSize = 1);

    void draw2dRectangle(const core::vector2ds& lb,const core::vector2ds& rt,core::rectf TexCord = core::rectf(0,0,1,1));
    void draw2dTriangle(const core::vector2ds& p1,const core::vector2ds& p2,const core::vector2ds& p3);
    void draw2dLine(const core::vector2ds& start,const core::vector2ds& end,u32 LineWidth = 1);
    void draw2dPoint(const core::vector2ds& position,u32 PointSize = 1);

    u32 getType()
    {
        return ERT_OPENGL;
    }
protected:
private:
    //Internal functions
    inline void to_opengl_primitive(E_PRIMITIVE_TYPE engine_primitive,u32& gl_primitive,u32& vertexperprimitive);
    inline void enable_client_states(bool vert,bool tex,bool norm,bool color);


    //------------------------
    bool still_alive;
    //states
    ITexture*   CurrentTexture;
    IMaterial*  CurrentMaterial;
    STextureGenParams CurrentTextureGenParams;
    bool ClientState[4];
    //------------------------
    const char* vendorname;
    const char* versionname;
    const char* renderername;
    const char* extensionlist;
    //------------------------
    core::rectu        ViewportRect;
    core::dimension2du ViewportSize;
    core::dimension2du FrameSize;
    //------------------------
    CFPSCounter fps_counter;
    u32 PrimitevesPerDraw;
    u32 PrimitevesDrawNow;
    u32 VertexPerDraw;
    u32 VertexDrawNow;
    //------------------------
    core::matrix4f ProjectionMatrix;
    core::matrix4f ViewMatrix;
    core::matrix4f ModelMatrix;
    core::matrix4f TextureMatrix;
    //------------------------

    //------------------------RTT
    u32 active_framebuffer_object;
    u32 active_renderbuffer_object;
    //---------------------------
    window::IWindow* Window;

    //cache
    //Render States
    std::map<E_RENDER_STATE,int> RenderStates;
    bool RendererClientStatesList[RCSL_STATES_COUNT];



};
}
}
#endif // COPENGLDRIVER_H
