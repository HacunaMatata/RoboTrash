#ifndef vector3d_t_H
#define vector3d_t_H

#include "Types.h"

#include <stdio.h>
#include <string.h>

namespace novaengine
{
namespace core
{

template <class T>
class vector3d_t
{
public:
    vector3d_t<T>():
        x(0),y(0),z(0)
    {};

    vector3d_t<T>(T v):
        x(v),y(v),z(v)
    {};

    vector3d_t<T>(T x_,T y_,T z_):
        x(x_),y(y_),z(z_)
    {};


    vector3d_t set(T _val)
    {
        x = _val;
        y = _val;
        z = _val;
        return *this;
    }


    vector3d_t set(T _x,T _y,T _z)
    {
        x = _x;
        y = _y;
        z = _z;
        return *this;
    }

    vector3d_t set(vector3d_t<T>& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    vector3d_t add(T _val)
    {
        x+=_val;
        y+=_val;
        z+=_val;
        return *this;
    }

    vector3d_t add(T _x,T _y,T _z)
    {
        x += _x;
        y += _y;
        z += _z;
        return *this;
    }

    vector3d_t add(vector3d_t<T>& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    vector3d_t<T> get_add(T _val)
    {
        return vector3d_t<T>(x+_val,y+_val,z+_val);
    }

    vector3d_t<T> get_add(T _x,T _y,T _z)
    {
        return vector3d_t<T>(x+_x,y+_y,z+_z);
    }

    vector3d_t<T> get_add(const vector3d_t &other)
    {
        return vector3d_t<T>(x+ other.x,y+ other.y,z+ other.z);
    }

    vector3d_t<T> operator= (const vector3d_t &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    vector3d_t<T> operator= (T other)
    {
        x = other;
        y = other;
        z = other;
        return *this;
    }

    vector3d_t<T> operator - () const
    {
        return vector3d_t<T>(-x,-y,-z);
    }

    vector3d_t<T> operator += (const vector3d_t &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    vector3d_t<T> operator += (const T &value)
    {
        x += value;
        y += value;
        z += value;
        return *this;
    }

    vector3d_t<T> operator + (const vector3d_t &other)
    {
        return vector3d_t<T>(x+ other.x,y+ other.y,z+ other.z);
    }

    vector3d_t<T> operator + (const T &value)
    {
        T tx = x+ value;
        T ty = y+ value;
        T tz = z+ value;
        return vector3d_t<T>(tx,ty,tz);
    }

    vector3d_t<T> operator -= (const vector3d_t &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    vector3d_t<T> operator -= (const T value)
    {
        x -= value;
        y -= value;
        z -= value;
        return *this;
    }

    vector3d_t<T> operator - (const vector3d_t &other)
    {
        T tx = x- other.x;
        T ty = y- other.y;
        T tz = z- other.z;
        return vector3d_t<T>(tx,ty,tz);
    }

    vector3d_t<T> operator - (const T value)
    {
        T tx = x- value;
        T ty = y- value;
        T tz = z- value;
        return vector3d_t<T>(tx,ty,tz);
    }

    vector3d_t<T> operator *= (const vector3d_t &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    vector3d_t<T> operator *= (const T value)
    {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    vector3d_t<T> operator * (const vector3d_t &other)
    {
        T tx = x* other.x;
        T ty = y* other.y;
        T tz = z* other.z;
        return vector3d_t<T>(tx,ty,tz);
    }

    vector3d_t<T> operator * (const T value)
    {
        T tx = x* value;
        T ty = y* value;
        T tz = z* value;
        return vector3d_t<T>(tx,ty,tz);
    }

    vector3d_t<T> operator /= (const vector3d_t &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    vector3d_t<T> operator /= (const T value)
    {
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }

    vector3d_t<T> operator / (const vector3d_t &other)
    {
        T tx = x/ other.x;
        T ty = y/ other.y;
        T tz = z/ other.z;
        return vector3d_t<T>(tx,ty,tz);
    }

    vector3d_t<T> operator / (const T value)
    {
        T tx = x/ value;
        T ty = y/ value;
        T tz = z/ value;
        return vector3d_t<T>(tx,ty,tz);
    }

    bool operator == (const vector3d_t &other ) const
    {

        return x == other.x && y == other.y && z == other.z;
    }

    bool operator !=  (const vector3d_t &other ) const
    {

        return x != other.x && y != other.y && z != other.z;
    }
    //------------------------------------------------------
    T length () const
    {
        return (T)sqrt( x * x + y * y + z * z);
    }

    T lengthSq() const
    {
        return x * x + y * y + z * z;
    }

    vector3d_t<T> normalize ()
    {
        return (*this) /= length();
    }

    vector3d_t<T> cross_Product(const vector3d_t<T>& vec) const
    {
        return vector3d_t<T>(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
    }

    T dot_Product(const vector3d_t<T>& other) const
    {
        return x*other.x + y*other.y + z*other.z;
    }

    T distanceTo (const vector3d_t &other)
    {
        return (T) sqrt(sqr(x - other.x) + sqr(y - other.y) + sqr(z - other.z));
    }

    T distanceToSq (const vector3d_t &other)
    {
        return sqr(x - other.x) + sqr(y - other.y) + sqr(z - other.z);
    }

    T sqr(T num)
    {
        return num*num;
    }

    //Misc
    #ifdef vector2d_t_H
    #include "vector2d_t.h"
    vector2d_t<T> to_vector2d() const
    {
        return vector2d_t<T>(x,y);
    }
    #endif


    T x;
    T y;
    T z;
};


}
}
#endif // VECTOR3_H
