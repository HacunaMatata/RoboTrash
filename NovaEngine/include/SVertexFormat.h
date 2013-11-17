#ifndef SVERTEXFORMAT_H
#define SVERTEXFORMAT_H


#include "Types.h"

namespace novaengine
{
namespace render
{

struct SVertexFormat
{
    u32 VertexShift;
    u32 TexCordShift;
    u32 NormalShift;
    u32 VertColorShift;
};

}
}

#endif // SVERTEXFORMAT_H
