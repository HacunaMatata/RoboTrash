#ifndef IRENDERER_H
#define IRENDERER_H

#include "Object.h"
#include "Types.h"
#include "ERendererEnums.h"

#include "ITexture.h"
#include "IImage.h"
#include "IVertexArray.h"
#include "IVertexBufferObject.h"
#include "CMaterial.h"
#include "STextureGenParams.h"

namespace novaengine
{
namespace renderer
{

class IRenderer : public Object
{
public:


    //--------------------------------------------------------------------------
    virtual bool update() = 0;
    //--------------------------------------------------------------------------
    virtual void OnResize() = 0;
    virtual void setViewport(core::rectu) = 0;
    virtual core::rectu getViewport() = 0;
    //--------------------------------------------------------------------------
    virtual void begin_frame(bool clear_viewport=true,core::color4f Color = core::color4f(0,0,0,0)) = 0;
    virtual void end_frame() = 0;
    //--------------------------------------------------------------------------
    virtual const char* getVendorName() = 0;
    virtual const char* getVersionName() = 0;
    virtual const char* getRendererName() = 0;
    //--------------------------------------------------------------------------
    virtual void setTextureGenParams(STextureGenParams) = 0;
    virtual STextureGenParams getTextureGenParams() = 0;
    virtual ITexture* GenTexture(IImage*,STextureGenParams* = 0) = 0;
    virtual IImage*   GenImage(ITexture*) = 0;
    //--------------------------------------------------------------------------
    virtual void setTransform(const core::matrix4f&,E_MATRIX_TYPE) = 0;
    virtual const core::matrix4f& getTransform(E_MATRIX_TYPE) = 0;
    //--------------------------------------------------------------------------
    virtual void setActiveTexture(ITexture*) = 0;
    virtual ITexture* getActiveTexture() = 0;
    //--------------------------------------------------------------------------
    virtual void setActiveMaterial(IMaterial*) = 0;
    virtual IMaterial* getActiveMaterial() = 0;
    //--------------------------------------------------------------------------
    virtual void setRenderState(int flag,int value = 1) = 0;
    virtual int  getRenderState(int flag) = 0;
    //--------------------------------------------------------------------------
    virtual bool isSupported(E_RENDERER_FUTURES future) = 0;
    //--------------------------------------------------------------------------
    virtual f32 getFPS() = 0;       // Frame per second
    virtual f32 getMPF() = 0;       // Miliseconds per frame
    virtual u32 getPPD() = 0;       // Primitives per draw
    virtual u32 getVPD() = 0;       // Vertex per draw
    //--------------------------------------------------------------------------
    virtual void setRenderTarget(int target_type,ITexture* target_texture) = 0;
    //-----------------------------------------------------------------------VBO
    virtual void buildVertexBufferObject(IVertexArray*   array)   = 0;//Create vbo
    virtual void rebuildVertexBufferObject(IVertexArray*) = 0;//Rebuild current vbo
    virtual void drawVertexBufferObject(IVertexArray*)    = 0;//Draw vbo
    //--------------------------------------------------------------------------
    virtual void drawPrimitiveList(const SVertex*,u32 VertexCount,E_PRIMITIVE_TYPE,u32 VertexFormat) = 0; //Cookies
    virtual void drawIndexedPrimitiveList(const u32* Index,u32 IndexCount,const SVertex*,u32 VertexCount,E_PRIMITIVE_TYPE,u32 VertexFormat) = 0;
    virtual void drawArrays(u32 indices_count,u32 vertex_count,const u32* indices,const core::vector3df* verticles,const core::vector2df* texverts,const core::vector3df* normals,const core::color4u* colors,E_PRIMITIVE_TYPE) = 0;
    //Additional draw functions for easy drawing mesh and VertexArray
    virtual void drawVertexArray(IVertexArray*) = 0;
    //virtual void drawMesh(IMesh* mesh) = 0;

    virtual void draw3dRectangle(const core::vector3df& p1,const core::vector3df& p2,const core::vector3df& p3,const core::vector3df& p4,core::rectf TexCord = core::rectf(0,0,1,1)) = 0;
    virtual void draw3dTriangle(const core::vector3df& p1,const core::vector3df& p2,const core::vector3df& p3) = 0;
    virtual void draw3dLine(const core::vector3df& start,const core::vector3df& end,u32 LineWidth = 1) = 0;
    virtual void draw3dPoint(const core::vector3df& position,u32 PointSize = 1) = 0;

    virtual void draw2dRectangle(const core::vector2ds& lb,const core::vector2ds& rt,core::rectf TexCord = core::rectf(0,0,1,1)) = 0;
    virtual void draw2dTriangle(const core::vector2ds& p1,const core::vector2ds& p2,const core::vector2ds& p3) = 0;
    virtual void draw2dLine(const core::vector2ds& start,const core::vector2ds& end,u32 LineWidth = 1) = 0;
    virtual void draw2dPoint(const core::vector2ds& position,u32 PointSize = 1) = 0;


    virtual u32 getType() = 0;
};


}

}


#endif // IRenderer_H
