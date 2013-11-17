#ifndef IVERTEXARRAY_H
#define IVERTEXARRAY_H



#include "Types.h"
#include "Object.h"


#include "SVertex.h"
#include "ERendererEnums.h"
#include "IVertexBufferObject.h"
#include "IMaterial.h"

#include "aabbox3d.h"



namespace novaengine
{
namespace renderer
{


class IVertexArray : public Object
{
public:

    virtual void* getVerticles() = 0;
    virtual u32*  getIndices()   = 0;

    virtual SVertex* getVertex(u32 index) = 0;

    virtual const u32 getVertexCount()  = 0;
    virtual const u32 getIndicesCount() = 0;

    virtual const u32 getVertexFormat() = 0;
    virtual void setVertexFormat(u32)   = 0;

    virtual const E_PRIMITIVE_TYPE getPrimitiveType() = 0;
    virtual void setPrimitiveType(E_PRIMITIVE_TYPE)   = 0;

    virtual void addVertex(SVertex vert) = 0;
    virtual void addVerticles(SVertex* other_verticles,u32 verticles_count) = 0;
    virtual void addVerticles(SVertex* other_verticles,u32 verticles_count,core::vector3df offset) = 0;
    virtual void addVertexArray(IVertexArray* other_VertexArray) = 0;
    virtual void addVertexArray(IVertexArray* other_VertexArray,core::vector3df offset) = 0;
    virtual void setIndices(u32* indices_list,u32 indices_count) = 0;

    virtual void moveVertex(core::vector3df dir,u32 index) = 0;
    virtual void moveVerticles(core::vector3df dir) = 0;

    virtual void clear_vertex_array() = 0;
    virtual void reserve_vertex_space(u32 verticles_count) = 0;

    virtual void setArrayType(E_VERTEX_ARRAY_TYPE type) = 0;
    virtual u32  getArrayType() = 0;

    //Temp vbo section
    virtual renderer::IVertexBufferObject* get_vbo_pointer()           = 0;
    virtual void   set_vbo_pointer(renderer::IVertexBufferObject* vbo) = 0;
};

}
}

#endif // IVertexArray_H

/*

public:

    virtual void* getVerticles()
    {
         //return pointer on the first array element
        return &Verticles[0];
    }
    virtual SVertex* getVertex(u32 index)
    {
        return &Verticles[index];
    }
    virtual const u32 getVertexCount()
    {
        return Verticles.size();
    }
    //append vertex to buffer
    virtual void addVertex(SVertex vert)
    {
        // One vertex
        Verticles.push_back(vert);
    }
    virtual void addVerticles(SVertex* OtherVerticles,u32 VerticlesCount)
    {
        //Array of verticles
        Verticles.insert(Verticles.end(),OtherVerticles,OtherVerticles+VerticlesCount);
    }
    virtual void addVertexArray(IVertexArray otherBuffer)
    {
        //other buffer
        Verticles.insert(Verticles.end(),otherBuffer.Verticles.begin(),otherBuffer.Verticles.end());
    }

    virtual void moveVertex(core::vector3df dir,u32 index)
    {
        Verticles[index].Position += dir;
    }
    virtual void moveVerticles(core::vector3df dir)
    {
        int size = Verticles.size();
        for(int i = 0; i < size; i++)
        {
            Verticles[i].Position += dir;
        }
    }

protected:
private:
    std::vector<SVertex> Verticles;


*/
