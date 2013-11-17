#ifndef CSCENEMESH_H
#define CSCENEMESH_H

#include "Object.h"
#include "Types.h"
#include "IVertexBuffer.h"
#include "ISceneMesh.h"

#include <vector>

namespace novaengine
{
namespace scene
{

class CSceneMesh : public ISceneNode()
{
    public:
        CSceneMesh(ISceneManager* smgr,renderer::IMesh* mesh = 0,ISceneNode* parent = 0,s32 ID = -1,core::vector3df position = core::vector3df(0,0,0),core::vector3df rotation= core::vector3df(0,0,0),core::vector3df scale= core::vector3df(1,1,1)):
        CSceneNode(smgr,parent,ID,position,rotation,scale),
        Mesh(0)
        {

        }
        virtual ~ISceneMesh()
        {

        }

        virtual void setMesh(renderer::IMesh* mesh)
        {

        }
        virtual renderer::IMesh* getMesh()
        {

        }

    protected:
    private:


};

}

}
#endif // ISCENEMESH_H
