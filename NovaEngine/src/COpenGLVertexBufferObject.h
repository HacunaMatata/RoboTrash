#ifndef COPENGLVERTEXBUFFEROBJECT_H
#define COPENGLVERTEXBUFFEROBJECT_H


#include "Types.h"
#include "IVertexBufferObject.h"
#include "IVertexArray.h"

#include "GL/glew.h"

namespace novaengine
{
namespace renderer
{

class COpenGLVertexBufferObject : public IVertexBufferObject
{
public:
    COpenGLVertexBufferObject(IVertexArray* p_vertex_array)
    {
        vbo_id_verticles = 0;
        vbo_id_indices   = 0;
        vao_id           = 0;
        need_rebuild     = false;


        IndexCount    = p_vertex_array->getIndicesCount();
        VertexCount   = p_vertex_array->getVertexCount();

        //!< Preparing VBO
        if(GLEW_ARB_vertex_buffer_object)
        {
            io::Log::println("ARB_vertex_buffer_object avalible.",ELL_DEBUG_ENGINE);

            //!< generate, bind VBO and upload vertex data to them
            glGenBuffers ( 1, &vbo_id_verticles );
            glBindBuffer ( GL_ARRAY_BUFFER_ARB, vbo_id_verticles );
            glBufferData ( GL_ARRAY_BUFFER_ARB, sizeof(SVertex) * VertexCount, p_vertex_array->getVerticles(), GL_STREAM_DRAW );

            //!< generate, bind VBO and upload indices data to them (if array have indices)
            if(IndexCount)
            {
                glGenBuffers ( 1, &vbo_id_indices );
                glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, vbo_id_indices );
                glBufferData ( GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * IndexCount, p_vertex_array->getIndices(), GL_STREAM_DRAW );
            }

            //!< Unbind buffers
            glBindBuffer(GL_ARRAY_BUFFER,0);
            if(IndexCount)
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        }
        //!< Preparing VAO(if it supported)
        if(GLEW_ARB_vertex_array_object)
        {
            io::Log::println("ARB_vertex_array_object avalible.",ELL_DEBUG_ENGINE);

            //!< generate and bind VAO id
            glGenVertexArrays(1,&vao_id);
            glBindVertexArray(vao_id);

            //!< bind VBO vertex id
            glBindBuffer ( GL_ARRAY_BUFFER, vbo_id_verticles );

            //!< setup VAO
            //------------------------------------------------------------
            glEnableClientState(GL_VERTEX_ARRAY         );
            glEnableClientState(GL_TEXTURE_COORD_ARRAY  );
            glEnableClientState(GL_NORMAL_ARRAY         );
            glEnableClientState(GL_COLOR_ARRAY          );
            //------------------------------------------------------------
            glVertexPointer     (3  ,   GL_FLOAT        ,   sizeof(SVertex) ,   (void*)  0  );
            glTexCoordPointer   (2  ,   GL_FLOAT        ,   sizeof(SVertex) ,   (void*) 12  );
            glNormalPointer     (       GL_FLOAT        ,   sizeof(SVertex) ,   (void*) 20  );
            glColorPointer      (4  ,   GL_UNSIGNED_BYTE,   sizeof(SVertex) ,   (void*) 32  );
            //------------------------------------------------------------

            //!< bind VBO indices id(if it need)
            if(IndexCount)
                glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, vbo_id_indices);

            //!< Unbind VAO
            glBindVertexArray(0);
        }

    }
    //----------------------------------------------------------
    virtual ~COpenGLVertexBufferObject()
    {
        if(GLEW_ARB_vertex_array_object)
        {
            glDeleteVertexArrays(1,&vao_id);
        }

        if(GLEW_ARB_vertex_buffer_object)
        {
            glDeleteBuffers(1,&vbo_id_verticles);
            if(!vbo_id_indices)
                glDeleteBuffers(1,&vbo_id_indices);
        }
    }
    //----------------------------------------------------------
    bool isOk()
    {
        if(glIsBuffer(vbo_id_verticles)                            == false)
            return false;
        if(IndexCount && glIsBuffer(vbo_id_indices)                == false)
            return false;
        if(GLEW_ARB_vertex_array_object && glIsVertexArray(vao_id) == false)
            return false;

        return true;
    }
    //----------------------------------------------------------
    void bind_buffer()
    {
        //!< bind VAO, if VAO not supported we bind VBO vertex and VBO indices
        if(GLEW_ARB_vertex_array_object)
        {
            glBindVertexArray(vao_id);
        }
        else if(GLEW_ARB_vertex_buffer_object)
        {
            glBindBuffer(GL_ARRAY_BUFFER,vbo_id_verticles);
            if(!vbo_id_indices)
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vbo_id_indices);
        }
    }
    //----------------------------------------------------------
    void unbind_buffer()
    {
        //!< unbind VAO(or VBO)
        if(GLEW_ARB_vertex_array_object)
        {
            glBindVertexArray(0);
        }
        else if(GLEW_ARB_vertex_buffer_object)
        {
            glBindBuffer(GL_ARRAY_BUFFER,0);
            if(!vbo_id_indices)
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        }
    }
    //----------------------------------------------------------
    void rebuild_buffer(IVertexArray* p_vertex_array)
    {
        io::Log::println("Rebuilding vbo...",ELL_DEEP_DEBUG);

                IndexCount    = p_vertex_array->getIndicesCount();
                VertexCount   = p_vertex_array->getVertexCount();

                glBindBuffer(GL_ARRAY_BUFFER,vbo_id_verticles);
                glBufferData ( GL_ARRAY_BUFFER_ARB, sizeof(SVertex) * VertexCount, p_vertex_array->getVerticles(), GL_STREAM_DRAW );
                glBindBuffer(GL_ARRAY_BUFFER,0);

                if(IndexCount)
                {
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vbo_id_indices);
                    glBufferData ( GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * IndexCount, p_vertex_array->getIndices(), GL_STREAM_DRAW );
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
                }

        need_rebuild = false;
    }
    //----------------------------------------------------------
    void request_rebuild()
    {
        need_rebuild = true;
    };
    bool required_rebuild()
    {
        return need_rebuild;
    };

    u32 vbo_id_verticles;
    u32 vbo_id_indices;
    u32 vao_id;
    bool need_rebuild;

protected:
private:


    u32              IndexCount;
    u32              VertexCount;
};

}
}
#endif // COPENGLVERTEXBUFFEROBJECT_H
