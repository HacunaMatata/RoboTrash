#ifndef AABBOX_H
#define AABBOX_H

#include "Types.h"

namespace novaengine
{
namespace core
{
class aabbox3d
{
public:
    aabbox3d()
    {
        min_Point = vector3df(0,0,0);
        max_Point = vector3df(0,0,0);
        Empty = true;
    }
    virtual ~aabbox3d()
    {}



    vector3df getCenter()
    {
        return (min_Point + max_Point) / 2;
    }

    void addVertex(vector3df vertex)
    {
        if(Empty)
        {
            Empty = false;
            min_Point = vertex;
            max_Point = vertex;
            return;
        }


        if(vertex.x < min_Point.x)
            min_Point.x = vertex.x;
        if(vertex.x > max_Point.x)
            max_Point.x = vertex.x;

        if(vertex.y < min_Point.y)
            min_Point.y = vertex.y;
        if(vertex.y > max_Point.y)
            max_Point.y = vertex.y;

        if(vertex.z < min_Point.z)
            min_Point.z = vertex.z;
        if(vertex.z > max_Point.z)
            max_Point.z = vertex.z;
    }

    void addVerticles(vector3df *verticles,u32 vertexcount)
    {
        for(u32 c = 0; c < vertexcount; c++)
            addVertex(verticles[c]);
    }


    void reset()
    {
        Empty = true;
        min_Point = 0;
        max_Point = 0;
    }

    //--------------------------
    vector3df* getBoundaryPoints(core::vector3df translation = vector3df(0,0,0))
    {
        vector3df *Vertex = new vector3df[8];

        vector3df middle = getCenter();
        vector3df diag   = middle - max_Point;

        Vertex[0] = core::vector3df(middle.x + diag.x, middle.y + diag.y, middle.z + diag.z) + translation;
        Vertex[1] = core::vector3df(middle.x + diag.x, middle.y - diag.y, middle.z + diag.z) + translation;
        Vertex[2] = core::vector3df(middle.x + diag.x, middle.y + diag.y, middle.z - diag.z) + translation;
        Vertex[3] = core::vector3df(middle.x + diag.x, middle.y - diag.y, middle.z - diag.z) + translation;
        Vertex[4] = core::vector3df(middle.x - diag.x, middle.y + diag.y, middle.z + diag.z) + translation;
        Vertex[5] = core::vector3df(middle.x - diag.x, middle.y - diag.y, middle.z + diag.z) + translation;
        Vertex[6] = core::vector3df(middle.x - diag.x, middle.y + diag.y, middle.z - diag.z) + translation;
        Vertex[7] = core::vector3df(middle.x - diag.x, middle.y - diag.y, middle.z - diag.z) + translation;

        return Vertex;
    }
    //-------intersects
    bool intersectsWithBox(const aabbox3d& other) const
    {
        return (min_Point.x <= other.max_Point.x && min_Point.y <= other.max_Point.y && min_Point.z <= other.max_Point.z &&
                max_Point.x >= other.min_Point.x && max_Point.y >= other.min_Point.y && max_Point.z >= other.min_Point.z);
    }
private:

    vector3df min_Point;
    vector3df max_Point;
    bool Empty;
};

}
}


#endif // AABBOX_H
