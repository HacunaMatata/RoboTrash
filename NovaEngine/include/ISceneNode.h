#ifndef ISCENENODE_H
#define ISCENENODE_H

#include "Object.h"
#include "Types.h"

#include "ISceneManager.h"

#include "IScene.h"

#include "../src/Logger.h"



namespace novaengine
{
namespace scene
{

//class ISceneManager;

class ISceneNode : public Object
{
public:

    ISceneNode(ISceneManager* smgr,ISceneNode* parent = 0,s32 ID = -1,core::vector3df position = core::vector3df(0,0,0),core::vector3df rotation= core::vector3df(0,0,0),core::vector3df scale= core::vector3df(1,1,1)):
        SceneManager(smgr),
        Position(position),
        Rotation(rotation),
        Scale(scale),
        update_transform(1),
        Scene(0),
        Parent(parent),
        NodeID(ID),
        Visible(true),
        callback_update(NULL),
        callback_animate(NULL),
        callback_render(NULL)
    {

    }

    virtual ~ISceneNode()
    {
        removeAllChilds();
        UnRegisterNode();
    }

    //----------------------------------Position
    virtual void setPosition(core::vector3df v_position)
    {
        Position = v_position;
        update_transform = true;
    }
    virtual core::vector3df getPosition()
    {
        return Position;
    }
    virtual core::vector3df getAbsolutePosition()
    {
        if(Parent)
        {
            return (Position + Parent->getAbsolutePosition());
        }
        return Position;
    }
    //----------------------------------Rotation
    virtual void setRotation(core::vector3df v_rotation)
    {
        Rotation = v_rotation;
        update_transform = true;
    }
    virtual core::vector3df getRotation()
    {
        return Rotation;
    }
    virtual core::vector3df getAbsoluteRotation()
    {
        if(Parent)
            return Rotation + Parent->getAbsoluteRotation();
        return Rotation;
    }
    //----------------------------------Scale
    virtual void setScale(core::vector3df v_scale)
    {
        Scale = v_scale;
        update_transform = true;
    }
    virtual core::vector3df getScale()
    {
        return Scale;
    }
    virtual core::vector3df getAbsoluteScale()
    {
        if(Parent)
            return (Scale + Parent->getAbsoluteScale());
        return Scale;
    }
    //----------------------------------getTransformation
    virtual core::matrix4f getRelativeTransformation()
    {
        if(update_transform)
        {
            RelativeTransformation.makeIndetify();
            RelativeTransformation.setTranslate(Position);
            RelativeTransformation.setRotationDegrees(Rotation);
            RelativeTransformation.setScale(Scale);
            update_transform = false;
        }
        return RelativeTransformation;
    }
    virtual core::matrix4f getAbsoluteTransformation()
    {
        if(Parent)
        {
            return Parent->getAbsoluteTransformation() * getRelativeTransformation();
        }
        return getRelativeTransformation();
    }

    //----------------------------------Rel
    virtual void setParent(ISceneNode* newParent)
    {
        if(newParent)
        {
            if(Parent == newParent)
                return;

            //If parent have another Scene then node change they Scene to parent Scene
            if(newParent->getScene() != Scene)
                RegisterNode(newParent->getScene());

            //If node already have another parent then node must delete from childs list old parent before set new
            if(Parent)
                Parent->removeChild(this);

            Parent = newParent;

            Parent->addChild(this);

            return;
        }
        Parent = NULL;
    }

