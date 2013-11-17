#ifndef CGUILayout_H
#define CGUILayout_H

#include "Types.h"

#include "IGUIManager.h"
#include "IGUILayout.h"

#include "Logger.h"
#include <vector>
#include <algorithm>

namespace novaengine
{
namespace gui
{
//simple sorting
bool sort_back_to_front(IGUINode* node1,IGUINode* node2)
{
  return (node1->getZLay() > node2->getZLay());
}
//---------------------------------------------------------
class CGUILayout : public IGUILayout
{

public:
    CGUILayout(IGUIManager* guimgr)
    {
        GUIManager = guimgr;
    }

    virtual ~CGUILayout()
    {
        eraseLayout();
    }

    virtual bool OnEvent(SEvent event)
    {
        u32 ListSize = GUINode_List.size();

        for(u32 i = 0; i < ListSize; i++)
        {
            GUINode_List[i]->OnEvent(event);
        }
    }
    //NodeList
    virtual void addNode(IGUINode* GUINode)
    {
        if(GUINode == NULL)
            return;

        GUINode->capture();
        GUINode_List.push_back(GUINode);
    }
    virtual void removeNode(IGUINode* GUINode)
    {
        if(GUINode == NULL)
            return;

        u32 ListSize = GUINode_List.size();


        for(u32 i = 0; i < ListSize; i++)
        {
            if(GUINode == GUINode_List[i])
            {
                GUINode_List[i]->UnRegisterNode();
                GUINode_List[i]->release();
                GUINode_List[i] = NULL;
                GUINode_List.erase(GUINode_List.begin() + i);
            }
        }
    }

    virtual IGUINode** getNodeList()
    {
        return &GUINode_List.front();
    }
    virtual u32  getNodeCount()
    {
        return GUINode_List.size();
    }
    virtual void eraseLayout()
    {
        u32 ListSize = GUINode_List.size();

        char buf[256];
        sprintf(buf,"Erasing GUILayout(%d)[ %d nodes]",0,ListSize);
        io::Log::println(buf,ELL_DEBUG_ENGINE);

        for(u32 i = 0;i < ListSize;i++)
        {

            //Store node in temp varible and set pointer in null because UnRegisterNode recall removeNode they change listsize
            IGUINode* Node = GUINode_List[i];
            GUINode_List[i] = NULL;

            if(Node == NULL)
                break;
            //Unregister from scene and release node
            Node->UnRegisterNode();
            Node->release();


        }
        GUINode_List.clear();


    }

    virtual IGUINode* getNodeByID(s32 id)
    {
        u32 ListSize = GUINode_List.size();

        for(u32 NodeNum = 0; NodeNum < ListSize; NodeNum++)
        {
            IGUINode* SNode = GUINode_List[NodeNum];
            if(SNode->getNodeID() == id)
                return SNode;
        }

        return NULL;
    }
    //ActiveSceene
    virtual void setActive()
    {
        GUIManager->setActiveLayout(this);
    }
    virtual bool isActive()
    {
        return (GUIManager->getActiveLayout() == this);
    }
    //Render
    virtual void update()
    {
        std::sort(GUINode_List.begin(),GUINode_List.end(),sort_back_to_front);
    }
    virtual void animate()
    {}
    virtual void render()
    {
        GUIManager->setActiveLayout(this);


        u32 ListSize = GUINode_List.size();
        for(int i = 0; i < ListSize; i++)
        {
            GUINode_List[i]->render();
        }
    }

protected:
private:
    //GUIManager
    IGUIManager* GUIManager;
    //NodeList
    std::vector<IGUINode*> GUINode_List;

};

}
}
#endif // CGUILayout_H
