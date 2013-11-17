#ifndef ISCENEMESH_H
#define ISCENEMESH_H

#include "Object.h"
#include "Types.h"
#include "IVertexBuffer.h"
#include "ISceneNode.h"

namespace novaengine
{
namespace scene
{

class ISceneMesh : public ISceneNode()
{
    public:
        ISceneMesh(ISceneManager* smgr,renderer::IMesh* mesh = 0,ISceneNode* parent = 0,s32 ID = -1,core::vector3df position = core::vector3df(0,0,0),core::vector3df rotation= core::vector3df(0,0,0),core::vector3df scale= core::vector3df(1,1,1)):
        ISceneNode(smgr,parent,ID,position,rotation,scale){}
        virtual ~ISceneMesh() {}

        virtual void setMesh(renderer::IMesh* mesh) = 0;

        virtual renderer::IMesh* getMesh() = 0;


    protected:
    private:
};

}

}
#endif // ISCENEMESH_H
