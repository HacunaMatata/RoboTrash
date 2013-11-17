#ifndef TYPES_H
#define TYPES_H


//------------------------------digital
//integer
typedef char              s8;
typedef unsigned char     u8;
typedef short             s16;
typedef unsigned short    u16;
typedef int               s32;
typedef unsigned int      u32;
typedef long int          s64;
typedef unsigned long int u64;
//float
typedef float             f32;
typedef double            f64;
typedef double            d64;
//ex
typedef unsigned char     byte;
typedef char*             c_str;
//extended types

#include "dimension2d_t.h"
#include "vector2d_t.h"
#include "vector3d_t.h"
#include "matrix4_t.h"
#include "color4_t.h"
#include "rect_t.h"
#include <string>
#include <vector>



namespace novaengine
{
namespace core
{
///Type Dimension
typedef dimension2d_t<s32> dimension2ds;
typedef dimension2d_t<u32> dimension2du;
typedef dimension2d_t<f32> dimension2df;
typedef dimension2d_t<f64> dimension2dd;
///Type Vector2d
typedef vector2d_t<s32> vector2ds;
typedef vector2d_t<f32> vector2df;
typedef vector2d_t<f64> vector2dd;
///Type Vector3d
typedef vector3d_t<s32> vector3ds;
typedef vector3d_t<f32> vector3df;
typedef vector3d_t<f64> vector3dd;
typedef vector3d_t<f64> vector3d;
///Type Matrix
typedef matrix4_t<f32> matrix4f;
typedef matrix4_t<f32> matrixd;
///Type Rect
typedef rect_t<s32> rects;
typedef rect_t<u32> rectu;
typedef rect_t<f32> rectf;
typedef rect_t<f64> rectd;
///Type Color
typedef color4_t<u8>    color4u;
typedef color4_t<f32>   color4f;
typedef color4_t<f64>   color4d;

///! Temp typedef,in future i replace this on my own STL
//Str
typedef  std::basic_string<char>     cstring;
typedef  std::basic_string<wchar_t>  wstring;
//Arr
//In future i replace all "std::vector" on "core::Array"

}
}


#endif // TYPES_H
