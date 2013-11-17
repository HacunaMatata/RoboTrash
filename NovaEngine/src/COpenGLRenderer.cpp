#include "COpenGLRenderer.h"


namespace novaengine
{
namespace renderer
{
//--------------------------------------------------------------------------------------------------------

COpenGLRenderer::COpenGLRenderer(SEngineParams params,INovaEngine* RootEngine)
{
    setObjectName("OpenGLRenderer");
    io::Log::println("Init. COpenGLRenderer - begin.",ELL_DEBUG_ENGINE);

    versionname   =  reinterpret_cast<const char*>(glGetString(GL_VERSION));
    vendorname    =  reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    renderername  =  reinterpret_cast<const char*>(glGetString(GL_RENDERER));
    extensionlist =  reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));
    //-------------------------------------------------------------------------
    //we get from versionname just numbers
    u32 p = 0;
    while(versionname[p] != '\0' && versionname[p] != ' ')
        p++;
    char* temp_versionname = new char[p+1];
    for(u32 i = 0; i<p; i++)
        temp_versionname[i] = versionname[i];
    temp_versionname[p] = '\0';
    versionname = temp_versionname;
    //-------------------------------------------------------------------------
    active_framebuffer_object = 0;
    active_renderbuffer_object = 0;
    //-------------------------------------------------------------------------
    PrimitevesPerDraw = 0;
    PrimitevesDrawNow = 0;
    still_alive = true;
    ViewportSize = params.WindowSize;

    Window = RootEngine->getWindow();
    //-------------------------------------------------------------------------

    glClearColor(0,0,0,0);
    glClearDepth(1.0f);


    setRenderState(ERS_ENABLE_TEXTURES_2D,true);

    setRenderState(ERS_ENABLE_BLENDING,true);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    setRenderState(ERS_ENABLE_DEPTH_TEST,true);
    setRenderState(ERS_DEPTH_TEST_MODE,EDTM_LEQUAL);

    setRenderState(ERS_ENABLE_CULL_FACE,true);
    setRenderState(ERS_CULL_FACE_MODE,ECFM_BACK);


    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT,GL_FASTEST);

    io::Log::println("OpenGL version  ",versionname);
    io::Log::println("OpenGL vendor   ",vendorname);
    io::Log::println("OpenGL renderer ",renderername);
    //-------------------------------------------------
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        char buf[256];
        sprintf(buf,"Cannot init GLEW %s",glewGetErrorString(err));
        io::Log::println(buf,ELL_FATAL_ERROR);
        still_alive = false;
    }
    else
    {
        char buf[256];
        sprintf(buf,"Using GLEW v.%s",glewGetString(GLEW_VERSION));
        io::Log::println(buf);
    }
    //--------------------------------------------------
    setTransform(core::matrix4f(),EMT_PROJECTION);
    setTransform(core::matrix4f(),EMT_VIEW);
    setTransform(core::matrix4f(),EMT_MODEL);

    //fix opengl texture coords from left-bottom to left-top
    core::matrix4f texture;
    texture.setScale(core::vector3df(1,-1,1));
    setTransform(texture,EMT_TEXTURE);


    OnResize();

    enable_client_states(false,false,false,false);
    io::Log::println("Init. COpenGLRenderer - done.",ELL_DEBUG_ENGINE);

}