    virtual ISceneNode* getParent()
    {
        return Parent;
    }
    virtual void addChild(ISceneNode* Child)
    {
        if(Child)
        {
            if(Child->getScene() != Scene)
                Child->RegisterNode(Scene);

            Child->setParent(this);

            Childs.push_back(Child);
            return;

        }
    }
    virtual void removeChild(ISceneNode* Child)
    {
        if(Child)
        {
            u32 ListSize = Childs.size();

            for(u32 i = 0; i < ListSize; i++)
            {
                if(Child == Childs[i])
                {
                    Childs[i]->setParent(NULL);
                    Childs.erase(Childs.begin() + i);
                }
            }
        }
    }
    virtual void removeAllChilds()
    {
        u32 ListSize = Childs.size();

        for(u32 i = 0; i < ListSize; i++)
        {
            Childs[i]->setParent(NULL);
        }
        Childs.clear();
    }
    //----------------------------------NodeID
    virtual void setNodeID(s32 id)
    {
        NodeID = id;
    }
    virtual s32 getNodeID()
    {
        return NodeID;
    }
    //----------------------------------NodeType
    virtual void setNodeType(s32 type)
    {
        NodeType = type;
    }
    virtual s32 getNodeType()
    {
        return NodeType;
    }
    //----------------------------------Visible
    virtual void setVisible(bool _visible)
    {
        Visible = _visible;
    }
    virtual bool isVisible()
    {
        return Visible;
    }
    //----------------------------------Registring node
    virtual void RegisterNode(IScene* newScene = 0)
    {
        //if Scene = 0 then we register this node and all they childs in rootscene
        if(newScene == NULL)
            newScene = SceneManager->getRootScene();


        if(Scene == newScene)
            return;

        //if node already registered in scene we must unregister they
        if(Scene)
            UnRegisterNode();

        if(newScene)
            newScene->RegisterNode(this);

        RegisterChilds(newScene);

        Scene = newScene;
    }
    virtual void UnRegisterNode()
    {

        if(Scene == NULL)
            return;

        //Set current scene in NULL if Scene->removeNode() recall this function again and this func again call removeNode() and programm going on loop
        IScene* oldScene = Scene;
        Scene = NULL;

        oldScene->UnRegisterNode(this);

        if(Parent)
        {
            //if Parent node not unregistered we will set current parent in null
            if(Parent->getScene() != NULL)
            {
                setParent(NULL);
            }
        }

        //UnRegister all childs
        UnRegisterChilds();

        //---------------------

    }
    virtual IScene* getScene()
    {
        return Scene;
    }
    //----------------------------------Material
    virtual void setMaterial(renderer::IMaterial* material,u32 Material_index = 0) {};
    virtual renderer::IMaterial* getMaterial(u32 Material_index = 0)
    {
        return NULL;
    };
    //----------------------------------callback
    // you can register you own function, this func will be calld on every SceneNode::update,animate and render
    // Holly cow, sorry my english =(

    /* remove this shit in future */
    virtual void register_update_callback(bool(*callback) (renderer::IRenderer*,scene::ISceneNode*))
    {
        if(callback)
            callback_update = callback;
        else
            callback_update = NULL;
    }
    virtual void register_animate_callback(bool(*callback) (renderer::IRenderer*,scene::ISceneNode*))
    {
        if(callback)
            callback_animate = callback;
        else
            callback_animate = NULL;
    }
    virtual void register_render_callback(bool(*callback) (renderer::IRenderer*,scene::ISceneNode*))
    {
        if(callback)
            callback_render = callback;
        else
            callback_render = NULL;
    }
    //----------------------------------------

    virtual void update()
    {
        if(callback_update && callback_update(SceneManager->getRenderer(),this))
            return;
    }
    virtual void animate()
    {
        if(callback_animate && callback_animate(SceneManager->getRenderer(),this))
            return;
    }
    virtual void render()
    {
        if(callback_render && callback_render(SceneManager->getRenderer(),this))
            return;
    }

protected:

    ISceneManager* SceneManager;

    //Transform
    core::matrix4f  RelativeTransformation;
    core::vector3df Position;
    core::vector3df Rotation;
    core::vector3df Scale;

    bool update_transform;

    //Node relative
    IScene*     Scene;
    ISceneNode* Parent;
    std::vector<ISceneNode*> Childs;

    //Node prop
    s32  NodeID;
    s32  NodeType;
    bool Visible;

    //Node draw hints
    s32 _somethink_;

    //callback func


    bool(*callback_update)  (renderer::IRenderer*,scene::ISceneNode*);
    bool(*callback_animate) (renderer::IRenderer*,scene::ISceneNode*);
    bool(*callback_render)  (renderer::IRenderer*,scene::ISceneNode*);
private:

    void RegisterChilds(IScene* newScene)
    {
        u32 ListSize = Childs.size();
        if(ListSize > 0)
        {
            for(u32 i = 0; i < ListSize; i++)
            {
                Childs[i]->RegisterNode(newScene);
            }
        }
    }

    void UnRegisterChilds()
    {
        u32 ListSize = Childs.size();
        for(u32 i = 0; i < ListSize; i++)
        {
            Childs[i]->UnRegisterNode();
        }
    }

};

typedef ISceneNode* sNode;
}
}
#endif // ISCENENODE_H
