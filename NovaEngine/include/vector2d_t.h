#ifndef vector2d_t_H
#define vector2d_t_H

#include "Types.h"
#include <math.h>
namespace novaengine
{
namespace core
{

template <class T>
class vector2d_t
{
public:
    vector2d_t<T>():
        x(0),y(0)
    {};

    vector2d_t<T>(T val_):
        x(val_),y(val_)
    {};

    vector2d_t<T>(T x_,T y_):
        x(x_),y(y_)
    {};


    vector2d_t set(T _val)
    {
        x = _val;
        y = _val;
        return *this;
    }

    vector2d_t set(T _x,T _y)
    {
        x = _x;
        y = _y;
        return *this;
    }

    vector2d_t set(vector2d_t<T>& other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }

    vector2d_t add(T _val)
    {
        x += _val;
        y += _val;
        return *this;
    }

    vector2d_t add(T _x,T _y)
    {
        x += _x;
        y += _y;
        return *this;
    }

    vector2d_t add(vector2d_t<T>& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    vector2d_t<T> get_add(T _val)
    {
        return vector2d_t<T>(x+_val,y+_val);
    }

    vector2d_t<T> get_add(T _x,T _y)
    {
        return vector2d_t<T>(x+_x,y+_y);
    }

    vector2d_t<T> get_add(const vector2d_t &other)
    {
        return vector2d_t<T>(x+ other.x,y+ other.y);
    }

    vector2d_t<T> operator= (const vector2d_t &other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }

    vector2d_t operator= (T other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }

    vector2d_t<T> operator - () const
    {
        return vector2d_t(-x,-y);
    }

    vector2d_t<T> operator += (const vector2d_t &other)
    {
        x += other.x;
        y += other.y;

        return *this;
    }

    vector2d_t<T> operator -= (const vector2d_t &other)
    {
        x -= other.x;
        y -= other.y;

        return *this;
    }

    vector2d_t<T> operator += (const T v)
    {
        x += v;
        y += v;

        return *this;
    }

    vector2d_t<T> operator -= (const T v)
    {
        x -= v;
        y -= v;

        return *this;
    }

    vector2d_t<T> operator *= (const vector2d_t &other)
    {
        x *= other.x;
        y *= other.y;

        return *this;
    }

    vector2d_t<T> operator *= (const T v)
    {
        x *= v;
        y *= v;

        return *this;
    }

    vector2d_t<T> operator /= (const vector2d_t &other)
    {
        x /= other.x;
        y /= other.y;

        return *this;
    }

    vector2d_t<T> operator /= (const T v)
    {
        x /= v;
        y /= v;

        return *this;
    }

    vector2d_t<T> operator * (const vector2d_t &other)
    {
        T tx = x* other.x;
        T ty = y* other.y;
        return vector2d_t<T>(tx,ty);
    }

    vector2d_t<T> operator * (const T value)
    {
        T tx = x* value;
        T ty = y* value;
        return vector2d_t<T>(tx,ty);
    }

    vector2d_t<T> operator + (const vector2d_t &other)
    {
        T tx = x + other.x;
        T ty = y + other.y;

        return vector2d_t<T>(tx,ty);
    }

    vector2d_t<T> operator - (const vector2d_t &other)
    {
        T tx = x - other.x;
        T ty = y - other.y;

        return vector2d_t<T>(tx,ty);
    }


    vector2d_t<T> operator + (const T v)
    {
        x += v;
        y += v;

        return *this;
    }

    vector2d_t<T> operator - (const T v)
    {
        x -= v;
        y -= v;

        return *this;
    }

    bool operator == (const vector2d_t &other ) const
    {

        return x == other.x && y == other.y;
    }

    bool operator !=  (const vector2d_t &other ) const
    {

        return x != other.x || y != other.y;
    }

    T length () const
    {
        return (T)sqrt( x * x + y * y);
    }

    T lengthSq() const
    {
        return x * x + y * y;
    }

    vector2d_t<T> normalize ()
    {
        return (*this) /= length();
    }

    T distanceTo (const vector2d_t &other)
    {
        return (T) sqrt(sqr(x - other.x) + sqr(y - other.y));
    }

    T distanceToSq (const vector2d_t &other)
    {
        return sqr(x - other.x) + sqr(y - other.y);
    }

    T sqr(T num)
    {
        return num*num;
    }

    //Misc
#ifdef vector3d_t_H
#include "vector3d_t.h"
    vector3d_t<T> to_vector3d() const
    {
        return vector3d_t<T>(x,y,0);
    }
#endif

    T x;
    T y;
};

}

}




#endif // vector2d_t_H