COpenGLRenderer::~COpenGLRenderer()
{
    delete versionname;

    if(GLEW_ARB_framebuffer_object)
    {
        if(active_framebuffer_object)
            glDeleteFramebuffers(1,&active_framebuffer_object);
    }
}
//--------------------------------------------------------------------------------------------------------
bool COpenGLRenderer::COpenGLRenderer::update()
{
    if(still_alive)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//--------------------------------------------------------------------------------------------------------
///----------------------------
void COpenGLRenderer::COpenGLRenderer::begin_frame(bool clear_viewport,core::color4f Color)
{
    glClearColor(Color.Red,Color.Green,Color.Blue,Color.Alpha);
    GLbitfield GL_FLAGS = 0;

    GL_FLAGS |= GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;

    glFrontFace(GL_CCW);

    if(clear_viewport)
        glClear(GL_FLAGS);
}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::COpenGLRenderer::end_frame()
{
    fps_counter.register_frame();

    PrimitevesPerDraw = PrimitevesDrawNow;
    PrimitevesDrawNow = 0;

    VertexPerDraw = VertexDrawNow;
    VertexDrawNow = 0;

    Window->SwapBuffers();
}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::OnResize()
{
    FrameSize = Window->getWindowSize();

    core::rectu new_vp_rect;

    new_vp_rect.X1 = 0;
    new_vp_rect.Y1 = 0;
    new_vp_rect.X2 = Window->getWindowSize().width;
    new_vp_rect.Y2 = Window->getWindowSize().height;

    setViewport(new_vp_rect);

}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::setViewport(core::rectu nvp)
{
    glViewport(nvp.X1,FrameSize.height - nvp.Y2,nvp.X2,nvp.Y2 - nvp.Y1);
    ViewportRect = nvp;
    ViewportSize = core::dimension2du(nvp.X2 - nvp.X1,nvp.Y2 - nvp.Y1);
    //io::Log::println("View port size: w%d h%d",ViewportSize.width,ViewportSize.height);
}
//--------------------------------------------------------------------------------------------------------
core::rectu COpenGLRenderer::getViewport()
{
    return ViewportRect;
}
//--------------------------------------------------------------------------------------------------------
///----------------------------
const char* COpenGLRenderer::getVendorName()
{
    return vendorname;
}
//--------------------------------------------------------------------------------------------------------
const char* COpenGLRenderer::getVersionName()
{
    return versionname;
}
//--------------------------------------------------------------------------------------------------------
const char* COpenGLRenderer::getRendererName()
{
    return renderername;
}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::setTextureGenParams(STextureGenParams tgp)
{
    CurrentTextureGenParams = tgp;
}
//--------------------------------------------------------------------------------------------------------
STextureGenParams COpenGLRenderer::getTextureGenParams()
{
    return CurrentTextureGenParams;
}
//--------------------------------------------------------------------------------------------------------
ITexture* COpenGLRenderer::COpenGLRenderer::GenTexture(IImage* img,STextureGenParams* tgp)
{
    if(!img)
    {
        io::Log::println("[Renderer]: Image pointer contain null!",ELL_ERROR);
        return NULL;
    }
    if(!tgp)
    {
        tgp = &CurrentTextureGenParams;
    }

    unsigned int GlTexture;

    glGenTextures(1,&GlTexture);
    glBindTexture(GL_TEXTURE_2D,GlTexture);

    /// Texture generation
    char buf[256]; //!< tmp string
    //----------------------------TEXTURE_MAG_FILTER
    switch(tgp->Texture_mag_filter)
    {
    case ETBF_LINEAR:
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        break;

    case ETBF_NEAREST:
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        break;

    default:
        sprintf(buf,"[Renderer]: unsuported texture generation flag:%s[%d]","mag_filter",tgp->Texture_mag_filter);
        io::Log::println(buf,ELL_WARNING);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        break;
    }

    //----------------------------TEXTURE_MIN_FILTER
    switch(tgp->Texture_min_filter)
    {
    case ETBF_LINEAR:
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        break;

    case ETBF_NEAREST:
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        break;

    default:
        sprintf(buf,"[Renderer]: unsuported texture generation flag:%s[%d]","min_filter",tgp->Texture_min_filter);
        io::Log::println(buf,ELL_WARNING);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        break;
    }
    //--------------------------WRAP_U
    switch(tgp->Texture_wrap_u)
    {
    case ETBF_REPEAT:
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_REPEAT);
        break;

    case ETBF_NOT_REPEAT:
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_CLAMP);
        break;

    default:

        sprintf(buf,"[Renderer]: unsuported texture generation flag:%s[%d]","wrap_u",tgp->Texture_wrap_u);
        io::Log::println(buf,ELL_WARNING);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_REPEAT);
        break;
    }
    //--------------------------WRAP_W
    switch(tgp->Texture_wrap_w)
    {
    case ETBF_REPEAT:
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        break;

    case ETBF_NOT_REPEAT:
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
        break;

    default:

        sprintf(buf,"[Renderer]: unsuported texture generation flag:%s[%d]","wrap_w",tgp->Texture_wrap_w);
        io::Log::println(buf,ELL_WARNING);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        break;
    }
    //-----------------------------

    GLenum GL_PixelFormat;
    GLenum GL_InternalFormat;
    E_PIXEL_FORMAT PixelFormat = img->getPixelFormat();


    switch(PixelFormat)
    {
    case EPF_R8G8B8:
        GL_PixelFormat      = GL_RGB;
        GL_InternalFormat   = GL_RGBA;
        break;

    case EPF_R8G8B8A8:
        GL_PixelFormat      = GL_RGBA;
        GL_InternalFormat   = GL_RGBA;
        break;

    case EPF_B8G8R8:
        GL_PixelFormat      = GL_BGR;
        GL_InternalFormat   = GL_RGBA;
        break;

    case EPF_B8G8R8A8:
        GL_PixelFormat      = GL_BGRA;
        GL_InternalFormat   = GL_RGBA;
        break;
    case EPF_DEPTH:
        GL_PixelFormat      = GL_DEPTH_COMPONENT;
        GL_InternalFormat   = GL_DEPTH_COMPONENT;
        break;
    }

    glTexImage2D(
        GL_TEXTURE_2D                   ,
        0                               ,
        GL_InternalFormat               ,
        img->getImageDimension().width  ,
        img->getImageDimension().height ,
        0                               ,
        GL_PixelFormat                  ,
        GL_UNSIGNED_BYTE                ,
        img->lock()
    );

    glBindTexture(GL_TEXTURE_2D,0);

    return new COpenGLTexture(img->getImageDimension(),GlTexture);
}
//--------------------------------------------------------------------------------------------------------
IImage*   COpenGLRenderer::COpenGLRenderer::GenImage(ITexture* tex)
{
    if(!tex)
        return NULL;

    u8* pixels = new u8[tex->getTextureDimension().width * tex->getTextureDimension().width * 4];

    glBindTexture(GL_TEXTURE_2D,*(GLuint*)tex->getRendererTexture());
    glGetTexImage(GL_TEXTURE_2D,0,GL_RGBA,GL_UNSIGNED_BYTE,pixels);
    glBindTexture(GL_TEXTURE_2D,0);

    IImage* TextureImg = new CImage(EPF_R8G8B8A8,tex->getTextureDimension(),pixels);

    return TextureImg;
}
//--------------------------------------------------------------------------------------------------------
///----------------------------
void COpenGLRenderer::setTransform(const core::matrix4f& mat,E_MATRIX_TYPE mtype)
{

    switch(mtype)
    {

    case EMT_PROJECTION:

        //--------------------------------------
        if(ProjectionMatrix == mat)
            return;
        //--------------------------------------
        ProjectionMatrix = mat;

        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(ProjectionMatrix.getPointer());
        //--------------------------------------
        break;
    case EMT_VIEW:
    case EMT_MODEL:

        //--------------------------------------
        if(mtype == EMT_VIEW)
        {
            if(ViewMatrix == mat)
                return;
            ViewMatrix  = mat;
        }
        else
        {
            if(ModelMatrix == mat)
                return;
            ModelMatrix = mat;
        }
        //--------------------------------------
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf((ViewMatrix * ModelMatrix).getPointer());
        //--------------------------------------
        break;
    case EMT_TEXTURE:

        //--------------------------------------
        if(TextureMatrix == mat)
            return;
        //--------------------------------------
        TextureMatrix = mat;
        glMatrixMode(GL_TEXTURE);
        glLoadMatrixf(TextureMatrix.getPointer());
        //--------------------------------------
        break;
    }


}
//--------------------------------------------------------------------------------------------------------
const core::matrix4f& COpenGLRenderer::getTransform(E_MATRIX_TYPE mtype)
{
    switch(mtype)
    {

    case EMT_PROJECTION:
        return ProjectionMatrix;
    case EMT_VIEW:
        return ViewMatrix;
    case EMT_MODEL:
        return ModelMatrix;
    case EMT_TEXTURE:
        return TextureMatrix;

    }
}
//--------------------------------------------------------------------------------------------------------
///----------------------------
void COpenGLRenderer::setActiveTexture(ITexture* tex)
{
    if(!tex)
    {
        glBindTexture(GL_TEXTURE_2D,0);
        return;
    }

    glBindTexture(GL_TEXTURE_2D,*(GLuint*)tex->getRendererTexture());
    CurrentTexture = tex;
}
//--------------------------------------------------------------------------------------------------------
ITexture* COpenGLRenderer::getActiveTexture()
{
    return CurrentTexture;
}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::setActiveMaterial(IMaterial* material)
{
    if(material)
    {
        glColor4ub(material->getMaterialColor().Red,material->getMaterialColor().Green,material->getMaterialColor().Blue,material->getMaterialColor().Alpha);
        setActiveTexture(material->getMaterialTexture());
        setRenderState(ERS_ENABLE_WIREFRAME,material->getMaterialWireframe());

        CurrentMaterial = material;
    }
    else
    {
        glColor4ub(255,255,255,255);
        setActiveTexture(NULL);
    }
}
//--------------------------------------------------------------------------------------------------------
IMaterial* COpenGLRenderer::getActiveMaterial()
{
    return CurrentMaterial;
}
//--------------------------------------------------------------------------------------------------------
///----------------------------
void COpenGLRenderer::setRenderState(int flag,int value)
{
    switch(flag)
    {
        //!-------------------------------DEPTH_BUFFER
    case ERS_ENABLE_DEPTH_TEST:
        if(value)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);
        RenderStates[ERS_ENABLE_DEPTH_TEST] = value;
        break;

    case ERS_DEPTH_TEST_MODE:
        if(value == EDTM_NEVER)     glDepthFunc(GL_NEVER);
        if(value == EDTM_LESS)      glDepthFunc(GL_LESS);
        if(value == EDTM_EQUAL)     glDepthFunc(GL_EQUAL);
        if(value == EDTM_LEQUAL)    glDepthFunc(GL_LEQUAL);
        if(value == EDTM_GREATER)   glDepthFunc(GL_GREATER);
        if(value == EDTM_NOTEQUAL)  glDepthFunc(GL_NOTEQUAL);
        if(value == EDTM_GEQUAL)    glDepthFunc(GL_GEQUAL);
        if(value == EDTM_ALWAYS)    glDepthFunc(GL_ALWAYS);
        RenderStates[ERS_DEPTH_TEST_MODE] = value;
        break;
        //!-------------------------------PIXEL_BLEND

    case ERS_ENABLE_BLENDING:
        if(value)
            glEnable(GL_BLEND);
        else
            glDisable(GL_BLEND);
        RenderStates[ERS_ENABLE_BLENDING] = value;
        break;

        //!-------------------------------TEXTURE_MAPPING
    case ERS_ENABLE_TEXTURES_2D:
        if(value)
            glEnable(GL_TEXTURE_2D);
        else
            glDisable(GL_TEXTURE_2D);
        RenderStates[ERS_ENABLE_TEXTURES_2D] = value;
        break;

        //!-------------------------------WIREFRAME_RENDER
    case ERS_ENABLE_WIREFRAME:
        if(value)
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        RenderStates[ERS_ENABLE_WIREFRAME] = value;
        break;

        //!-------------------------------CULL_FACE
    case ERS_ENABLE_CULL_FACE:
        if(value)
            glEnable(GL_CULL_FACE);
        else
            glDisable(GL_CULL_FACE);
        RenderStates[ERS_ENABLE_CULL_FACE] = value;
        break;

    case ERS_CULL_FACE_MODE:
        if(value == ECFM_BACK)      glCullFace(GL_BACK);
        if(value == ECFM_FRONT)     glCullFace(GL_FRONT);
        if(value == ECFM_ALL)       glCullFace(GL_FRONT_AND_BACK);
        RenderStates[ERS_CULL_FACE_MODE] = value;
        break;
    default:
        break;
    }

}
//--------------------------------------------------------------------------------------------------------
int COpenGLRenderer::getRenderState(int flag)
{
    switch(flag)
    {
        //!-------------------------------DEPTH_BUFFER
    case ERS_ENABLE_DEPTH_TEST:
        return RenderStates[ERS_ENABLE_DEPTH_TEST];
    case ERS_DEPTH_TEST_MODE:
        return RenderStates[ERS_DEPTH_TEST_MODE];
        //!-------------------------------PIXEL_BLEND
    case ERS_ENABLE_BLENDING:
        return RenderStates[ERS_ENABLE_BLENDING];
        //!-------------------------------TEXTURE_MAPPING
    case ERS_ENABLE_TEXTURES_2D:
        return RenderStates[ERS_ENABLE_TEXTURES_2D];
        //!-------------------------------CULL_FACE
    case ERS_ENABLE_CULL_FACE:
        return RenderStates[ERS_ENABLE_CULL_FACE];
    case ERS_CULL_FACE_MODE:
        return RenderStates[ERS_CULL_FACE_MODE];

    default:
        return 0;

    }
}
//--------------------------------------------------------------------------------------------------------
bool COpenGLRenderer::isSupported(E_RENDERER_FUTURES future)
{
    switch(future)
    {
    case ERF_RENDER_GRAPHICS:
        return true;
    case ERF_VBO_SUPPORT:
        return (GLEW_ARB_vertex_buffer_object);
    case ERF_RENDER_TO_TEXTURE:
        return (GLEW_ARB_framebuffer_object);
    }
}
//--------------------------------------------------------------------------------------------------------
f32 COpenGLRenderer::getFPS()
{
    return fps_counter.getFPS();    // Frame per second
}
//--------------------------------------------------------------------------------------------------------
f32 COpenGLRenderer::getMPF()
{
    return fps_counter.getMPF();    // Miliseconds per frame
}
//--------------------------------------------------------------------------------------------------------
u32 COpenGLRenderer::getPPD()
{
    return PrimitevesPerDraw;       // Primitives per draw
}
//--------------------------------------------------------------------------------------------------------
u32 COpenGLRenderer::getVPD()
{
    return VertexPerDraw;           // Vertex per draw
}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::initFrameBuffers()
{

}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::setRenderTarget(int target_type,ITexture* target_texture)
{
    ///If we have version 3.0 or > opengl context we use core framebuffer
    if(GLEW_ARB_framebuffer_object && GLEW_VERSION_3_0)
    {
        // Preparing framebuffer //
        if(active_framebuffer_object == 0)
            glGenFramebuffers(1,&active_framebuffer_object);


        if(target_type == 0)
        {
            glBindFramebuffer(GL_FRAMEBUFFER,0);
            OnResize();
        }
        else
        {
            GLuint              gltex         = 0;
            core::dimension2du  texture_size  = FrameSize;

            if(target_texture != NULL)
            {
                gltex           = *(GLuint*)target_texture->getRendererTexture();
                texture_size    =           target_texture->getTextureDimension();

                FrameSize = texture_size;
            }

            setViewport(core::rectu(0,0,texture_size.width,texture_size.height));

            glBindFramebuffer(GL_FRAMEBUFFER,active_framebuffer_object);

            switch(target_type)
            {
            case ERTT_COLOR_BUFFER_1:
                glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, gltex, 0);
                break;
            case ERTT_COLOR_BUFFER_2:
                glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, gltex, 0);
                break;
            case ERTT_COLOR_BUFFER_3:
                glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, gltex, 0);
                break;
            case ERTT_COLOR_BUFFER_4:
                glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, gltex, 0);
                break;

            case ERTT_DEPTH_BUFFER:
                glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, gltex, 0);
                break;
            }
            GLenum err = glCheckFramebufferStatus(GL_FRAMEBUFFER);
            if(err != GL_FRAMEBUFFER_COMPLETE)
            {
                //io::Log::println("Something wrong with framebuffer...",ELL_ERROR);
                switch(err)
                {
                case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                    io::Log::println("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
                    break;
                case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
                    io::Log::println("GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT");
                    break;
                case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                    io::Log::println("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
                    break;
                case GL_FRAMEBUFFER_UNSUPPORTED:
                    io::Log::println("GL_FRAMEBUFFER_UNSUPPORTED");
                    break;
                default:
                    io::Log::println("Unknow error.");
                }

                return;
            }
        }
    }
    ///If we no have version 3.0 opengl context we use framebuffer from EXT
    if(GLEW_ARB_framebuffer_object && !GLEW_VERSION_3_0)
    {
        // Preparing framebuffer //
        if(active_framebuffer_object == 0)
            glGenFramebuffersEXT(1,&active_framebuffer_object);


        if(target_type == 0)
        {
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);
            OnResize();
        }
        else
        {
            GLuint              gltex         = 0;
            core::dimension2du  texture_size  = FrameSize;

            if(target_texture != NULL)
            {
                gltex           = *(GLuint*)target_texture->getRendererTexture();
                texture_size    =           target_texture->getTextureDimension();

                FrameSize = texture_size;
            }

            setViewport(core::rectu(0,0,texture_size.width,texture_size.height));

            glBindFramebuffer(GL_FRAMEBUFFER_EXT,active_framebuffer_object);

            switch(target_type)
            {
            case ERTT_COLOR_BUFFER_1:
                glFramebufferTexture(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, gltex, 0);
                break;
            case ERTT_COLOR_BUFFER_2:
                glFramebufferTexture(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT, gltex, 0);
                break;
            case ERTT_COLOR_BUFFER_3:
                glFramebufferTexture(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT2_EXT, gltex, 0);
                break;
            case ERTT_COLOR_BUFFER_4:
                glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3_EXT, gltex, 0);
                break;

            case ERTT_DEPTH_BUFFER:
                glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, gltex, 0);
                break;
            }

            if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            {
                io::Log::println("Something wrong with framebuffer...",ELL_ERROR);
                return;
            }
        }
    }

}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::buildVertexBufferObject(IVertexArray* buff)
{
    if(GLEW_ARB_vertex_array_object || GLEW_ARB_vertex_buffer_object)
    {

        //!----------------------------------------------------------------------
        COpenGLVertexBufferObject* vbo = new COpenGLVertexBufferObject(buff);

        if(vbo->isOk() == false)
        {
            io::Log::println("Cannot create VBO.",ELL_ERROR);
            buff->setArrayType(EVAT_RAWDATA);
            vbo->anihilate();
            return;
        }

        buff->set_vbo_pointer(vbo);
        //!----------------------------------------------------------------------
    }
    else
    {
        buff->setArrayType(EVAT_RAWDATA);
        io::Log::println("VBO not supported...",ELL_ERROR);
    }
}

