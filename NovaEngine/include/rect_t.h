#ifndef RECT_T_H
#define RECT_T_H

#include "Types.h"

namespace novaengine
{
namespace core
{

template <class T>
class rect_t
{
public:
  rect_t<T>()
  {
    X1 = 0;
    Y1 = 0;
    X2 = 0;
    Y2 = 0;
  };
  rect_t<T>(T x1,T y1,T x2,T y2)
  {
    X1 = x1;
    Y1 = y1;
    X2 = x2;
    Y2 = y2;
  };
  dimension2d_t<T> getDimension() const
  {
      dimension2d_t<T> td;
      td.width = X2 - X1;
      td.height = Y2 - Y1;
      return td;
  }

  bool operator == (const rect_t<T> &other ) const
  {
    return X1 == other.X1 && X2 == other.X2 && Y1 == other.Y1 && Y2 == other.Y2;
  }

  bool operator != (const rect_t<T> &other ) const
  {
    return X1 != other.X1 || X2 != other.X2 || Y1 != other.Y1 || Y2 != other.Y2;
  }

  bool PointInRect(T point_x,T point_y)
  {
      return (X1 < point_x && X2 > point_x && Y1 < point_y && Y2 > point_y);
  }

  u32 getArea()
  {
      return (X2 - X1) * (Y2 - Y1);
  }

  T X1;
  T Y1;
  T X2;
  T Y2;
};



}
}

#endif // RECT_H
