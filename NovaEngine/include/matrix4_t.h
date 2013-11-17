#ifndef MATRIX4_T_H
#define MATRIX4_T_H

#include "Types.h"
#include "NMath.h"

#include "vector3d_t.h"

#include <stdio.h>
#include <string.h>

#include <math.h>


namespace novaengine
{
namespace core
{

template<class T>
class matrix4_t
{
public:
    matrix4_t()
    {
        matrix = new T[16];
        makeIndetify();
    }
    matrix4_t(const matrix4_t<T>& other)
    {
        matrix = new T[16];
        makeIndetify();

        memcpy(matrix, other.matrix, 16*sizeof(T));
    }


    virtual ~matrix4_t()
    {
        delete matrix;
    }

    inline void makeIndetify()
    {
        memset(matrix,0,16*sizeof(T));
        matrix[0]  = matrix[5] = matrix[10] = matrix[15] = 1;
    }

    bool operator == (const matrix4_t<T> &other ) const
    {
        if(memcmp(matrix,other.matrix,16*sizeof(T)) != 0)
           return false;

        return true;
    }

    bool operator !=  (const matrix4_t<T> &other ) const
    {
        if(memcmp(matrix,other.matrix,16*sizeof(T)) == 0)
           return false;
        return false;
    }

    inline matrix4_t<T>& operator= (const matrix4_t<T>& other)
    {
        memcpy(matrix, other.matrix, 16*sizeof(T));
        return *this;
    }

    inline T& getElement(u32 index)
    {
        return matrix[index];
    }

    inline T& getElement(u32 X_index,u32 Y_index)
    {
        return matrix[4 * Y_index + X_index];
    }

    inline T& operator[](u32 index)
    {
        return matrix[index];
    }

    inline operator T*()
    {
        return matrix;
    }

    inline matrix4_t<T> operator+ (const matrix4_t<T>& other) const
    {
        matrix4_t<T> temp;
        temp.matrix[0]  = matrix[0]+other.matrix[0];
        temp.matrix[1]  = matrix[1]+other.matrix[1];
        temp.matrix[2]  = matrix[2]+other.matrix[2];
        temp.matrix[3]  = matrix[3]+other.matrix[3];
        temp.matrix[4]  = matrix[4]+other.matrix[4];
        temp.matrix[5]  = matrix[5]+other.matrix[5];
        temp.matrix[6]  = matrix[6]+other.matrix[6];
        temp.matrix[7]  = matrix[7]+other.matrix[7];
        temp.matrix[8]  = matrix[8]+other.matrix[8];
        temp.matrix[9]  = matrix[9]+other.matrix[9];
        temp.matrix[10] = matrix[10]+other.matrix[10];
        temp.matrix[11] = matrix[11]+other.matrix[11];
        temp.matrix[12] = matrix[12]+other.matrix[12];
        temp.matrix[13] = matrix[13]+other.matrix[13];
        temp.matrix[14] = matrix[14]+other.matrix[14];
        temp.matrix[15] = matrix[15]+other.matrix[15];
        return temp;
    }

    inline matrix4_t<T>& operator+= (const matrix4_t<T>& other)
    {
        matrix[0]+=other.matrix[0];
        matrix[1]+=other.matrix[1];
        matrix[2]+=other.matrix[2];
        matrix[3]+=other.matrix[3];
        matrix[4]+=other.matrix[4];
        matrix[5]+=other.matrix[5];
        matrix[6]+=other.matrix[6];
        matrix[7]+=other.matrix[7];
        matrix[8]+=other.matrix[8];
        matrix[9]+=other.matrix[9];
        matrix[10]+=other.matrix[10];
        matrix[11]+=other.matrix[11];
        matrix[12]+=other.matrix[12];
        matrix[13]+=other.matrix[13];
        matrix[14]+=other.matrix[14];
        matrix[15]+=other.matrix[15];

        return *this;
    }

    inline matrix4_t<T> operator- (const matrix4_t<T>& other) const
    {
        matrix4_t<T> temp;
        temp.matrix[0]  = matrix[0]-other.matrix[0];
        temp.matrix[1]  = matrix[1]-other.matrix[1];
        temp.matrix[2]  = matrix[2]-other.matrix[2];
        temp.matrix[3]  = matrix[3]-other.matrix[3];
        temp.matrix[4]  = matrix[4]-other.matrix[4];
        temp.matrix[5]  = matrix[5]-other.matrix[5];
        temp.matrix[6]  = matrix[6]-other.matrix[6];
        temp.matrix[7]  = matrix[7]-other.matrix[7];
        temp.matrix[8]  = matrix[8]-other.matrix[8];
        temp.matrix[9]  = matrix[9]-other.matrix[9];
        temp.matrix[10] = matrix[10]-other.matrix[10];
        temp.matrix[11] = matrix[11]-other.matrix[11];
        temp.matrix[12] = matrix[12]-other.matrix[12];
        temp.matrix[13] = matrix[13]-other.matrix[13];
        temp.matrix[14] = matrix[14]-other.matrix[14];
        temp.matrix[15] = matrix[15]-other.matrix[15];
        return temp;
    }

