
#ifndef CVertexArray_H
#define CVertexArray_H

#include "IVertexArray.h"

namespace novaengine
{
namespace renderer
{

class CVertexArray : public IVertexArray
{
public:
    CVertexArray()
    {
        VertexFormat  = EVF_VERTEX;
        PrimitiveType = EPT_TRIANGLES;
        ArrayType    = EVAT_UNDEFINDED;
        vbo           = NULL;
    }
    CVertexArray(SVertex* vert,u32 VertexCount,E_PRIMITIVE_TYPE PrimitiveType_,u32 VertexFormat_)
    {
        VertexFormat  = VertexFormat_;
        PrimitiveType = PrimitiveType_;
        ArrayType    = EVAT_RAWDATA;
        vbo           = NULL;

        addVerticles(vert,VertexCount);
    }

    ~CVertexArray()
    {
        if(vbo)
            vbo->release();
    }
    virtual void* getVerticles()
    {
        return &Verticles.front();//return pointer on the first array element
    }
    virtual u32*  getIndices()
    {
        if(Indices.size() == 0)
            return NULL;
        else
            return &Indices.front();
    }

    SVertex* getVertex(u32 index)
    {
        return &Verticles[index];
    }
    const u32 getVertexCount()
    {
        return Verticles.size();
    }
    virtual const u32 getIndicesCount()
    {
        return Indices.size();
    }

    const u32 getVertexFormat()
    {
        return VertexFormat;
    }
    void setVertexFormat(u32 vt)
    {
        VertexFormat = vt;
    }

    const E_PRIMITIVE_TYPE getPrimitiveType()
    {
        return PrimitiveType;
    }
    void setPrimitiveType(E_PRIMITIVE_TYPE pt)
    {
        PrimitiveType = pt;
    }


    void addVertex(SVertex vert)
    {
        Verticles.push_back(vert);
        if(vbo)
            vbo->request_rebuild();
    }
    void addVerticles(SVertex* OtherVerticles,u32 VerticlesCount)
    {
        Verticles.insert(Verticles.end(),OtherVerticles,OtherVerticles+VerticlesCount);
        if(vbo)
            vbo->request_rebuild();
    }
    void addVerticles(SVertex* OtherVerticles,u32 VerticlesCount,core::vector3df Offset)
    {
        Verticles.insert(Verticles.end(),OtherVerticles,OtherVerticles+VerticlesCount);

        u32 size = Verticles.size();
        for(u32 i = size - VerticlesCount;i < size;i++)
            moveVertex(Offset,i);

        if(vbo)
            vbo->request_rebuild();
    }
    void addVertexArray(IVertexArray* otherBuffer)
    {
        Verticles.insert(Verticles.end(),reinterpret_cast<SVertex*>(otherBuffer->getVerticles()),reinterpret_cast<SVertex*>(otherBuffer->getVerticles())+otherBuffer->getVertexCount());
        if(vbo)
            vbo->request_rebuild();
    }
    void addVertexArray(IVertexArray* otherBuffer,core::vector3df Offset)
    {
        Verticles.insert(Verticles.end(),reinterpret_cast<SVertex*>(otherBuffer->getVerticles()),reinterpret_cast<SVertex*>(otherBuffer->getVerticles())+otherBuffer->getVertexCount());

        u32 other_size  = otherBuffer->getVertexCount();
        u32 size        = Verticles.size();

        for(u32 i = size - other_size;i < size;i++)
            moveVertex(Offset,i);

        if(vbo)
            vbo->request_rebuild();
    }
    void setIndices(u32* indices_list,u32 indices_count)
    {
        if(indices_list != NULL)
        {
            Indices.clear();
            Indices.insert(Indices.begin(),indices_list,indices_list+indices_count);
        }
        else
        {
            Indices.clear();
        }
        if(vbo)
            vbo->request_rebuild();
    }

    void moveVertex(core::vector3df dir,u32 index)
    {
        Verticles[index].Position += dir;
        if(vbo)
            vbo->request_rebuild();
    }

    void moveVerticles(core::vector3df dir)
    {
        int size = Verticles.size();
        for(int i = 0; i < size; i++)
        {
            Verticles[i].Position += dir;
        }
        if(vbo)
            vbo->request_rebuild();
    }

    void clear_vertex_array()
    {
        Verticles.clear();
    }

    void reserve_vertex_space(u32 verticles_count)
    {
        Verticles.reserve(verticles_count);
    }

    void setArrayType(E_VERTEX_ARRAY_TYPE type)
    {
            ArrayType = type;
    }
    u32  getArrayType()
    {
        return ArrayType;
    }


    virtual renderer::IVertexBufferObject* get_vbo_pointer()
    {
        return vbo;
    };
    virtual void   set_vbo_pointer(renderer::IVertexBufferObject* p_vbo)
    {
        if(p_vbo != NULL)
        {
            vbo = p_vbo;
            ArrayType = EVAT_VBO;
        }
        else
        {
            if(vbo)
                vbo->anihilate();

            vbo = NULL;
            ArrayType = EVAT_RAWDATA;
        }
    };

protected:
    std::vector<SVertex>    Verticles;
    std::vector<u32>        Indices;

    u32                     VertexFormat;
    E_PRIMITIVE_TYPE        PrimitiveType;


    E_VERTEX_ARRAY_TYPE             ArrayType;
    renderer::IVertexBufferObject*   vbo;     //VBO pointer if ArrayType != EVAT_RAWDATA
};

}
}
#endif // CVertexArray_H
