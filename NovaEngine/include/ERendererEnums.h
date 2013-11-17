#ifndef ERENDERERENUMS_H
#define ERENDERERENUMS_H


namespace novaengine
{
namespace renderer
{

enum E_RENDERER_TYPE
{
    ERT_NULL        = 0x0,
    ERT_OPENGL      = 0x1,
};
//------------------------------------------
enum E_RENDERER_FUTURES
{
    ERF_RENDER_GRAPHICS     = 0x1,
    ERF_VBO_SUPPORT         = 0x2,
    ERF_RENDER_TO_TEXTURE   = 0x3,
};
//------------------------------------------
enum E_RENDER_STATE
{
    ERS_ENABLE_DEPTH_TEST   = 0x0,
    ERS_DEPTH_TEST_MODE     = 0x2,
    ERS_ENABLE_BLENDING     = 0x3,
    ERS_BLENDING_MODE       = 0x4,
    ERS_ENABLE_TEXTURES_2D  = 0x5,
    ERS_ENABLE_WIREFRAME    = 0x6,
    ERS_ENABLE_CULL_FACE    = 0x7,
    ERS_CULL_FACE_MODE      = 0x8,
};
//------------------------------------------
enum E_DEPTH_TEST_MODE
{
    EDTM_NEVER      =   0x00,
    EDTM_LESS       =   0x01,
    EDTM_EQUAL      =   0x02,
    EDTM_LEQUAL     =   0x03,
    EDTM_GREATER    =   0x04,
    EDTM_NOTEQUAL   =   0x05,
    EDTM_GEQUAL     =   0x06,
    EDTM_ALWAYS     =   0x07
};
//------------------------------------------
enum E_CULL_FACE_MODE
{
    ECFM_FRONT = 0x1,
    ECFM_BACK  = 0x2,
    ECFM_ALL   = 0x3,
};
//------------------------------------------
enum E_BLENDING_MODE
{
    Hmm_im_dont_know_what_add_here_now = 0xbad, //!< Realy...
};
//------------------------------------------
enum E_PRIMITIVE_TYPE
{
    EPT_POINTS              = 0x10,
    EPT_LINES               = 0x20,
    EPT_LINES_STRIP         = 0x21,
    EPT_TRIANGLES           = 0x30,
    EPT_TRIANGLES_STRIP     = 0x31,
    EPT_QUAD                = 0x40,
    EPT_QUAD_STRIP          = 0x41,
};
//------------------------------------------
enum E_MATRIX_TYPE
{
    EMT_PROJECTION = 0x0,
    EMT_VIEW       = 0x1,
    EMT_MODEL      = 0x2,
    EMT_TEXTURE    = 0x3,
};
//------------------------------------------
enum E_VERTEX_FORMAT
{
    EVF_VERTEX        = 0x1,
    EVF_TEXCOORD      = 0x2,
    EVF_NORMAL        = 0x4,
    EVF_VERTEX_COLOR  = 0x8,
};
//------------------------------------------
enum E_VERTEX_ARRAY_TYPE
{
    EVAT_UNDEFINDED = 0x0, //Not Definded
    EVAT_RAWDATA    = 0x1, //VertexArray
    EVAT_VBO        = 0x2, //VertexBufferObject (VBO)
};
//------------------------------------------
enum E_RENDER_TARGET_TYPE
{
    ERTT_COLOR_BUFFER_1 = 0x01,
    ERTT_COLOR_BUFFER_2 = 0x02,
    ERTT_COLOR_BUFFER_3 = 0x04,
    ERTT_COLOR_BUFFER_4 = 0x08,
    ERTT_DEPTH_BUFFER   = 0x10,
    ERTT_STENCIL_BUFFER = 0x20,

};

}
}
#endif // ERENDERERENUMS_H
