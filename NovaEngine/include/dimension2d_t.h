#ifndef DIMENSION2D_T_H
#define DIMENSION2D_T_H

namespace novaengine
{

namespace core
{

template< class T >
class dimension2d_t
{
public:
    dimension2d_t()
    {
        width  = 0;
        height = 0;
    }
    dimension2d_t(T width_,T height_)
    {
        width  = width_;
        height = height_;
    }

    dimension2d_t<T> operator*(const dimension2d_t<T> &other)
    {
        dimension2d_t<T> result;
        result.width = width * other.width;
        result.height = height * other.height;
        return result;
    }

    dimension2d_t<T> operator*=(const dimension2d_t<T> &other)
    {
        dimension2d_t<T> result;
        width *= other.width;
        height *= other.height;
    }

    bool operator == (const dimension2d_t<T> &other ) const
    {
        return width == other.width && height == other.height ;
    }

    bool operator != (const dimension2d_t<T> &other ) const
    {
        return width != other.width && height != other.height ;
    }

    T getArea()
    {
        return (width * height);
    }

    T width;
    T height;
};


}

}


#endif // dimension2d_t_H
