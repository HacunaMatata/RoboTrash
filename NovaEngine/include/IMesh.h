#ifndef IMESH_H
#define IMESH_H

#include "Object.h"
#include "IVertexArray.h"
#include "IMaterial.h"

namespace novaengine
{
namespace scene
{

class IMesh : public Object
{
    public:

        virtual void addVertexArray(renderer::IVertexArray* vertexarray) = 0;
        virtual void remVertexArray(u32 index)                 = 0;
        virtual u32  getVertexBufferCount()                    = 0;
        virtual renderer::IVertexArray*  getVertexArray(u32 index)       = 0;
        virtual renderer::IVertexArray** getVertexArrayList()            = 0;

        virtual void       setMaterial(renderer::IMaterial* material) = 0;
        virtual renderer::IMaterial* getMaterial() = 0;

    protected:
    private:
};

}
}
#endif // IMESH_H