//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::rebuildVertexBufferObject(IVertexArray* buff)
{
    COpenGLVertexBufferObject* vbo = (COpenGLVertexBufferObject*)buff->get_vbo_pointer();
    vbo->rebuild_buffer(buff);
}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::drawVertexBufferObject(IVertexArray* buff)
{
    COpenGLVertexBufferObject* vbo = (COpenGLVertexBufferObject*)buff->get_vbo_pointer();

    u32 IndexCount    = buff->getIndicesCount();
    u32 VertexCount   = buff->getVertexCount();
    u32 PrimitiveType = buff->getPrimitiveType();


    GLenum GLPrimitiveType   = 0;
    u32    VertexInPrimitive = 0;
    //!Convert E_PRIMITIVE_TYPE to GLenum
    to_opengl_primitive((E_PRIMITIVE_TYPE)PrimitiveType,GLPrimitiveType,VertexInPrimitive);

    //----------------------------------------------
    PrimitevesDrawNow   +=      VertexCount     /   VertexInPrimitive;
    VertexDrawNow       +=      VertexCount;
    //----------------------------------------------

    if(GLEW_ARB_vertex_array_object)
    {
        vbo->bind_buffer();

        bool iva = glIsVertexArray(vbo->vao_id);
        bool ivb = glIsBuffer(vbo->vbo_id_verticles);
        bool iib = glIsBuffer(vbo->vbo_id_indices);

        if(IndexCount != 0)
        {
            glDrawElements(GLPrimitiveType,IndexCount,GL_UNSIGNED_INT,0);
        }
        else
        {
            glDrawArrays(GLPrimitiveType,0,VertexCount);
        }
        vbo->unbind_buffer();

        glBindBuffer(GL_ARRAY_BUFFER,0);
        if(IndexCount)
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    }
    else if(GLEW_ARB_vertex_buffer_object)
    {
        vbo->bind_buffer();

        //------------------------------------------------------------
        glEnableClientState(GL_VERTEX_ARRAY         );
        glEnableClientState(GL_TEXTURE_COORD_ARRAY  );
        glEnableClientState(GL_NORMAL_ARRAY         );
        glEnableClientState(GL_COLOR_ARRAY          );
        //------------------------------------------------------------
        glVertexPointer     (3  ,   GL_FLOAT        ,   sizeof(SVertex) ,   (void*)  0  );
        glTexCoordPointer   (2  ,   GL_FLOAT        ,   sizeof(SVertex) ,   (void*) 12  );
        glNormalPointer     (       GL_FLOAT        ,   sizeof(SVertex) ,   (void*) 20  );
        glColorPointer      (4  ,   GL_UNSIGNED_BYTE,   sizeof(SVertex) ,   (void*) 32  );
        //------------------------------------------------------------
        if(IndexCount != 0)
            glDrawElements(GLPrimitiveType,IndexCount,GL_UNSIGNED_INT,0);
        else
            glDrawArrays(GLPrimitiveType,0,VertexCount);
        //---------------------------------------------

        vbo->unbind_buffer();
    }
}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::drawPrimitiveList(const SVertex* verticles,u32 VertexCount,E_PRIMITIVE_TYPE PrimitiveType,u32 VertexFormat)
{
    drawIndexedPrimitiveList(NULL,0,verticles,VertexCount,PrimitiveType,VertexFormat);
}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::drawIndexedPrimitiveList(const u32* Index,u32 IndexCount,const SVertex* verticles,u32 VertexCount,E_PRIMITIVE_TYPE PrimitiveType,u32 VertexFormat)
{
    if(verticles == NULL)
        return;
    //------------------------------------------------------------
    bool have_verticles = (VertexFormat & EVF_VERTEX);
    bool have_texcoords = (VertexFormat & EVF_TEXCOORD);
    bool have_normals   = (VertexFormat & EVF_NORMAL);
    bool have_colors    = (VertexFormat & EVF_VERTEX_COLOR);
    //!Enable/disable client states for drawing
    enable_client_states(have_verticles,have_texcoords,have_normals,have_colors);

    //!Send verticles to video adapter
    if(have_verticles)
        glVertexPointer(3,GL_FLOAT,sizeof(SVertex), &verticles[0].Position);
    if(have_texcoords)
        glTexCoordPointer(2,GL_FLOAT,sizeof(SVertex),&verticles[0].TexCoord);
    if(have_normals)
        glNormalPointer(GL_FLOAT,sizeof(SVertex),&verticles[0].Normal);
    if(have_colors)
        glColorPointer(4,GL_UNSIGNED_BYTE,sizeof(SVertex),&verticles[0].VertexColor);
    //------------------------------------------------------------
    GLenum GLPrimitiveType   = 0;
    u32    VertexInPrimitive = 0;
    //!Convert E_PRIMITIVE_TYPE to GLenum
    to_opengl_primitive((E_PRIMITIVE_TYPE)PrimitiveType,GLPrimitiveType,VertexInPrimitive);
    //----------------------------------------------
    if(Index != NULL && IndexCount != 0)
        glDrawElements(GLPrimitiveType,IndexCount,GL_UNSIGNED_INT,Index);
    else
        glDrawArrays(GLPrimitiveType,0,VertexCount);
    //----------------------------------------------
    PrimitevesDrawNow   +=      VertexCount     /   VertexInPrimitive;
    VertexDrawNow       +=      VertexCount;
    //----------------------------------------------

}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::drawArrays(u32 indices_count,u32 vertex_count,const u32* indices,const core::vector3df* verticles,const core::vector2df* texverts,const core::vector3df* normals,const core::color4u* colors,E_PRIMITIVE_TYPE PrimitiveType)
{
    //------------------------------------------------------------
    bool have_verticles = (verticles!=NULL);
    bool have_texcoords = (texverts !=NULL);
    bool have_normals   = (normals  !=NULL);
    bool have_colors    = (colors   !=NULL);

    //!Enable/disable client states for drawing
    enable_client_states(have_verticles,have_texcoords,have_normals,have_colors);

    //!Send verticles to video adapter
    if(have_verticles)
        glVertexPointer(    3,  GL_FLOAT,           0,  verticles);
    if(have_texcoords)
        glTexCoordPointer(  2,  GL_FLOAT,           0,  texverts);
    if(have_normals)
        glNormalPointer(        GL_FLOAT,           0,  normals);
    if(have_colors)
        glColorPointer(     4,  GL_UNSIGNED_BYTE,   0,  colors);
    //------------------------------------------------------------
    GLenum GLPrimitiveType   = 0;
    u32    VertexInPrimitive = 0;
    //!Convert E_PRIMITIVE_TYPE to GLenum
    to_opengl_primitive((E_PRIMITIVE_TYPE)PrimitiveType,GLPrimitiveType,VertexInPrimitive);
    //----------------------------------------------
    if(indices != NULL && indices_count != 0)
        glDrawElements(GLPrimitiveType,indices_count,GL_UNSIGNED_INT,indices);
    else
        glDrawArrays(GLPrimitiveType,0,vertex_count);
    //----------------------------------------------
    PrimitevesDrawNow   +=      vertex_count     /   VertexInPrimitive;
    VertexDrawNow       +=      vertex_count;
    //----------------------------------------------

}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::drawVertexArray(IVertexArray* buff)
{
    if(buff->getArrayType() == EVAT_RAWDATA)
    {

        if(buff->getIndicesCount() == 0)
            drawPrimitiveList(reinterpret_cast<SVertex*>(buff->getVerticles()),buff->getVertexCount(),buff->getPrimitiveType(),buff->getVertexFormat());
        else
            drawIndexedPrimitiveList(buff->getIndices(),buff->getIndicesCount(),reinterpret_cast<SVertex*>(buff->getVerticles()),buff->getVertexCount(),buff->getPrimitiveType(),buff->getVertexFormat());

    }
    if(buff->getArrayType() == EVAT_VBO)
    {

        if(buff->get_vbo_pointer() == NULL)
        {
            buildVertexBufferObject(buff);
        }

        if(buff->get_vbo_pointer() == NULL)
            return;

        if(buff->get_vbo_pointer()->required_rebuild())
        {
            rebuildVertexBufferObject(buff);
        }

        drawVertexBufferObject(buff);

    }
}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::draw3dRectangle(const core::vector3df& p1,const core::vector3df& p2,const core::vector3df& p3,const core::vector3df& p4,core::rectf TexCord)
{
    //--------------------------
    //!     1   3
    //      0   0
    //      |  /|
    //      | / |
    //      |/  |
    //      0   0
    //!     2   4
    //--------------------------
    const float points[12] = {p1.x,p1.y,p1.z,p2.x,p2.y,p2.z,p4.x,p4.y,p4.z,p3.x,p3.y,p3.z};
    const float uwpoints[8] = {TexCord.X1,TexCord.Y1,TexCord.X1,TexCord.Y2,TexCord.X2,TexCord.Y1,TexCord.X2,TexCord.Y2};

    enable_client_states(true,true,false,false);

    glVertexPointer(3,GL_FLOAT,0,points);
    glTexCoordPointer(2,GL_FLOAT,0,uwpoints);

    glDrawArrays(GL_TRIANGLE_STRIP,0,4);

    PrimitevesDrawNow += 2;
    VertexDrawNow     += 4;
}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::draw3dTriangle(const core::vector3df& p1,const core::vector3df& p2,const core::vector3df& p3)
{
    const float points[9] = {p1.x,p1.y,p1.z,p2.x,p2.y,p2.z,p3.x,p3.y,p3.z};
    const float uwpoints[8] = {0,0,0,1,1,1};

    enable_client_states(true,true,false,false);

    glVertexPointer(3,GL_FLOAT,0,points);
    glTexCoordPointer(2,GL_FLOAT,0,uwpoints);

    glDrawArrays(GL_TRIANGLES,0,3);

    PrimitevesDrawNow += 1;
    VertexDrawNow     += 3;
}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::draw3dLine(const core::vector3df& start,const core::vector3df& end,u32 LineWidth)
{
    glLineWidth(LineWidth);


    const float points[6] = {start.x,start.y,start.z,end.x,end.y,end.z};

    enable_client_states(true,false,false,false);

    glVertexPointer(3,GL_FLOAT,0,points);
    glDrawArrays(GL_LINES,0,2);

    PrimitevesDrawNow += 1;
    VertexDrawNow     += 2;

}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::draw3dPoint(const core::vector3df& position,u32 PointSize)
{
    glPointSize(PointSize);

    const float points[3] = {position.x,position.y,position.z};

    enable_client_states(true,false,false,false);

    glVertexPointer(3,GL_FLOAT,0,points);
    glDrawArrays(GL_POINTS,0,1);

    PrimitevesDrawNow += 1;
    VertexDrawNow     += 1;
}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::draw2dRectangle(const core::vector2ds& lb,const core::vector2ds& rt,core::rectf TexCord)
{
    const s32 points[8] = {lb.x,rt.y,lb.x,lb.y,rt.x,rt.y,rt.x,lb.y};
    const float uwpoints[8] = {TexCord.X1,TexCord.Y1,TexCord.X1,TexCord.Y2,TexCord.X2,TexCord.Y1,TexCord.X2,TexCord.Y2};

    enable_client_states(true,true,false,false);

    glVertexPointer(2,GL_INT,0,points);
    glTexCoordPointer(2,GL_FLOAT,0,uwpoints);

    PrimitevesDrawNow += 2;
    VertexDrawNow     += 4;
}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::draw2dTriangle(const core::vector2ds& p1,const core::vector2ds& p2,const core::vector2ds& p3)
{
    const s32 points[6] = {p1.x,p1.y,p2.x,p2.y,p3.x,p3.y};
    const float uwpoints[6] = {0,0,0,1,1,1};

    enable_client_states(true,true,false,false);

    glVertexPointer(2,GL_INT,0,points);
    glTexCoordPointer(2,GL_FLOAT,0,uwpoints);

    glDrawArrays(GL_TRIANGLES,0,3);

    PrimitevesDrawNow += 1;
    VertexDrawNow     += 3;
}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::draw2dLine(const core::vector2ds& start,const core::vector2ds& end,u32 LineWidth)
{
    glLineWidth(LineWidth);

    enable_client_states(true,false,false,false);

    const s32 points[4] = {start.x,start.y,end.x,end.y};

    glVertexPointer(2,GL_INT,0,points);
    glDrawArrays(GL_LINES,0,2);

    PrimitevesDrawNow += 1;
    VertexDrawNow     += 2;
}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::draw2dPoint(const core::vector2ds& position,u32 PointSize)
{
    glPointSize(PointSize);


    const s32 points[2] = {position.x,position.y};

    enable_client_states(true,false,false,false);

    glVertexPointer(2,GL_INT,0,points);
    glDrawArrays(GL_POINTS,0,1);

    PrimitevesDrawNow   += 1;
    VertexDrawNow       += 1;
}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::to_opengl_primitive(E_PRIMITIVE_TYPE engine_primitive,u32& gl_primitive,u32& vertexperprimitive)
{
    switch(engine_primitive)
    {
    case EPT_POINTS:
        gl_primitive = GL_POINTS;
        vertexperprimitive = 1;
        break;
    case EPT_LINES:
        gl_primitive = GL_LINES;
        vertexperprimitive = 2;
        break;
    case EPT_LINES_STRIP:
        gl_primitive = GL_LINE_STRIP;
        vertexperprimitive = 2;
        break;
    case EPT_TRIANGLES:
        gl_primitive = GL_TRIANGLES;
        vertexperprimitive = 3;
        break;
    case EPT_TRIANGLES_STRIP:
        gl_primitive = GL_TRIANGLE_STRIP;
        vertexperprimitive = 2;
        break;
    case EPT_QUAD:
        gl_primitive = GL_QUADS;
        vertexperprimitive = 4;
        break;
    case EPT_QUAD_STRIP:
        gl_primitive = GL_QUAD_STRIP;
        vertexperprimitive = 2;
        break;
    default:
        gl_primitive = GL_TRIANGLES;
        vertexperprimitive = 3;
        break;
    }
}
//--------------------------------------------------------------------------------------------------------
void COpenGLRenderer::enable_client_states(bool vert,bool tex,bool norm,bool color)
{
    //---------------------------------------------------------VertexArray
    if(vert)
    {
        if(RendererClientStatesList[RCSL_VERTEX_ARRAY] == false)
        {
            RendererClientStatesList[RCSL_VERTEX_ARRAY] = true;
            glEnableClientState(GL_VERTEX_ARRAY);
        }
    }
    else
    {
        if(RendererClientStatesList[RCSL_VERTEX_ARRAY] == true)
        {
            RendererClientStatesList[RCSL_VERTEX_ARRAY] = false;
            glDisableClientState(GL_VERTEX_ARRAY);
        }
    }
    //---------------------------------------------------------TextureCoordArray
    if(tex)
    {
        if(RendererClientStatesList[RCSL_TEXCORD_ARRAY] == false)
        {
            RendererClientStatesList[RCSL_TEXCORD_ARRAY] = true;
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        }
    }
    else
    {
        if(RendererClientStatesList[RCSL_TEXCORD_ARRAY] == true)
        {
            RendererClientStatesList[RCSL_TEXCORD_ARRAY] = false;
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
    }
    //---------------------------------------------------------NormalArray
    if(norm)
    {
        if(RendererClientStatesList[RCSL_NORMAL_ARRAY] == false)
        {
            RendererClientStatesList[RCSL_NORMAL_ARRAY] = true;
            glEnableClientState(GL_NORMAL_ARRAY);
        }
    }
    else
    {
        if(RendererClientStatesList[RCSL_NORMAL_ARRAY] == true)
        {
            RendererClientStatesList[RCSL_NORMAL_ARRAY] = false;
            glDisableClientState(GL_NORMAL_ARRAY);
        }
    }
    //---------------------------------------------------------ColorArray
    if(color)
    {
        if(RendererClientStatesList[RCSL_COLOR_ARRAY] == false)
        {
            RendererClientStatesList[RCSL_COLOR_ARRAY] = true;
            glEnableClientState(GL_COLOR_ARRAY);
        }
    }
    else
    {
        if(RendererClientStatesList[RCSL_COLOR_ARRAY] == true)
        {
            RendererClientStatesList[RCSL_COLOR_ARRAY] = false;
            glDisableClientState(GL_COLOR_ARRAY);
        }
    }
}
//--------------------------------------------------------------------------------------------------------
}
}

