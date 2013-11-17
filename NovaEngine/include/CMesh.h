#ifndef CMESH_H
#define CMESH_H

#include "Types.h"
#include "IMesh.h"
#include "IVertexArray.h"
#include "IMaterial.h"

namespace novaengine
{
namespace scene
{

class CMesh : public IMesh
{
public:
    CMesh():
MeshMaterial(0)
	{}
    virtual ~CMesh() {}

        virtual void addVertexArray(renderer::IVertexArray* vertexarray)
        {
            if(vertexarray)
                vertexarray->capture();
            MeshVertexArrays.push_back(vertexarray);
        }
        virtual void remVertexArray(u32 index)
        {
            if(index >= MeshVertexArrays.size())
                return;
            MeshVertexArrays[index]->release();
            MeshVertexArrays.erase(MeshVertexArrays.begin() + index);
        }
        virtual u32  getVertexBufferCount()
        {
            return MeshVertexArrays.size();
        }
        virtual renderer::IVertexArray*  getVertexArray(u32 index)
        {
            if(index >= MeshVertexArrays.size())
                return NULL;

            return MeshVertexArrays[index];
        }

        virtual renderer::IVertexArray** getVertexArrayList()
        {
            if(MeshVertexArrays.size() == 0)
                return NULL;

            return &MeshVertexArrays.front();
        }

        virtual void setMaterial(renderer::IMaterial* material)
        {
                if(material)
                    material->capture();
                if(MeshMaterial)
                    MeshMaterial->release();

                MeshMaterial = material;
        }

        virtual renderer::IMaterial* getMaterial()
        {
            return MeshMaterial;
        }

protected:
private:

    std::vector<renderer::IVertexArray*> MeshVertexArrays;
    renderer::IMaterial* MeshMaterial;
};

}
}
#endif // CMESH_H
