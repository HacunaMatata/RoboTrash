#ifndef CSCENE_H
#define CSCENE_H

#include "Types.h"
#include "IScene.h"


#include "ISceneManager.h"
#include "Logger.h"
#include <vector>
#include <algorithm>



namespace novaengine
{
namespace scene
{

//simple sorting
bool sort_back_to_front(ISceneNode* node1,ISceneNode* node2)
{
  return (node1->getPosition().z > node2->getPosition().z);
}
//---------------------------------------------------------
class CScene : public IScene
{
public:
    CScene(ISceneManager* smgr):
        SceneManager(smgr),
        SceneCamera(0)
    {

    }

    ~CScene()
    {
        eraseScene();
    }
    //NodeList
    void RegisterNode(ISceneNode*   SceneNode)
    {
        if(SceneNode == NULL)
            return;

        if(findNode(SceneNode))
            return;

        SceneNode->capture();
        SceneNode_List.push_back(SceneNode);

        SceneNode->RegisterNode(this);


    }
    void UnRegisterNode(ISceneNode* SceneNode)
    {
        if(SceneNode == NULL)
            return;

        u32 ListSize = SceneNode_List.size();
        for(u32 i = 0; i < ListSize; i++)
        {
            if(SceneNode == SceneNode_List[i])
            {
                SceneNode_List[i]->UnRegisterNode();
                SceneNode_List[i]->release();
                SceneNode_List[i] = NULL;
                SceneNode_List.erase(SceneNode_List.begin() + i);
            }
        }
    }
    ISceneNode** getNodeList()
    {
        return &SceneNode_List.front();
    }
    u32  getNodeCount()
    {
        return SceneNode_List.size();
    }
    void eraseScene()
    {
        u32 ListSize = SceneNode_List.size();

        char buf[256];
        sprintf(buf,"Erasing scene[ %u nodes]",ListSize);
        io::Log::println(buf,ELL_DEBUG_ENGINE);

        for(u32 i = 0; i < ListSize; i++)
        {
            // Store node in temp varible and set pointer in null
            // because SceneNode::UnRegisterNode recall Scene::UnRegisterNode
            ISceneNode* Node = SceneNode_List[i];
            SceneNode_List[i] = NULL;

            if(Node == NULL)
                break;

            //Unregister from scene and release node
            Node->UnRegisterNode();
            Node->release();
        }


        SceneNode_List.clear();

        setActiveCamera(NULL);
    }

    ISceneNode* getNodeByID(s32 id)
    {
        u32 ListSize = SceneNode_List.size();

        for(u32 NodeNum = 0; NodeNum < ListSize; NodeNum++)
        {
            if(SceneNode_List[NodeNum]->getNodeID() == id)
                return SceneNode_List[NodeNum];
        }

        return NULL;
    }

    //Camera
    void setActiveCamera(ISceneCamera* Camera)
    {
        if(SceneCamera)
            SceneCamera->release();

        if(Camera)
            Camera->capture();

        SceneCamera = Camera;
    }
    ISceneCamera* getActiveCamera()
    {
        return SceneCamera;
    }
    //ActiveSceene
    void setActive()
    {
        SceneManager->setActiveScene(this);
    }
    bool isActive()
    {
        return (SceneManager->getActiveScene() == this);
    }
    //Render
    void update()
    {
        std::sort (SceneNode_List.begin(),SceneNode_List.end(),sort_back_to_front);

        u32 ListSize = SceneNode_List.size();
        for(int i = 0; i < ListSize; i++)
        {
            SceneNode_List[i]->update();
        }
    }
    void animate()
    {
        u32 ListSize = SceneNode_List.size();
        for(int i = 0; i < ListSize; i++)
        {
            SceneNode_List[i]->animate();
        }
    }
    void render()
    {
        SceneManager->setActiveScene(this);

        if(SceneCamera)
            SceneCamera->render();

        u32 ListSize = SceneNode_List.size();
        for(int i = 0; i < ListSize; i++)
        {
            SceneNode_List[i]->render();
        }
    }

protected:
private:

    bool findNode(ISceneNode* SceneNode)
    {
        u32 ListSize = SceneNode_List.size();

        for(u32 NodeNum = 0; NodeNum < ListSize; NodeNum++)
        {
            if(SceneNode_List[NodeNum] == SceneNode)
                return true;
        }
        return false;
    }


    //SceneManager
    ISceneManager* SceneManager;
    //NodeList
    std::vector<ISceneNode*> SceneNode_List;
    //SceneCamera
    ISceneCamera* SceneCamera;
};

}
}
#endif // CSCENE_H
