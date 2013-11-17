#ifndef SVERTEX_H
#define SVERTEX_H

#include "Types.h"
namespace novaengine
{
namespace renderer
{

/// \brief Handle Vertex struct(Pos,TexCord,Normal,Color)
struct SVertex
{
    core::vector3df Position;
    core::vector2df TexCoord;
    core::vector3df Normal;
    core::color4u   VertexColor;
};

}
}
#endif // SVERTEX_H
