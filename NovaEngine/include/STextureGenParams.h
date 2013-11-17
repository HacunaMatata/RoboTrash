#ifndef STextureGenParams_H
#define STextureGenParams_H

#include "Types.h"

namespace novaengine
{
namespace renderer
{

enum E_TEXTURE_BUILD_FLAGS
{
    ETBF_UNDEFINED  = 0,
    //-------------------
    ETBF_NEAREST    = 0x01,
    ETBF_LINEAR     = 0x02,
    //-------------------
    ETBF_REPEAT     = 0x11,
    ETBF_NOT_REPEAT = 0x12,

};

struct STextureGenParams
{
    STextureGenParams():
    Texture_mag_filter(ETBF_LINEAR),
    Texture_min_filter(ETBF_LINEAR),
    Texture_wrap_u(ETBF_REPEAT),
    Texture_wrap_w(ETBF_REPEAT),
    Texture_max_level(1)
    {
    }

    u32 Texture_mag_filter;
    u32 Texture_min_filter;
    u32 Texture_wrap_u;
    u32 Texture_wrap_w;

    u32 Texture_max_level; //Mipmap count

};

}
}

#endif // STextureGenParams_H