    inline matrix4_t<T>& operator-= (const matrix4_t<T>& other)
    {
        matrix[0]-=other.matrix[0];
        matrix[1]-=other.matrix[1];
        matrix[2]-=other.matrix[2];
        matrix[3]-=other.matrix[3];
        matrix[4]-=other.matrix[4];
        matrix[5]-=other.matrix[5];
        matrix[6]-=other.matrix[6];
        matrix[7]-=other.matrix[7];
        matrix[8]-=other.matrix[8];
        matrix[9]-=other.matrix[9];
        matrix[10]-=other.matrix[10];
        matrix[11]-=other.matrix[11];
        matrix[12]-=other.matrix[12];
        matrix[13]-=other.matrix[13];
        matrix[14]-=other.matrix[14];
        matrix[15]-=other.matrix[15];

        return *this;
    }

    inline matrix4_t<T> operator* (T val) const
    {
        matrix4_t<T> temp;
        temp.matrix[0]=matrix[0]*val;
        temp.matrix[1]=matrix[1]*val;
        temp.matrix[2]=matrix[2]*val;
        temp.matrix[3]=matrix[3]*val;
        temp.matrix[4]=matrix[4]*val;
        temp.matrix[5]=matrix[5]*val;
        temp.matrix[6]=matrix[6]*val;
        temp.matrix[7]=matrix[7]*val;
        temp.matrix[8]=matrix[8]*val;
        temp.matrix[9]=matrix[9]*val;
        temp.matrix[10]=matrix[10]*val;
        temp.matrix[11]=matrix[11]*val;
        temp.matrix[12]=matrix[12]*val;
        temp.matrix[13]=matrix[13]*val;
        temp.matrix[14]=matrix[14]*val;
        temp.matrix[15]=matrix[15]*val;

        return *this;
    }

    inline matrix4_t<T>& operator *= (T val)
    {

        matrix[0]*=val;
        matrix[1]*=val;
        matrix[2]*=val;
        matrix[3]*=val;
        matrix[4]*=val;
        matrix[5]*=val;
        matrix[6]*=val;
        matrix[7]*=val;
        matrix[8]*=val;
        matrix[9]*=val;
        matrix[10]*=val;
        matrix[11]*=val;
        matrix[12]*=val;
        matrix[13]*=val;
        matrix[14]*=val;
        matrix[15]*=val;

        return *this;
    }

    inline matrix4_t<T> operator*(const matrix4_t<T> &other)
    {
        matrix4_t result;
        result = multiply(*this,other);
        return result;
    }

    inline matrix4_t<T>& operator*= (const matrix4_t<T> &other)
    {
        *this = multiply(*this,other);
        return *this;
    }

    inline matrix4_t<T>& buildOrthographicProjectionMatrix(f32 left,f32 right,f32 bottom,f32 top,f32 znear,f32 zfar)
    {
        makeIndetify();
        matrix[0]  = (T)  2 / (right - left);
        matrix[5]  = (T)  2 / (top - bottom);
        matrix[10] = (T) -2 / (zfar - znear);
        matrix[12] = (T) -((right + left) / (right - left));
        matrix[13] = (T) -((top + bottom) / (top - bottom));
        matrix[14] = (T) -((zfar + znear) / (zfar - znear));
        matrix[15] = 1;
        return *this;
    }

    inline matrix4_t<T>& buildPerspectiveProjectionMatrix(f32 fov,f32 aspect,f32 znear,f32 zfar)
    {
        makeIndetify();
        float right,left,top,bottom;
        float temp, temp2, temp3, temp4;

        top = znear * tanf(fov * PI / 360.0);
        bottom = -top;
        right = top * aspect;
        left = -right;

        temp =  2.0 * znear;
        temp2 = right - left;

        temp3 = -(top - bottom);
        temp4 = zfar - znear;



        matrix[0] = temp / temp2;
        matrix[5] = temp / temp3;
        matrix[8] = (right + left) / temp2;
        matrix[9] = (top + bottom) / temp3;
        matrix[10] = (-zfar - znear) / temp4;
        matrix[11] = -1.0;
        matrix[14] = (-temp * zfar) / temp4;
        matrix[15] = 0.0;

        return *this;
    }

