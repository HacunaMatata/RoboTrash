#ifndef NMATH_H
#define NMATH_H

#include "Types.h"



namespace novaengine
{
  namespace core
  {
    #ifdef PI
    #undef PI
    #endif
    const f32 PI = 3.14159265359f;

    #ifdef PI64
    #undef PI64
    #endif
    const f64 PI64 = 3.1415926535897932384626433832795028841971693993751;

    //! DEG <-> RAD
    //32bit conversion
    const f32 DEGTORAD = PI / 180.0f;
    const f32 RADTODEG = 180.0f / PI;
    //64bit conversion
    const f64 DEGTORAD64 = PI64 / 180.0;
    const f64 RADTODEG64 = 180.0 / PI64;

    inline f32 RadToDeg(f32 radians)
    {
      return RADTODEG * radians;
    }

    inline f64 RadToDeg(f64 radians)
    {
      return RADTODEG64 * radians;
    }

    inline f32 DegToRad(f32 degrees)
    {
      return DEGTORAD * degrees;
    }

    inline f64 DegToRad(f64 degrees)
    {
      return DEGTORAD64 * degrees;
    }
    //------------------------------
  }
}
#endif // NMATH_H
