#ifndef COLOR4_T_H
#define COLOR4_T_H



namespace novaengine
{
namespace core
{

template <class T>
class color4_t
{
public:
    color4_t()
    {
        Red = 255;
        Green = 255;
        Blue = 255;
        Alpha = 255;
    }
    color4_t(T Red_,T Green_,T Blue_,T Alpha_)
    {
        Red = Red_;
        Green = Green_;
        Blue = Blue_;
        Alpha = Alpha_;
    }


    color4_t operator= (const color4_t &other)
    {
        Red = other.Red;
        Green = other.Green;
        Blue = other.Blue;
        Alpha = other.Alpha;
        return *this;
    }

    color4_t invert()
    {
        Red   = 255 - Red;
        Green = 255 - Green;
        Blue  = 255 - Blue;
        Alpha = 255 - Alpha;
    }

    T Red;
    T Green;
    T Blue;
    T Alpha;

};


}
}

#endif // COLOR4_T_H