    inline matrix4_t<T>& buildLookAtMatrix(vector3d_t<T> Position,vector3d_t<T> Target,vector3d_t<T> UpVector)
    {
            /*
             zaxis = normal(At - Eye)
             xaxis = normal(cross(Up, zaxis))
             yaxis = cross(zaxis, xaxis)

             xaxis.x           yaxis.x           zaxis.x          0
             xaxis.y           yaxis.y           zaxis.y          0
             xaxis.z           yaxis.z           zaxis.z          0
            -dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  l
            */
        //! Temp fix
            if(Position == Target)
            {
                Target.z--;
            }
        //! --------
        makeIndetify();

        vector3d_t<T> XAxis,YAxis,ZAxis;

        ZAxis = Position-Target;
        ZAxis.normalize();
        XAxis = UpVector.cross_Product(ZAxis);
        XAxis.normalize();
        YAxis = XAxis.cross_Product(ZAxis);

        matrix[0]  = (T)XAxis.x;
		matrix[1]  = (T)YAxis.x;
		matrix[2]  = (T)ZAxis.x;
		matrix[3]  = 0;

		matrix[4]  = (T)XAxis.y;
		matrix[5]  = (T)YAxis.y;
		matrix[6]  = (T)ZAxis.y;
		matrix[7]  = 0;

		matrix[8]  = (T)XAxis.z;
		matrix[9]  = (T)YAxis.z;
		matrix[10] = (T)ZAxis.z;
		matrix[11] = 0;

		matrix[12] = (T)-XAxis.dot_Product(Position);
		matrix[13] = (T)-YAxis.dot_Product(Position);
		matrix[14] = (T)-ZAxis.dot_Product(Position);
		matrix[15] = 1;

        return *this;
    }


    inline matrix4_t<T>& transpose()
    {
        matrix4_t result;

        result.matrix[1] = matrix[4];
        result.matrix[2] = matrix[8];
        result.matrix[3] = matrix[12];
        result.matrix[7] = matrix[13];
        result.matrix[11] = matrix[14];
        result.matrix[9] = matrix[6];

        result.matrix[4] = matrix[1];
        result.matrix[8] = matrix[2];
        result.matrix[12] = matrix[3];
        result.matrix[13] = matrix[7];
        result.matrix[14] = matrix[11];
        result.matrix[6] = matrix[9];

        matrix = result.matrix;
        return *this;
    }

    inline matrix4_t<T>& setTranslate(vector2d_t<T> vec)
    {
        matrix[12] = vec.x;
        matrix[13] = vec.y;
    }

    inline matrix4_t<T>& setRotationDegrees(vector2d_t<T> rotation)
    {
        rotation *= DEGTORAD;
        vector3d_t<T> vec3d = vector3df(rotation.x,rotation.y,0);
        setRotationRadians(vec3d);
    }

    inline void setScale(vector2d_t<T> scale)
    {

        matrix4_t<T> sm;
        sm.matrix[0]  = (T)scale.x;
        sm.matrix[5]  = (T)scale.y;
        *this = multiply(*this,sm);
    }

    inline void rotateVector(vector2d_t<T>& vect)
    {
        vector2d_t<T> tmp = vect;
        vect.x = -(tmp.x*matrix[0] + tmp.y*matrix[1]);
        vect.y =   tmp.x*matrix[4] + tmp.y*matrix[5];
    }

    inline void translateVector(vector2d_t<T>& vect)
    {
        vect.x += matrix[3];
        vect.y += matrix[7];
    }

    inline void transformVector(vector2d_t<T>& vect)
    {
        T vector[2];

        vector[0] = vect.x*matrix[0] + vect.y*matrix[4] + matrix[12];
        vector[1] = vect.x*matrix[1] + vect.y*matrix[5] + matrix[13];

        vect.x = vector[0];
        vect.y = vector[1];
    }

    inline void setTranslate(vector3d_t<T> vec)
    {
        matrix[12] = vec.x;
        matrix[13] = vec.y;
        matrix[14] = vec.z;
    }

    inline void setRotationDegrees(vector3d_t<T> rotation)
    {
        setRotationRadians(rotation * DEGTORAD);
    }

    inline void setRotationRadians(vector3d_t<T> rotation)
    {
        const f64 cr = cos(rotation.x);
        const f64 sr = sin(rotation.x);
        const f64 cp = cos(rotation.y);
        const f64 sp = sin(rotation.y);
        const f64 cy = cos(rotation.z);
        const f64 sy = sin(rotation.z);

        matrix[0] = (T)(cp*cy);
        matrix[4] = (T)(cp*sy);
        matrix[8] = (T)(-sp);

        const f64 srsp = sr*sp;
        const f64 crsp = cr*sp;

        matrix[1] = (T)(srsp*cy-cr*sy);
        matrix[5] = (T)(srsp*sy+cr*cy);
        matrix[9] = (T)(sr*cp);

        matrix[2] = (T)(crsp*cy+sr*sy);
        matrix[6] = (T)(crsp*sy-sr*cy);
        matrix[10] = (T)(cr*cp);
    }

    inline void setScale(vector3d_t<T> scale)
    {

        matrix4_t<T> sm;
        sm.matrix[0]  = (T)scale.x;
        sm.matrix[5]  = (T)scale.y;
        sm.matrix[10] = (T)scale.z;
        *this = multiply(*this,sm);
    }

    inline void rotateVector(vector3d_t<T>& vect)
    {
        vector3d_t<T> tmp = vect;
        vect.x = -(tmp.x*matrix[0] + tmp.y*matrix[1] + tmp.z*matrix[2]);
        vect.y =   tmp.x*matrix[4] + tmp.y*matrix[5] + tmp.z*matrix[6];
        vect.z =   tmp.x*matrix[8] + tmp.y*matrix[9] + tmp.z*matrix[10];
    }

    inline void translateVector(vector3d_t<T>& vect)
    {
        vect.x += matrix[3];
        vect.y += matrix[7];
        vect.z += matrix[11];
    }

    inline void transformVector(vector3d_t<T>& vect)
    {
        T vector[3];

        vector[0] = vect.x*matrix[0] + vect.y*matrix[4] + vect.z*matrix[8] + matrix[12];
        vector[1] = vect.x*matrix[1] + vect.y*matrix[5] + vect.z*matrix[9] + matrix[13];
        vector[2] = vect.x*matrix[2] + vect.y*matrix[6] + vect.z*matrix[10] + matrix[14];

        vect.x = vector[0];
        vect.y = vector[1];
        vect.z = vector[2];
    }

    T* getPointer()
    {
        return matrix;
    }



protected:
private:

    inline matrix4_t<T> multiply(const matrix4_t<T>& mtx1,const matrix4_t<T>& mtx2)
    {
        matrix4_t mtx3;

        T *m1 = mtx1.matrix;
        T *m2 = mtx2.matrix;
        T *m3 = mtx3.matrix;


        m3[0]  = m1[0]*m2[0]  + m1[4]*m2[1]  + m1[8]*m2[2]  + m1[12]*m2[3];
        m3[4]  = m1[0]*m2[4]  + m1[4]*m2[5]  + m1[8]*m2[6]  + m1[12]*m2[7];
        m3[8]  = m1[0]*m2[8]  + m1[4]*m2[9]  + m1[8]*m2[10] + m1[12]*m2[11];
        m3[12] = m1[0]*m2[12] + m1[4]*m2[13] + m1[8]*m2[14] + m1[12]*m2[15];

        m3[1]  = m1[1]*m2[0]  + m1[5]*m2[1]  + m1[9]*m2[2]   + m1[13]*m2[3];
        m3[5]  = m1[1]*m2[4]  + m1[5]*m2[5]  + m1[9]*m2[6]   + m1[13]*m2[7];
        m3[9]  = m1[1]*m2[8]  + m1[5]*m2[9]  + m1[9]*m2[10]  + m1[13]*m2[11];
        m3[13] = m1[1]*m2[12] + m1[5]*m2[13] + m1[9]*m2[14]  + m1[13]*m2[15];

        m3[2]  = m1[2]*m2[0]  + m1[6]*m2[1]  + m1[10]*m2[2]  + m1[14]*m2[3];
        m3[6]  = m1[2]*m2[4]  + m1[6]*m2[5]  + m1[10]*m2[6]  + m1[14]*m2[7];
        m3[10] = m1[2]*m2[8]  + m1[6]*m2[9]  + m1[10]*m2[10] + m1[14]*m2[11];
        m3[14] = m1[2]*m2[12] + m1[6]*m2[13] + m1[10]*m2[14] + m1[14]*m2[15];

        m3[3]  = m1[3]*m2[0]  + m1[7]*m2[1]  + m1[11]*m2[2]  + m1[15]*m2[3];
        m3[7]  = m1[3]*m2[4]  + m1[7]*m2[5]  + m1[11]*m2[6]  + m1[15]*m2[7];
        m3[11] = m1[3]*m2[8]  + m1[7]*m2[9]  + m1[11]*m2[10] + m1[15]*m2[11];
        m3[15] = m1[3]*m2[12] + m1[7]*m2[13] + m1[11]*m2[14] + m1[15]*m2[15];
        mtx3.matrix = m3;
        return mtx3;
    }

    T* matrix;
};
}
}
#endif // MATRIX4_T_H
