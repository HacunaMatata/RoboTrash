#ifndef OBJECT_H
#define OBJECT_H

#include <cstdio>

#define NOVAENGINE_OBJECT_START_REFERENCECOUNT_VAL 1

namespace novaengine
{

class Object;

/// \brief Need for handle object release
class ObjectManager
{
public:
    virtual bool object_release_request(const Object* obj) = 0;
};


class Object
{
public:
    /// \brief Default constructor
    ///
    /// Set ReferenceCounter in 1,ObjectName in "NotDefined" and ObjectMgr in NULL
    Object() :
        ReferenceCount(NOVAENGINE_OBJECT_START_REFERENCECOUNT_VAL),
        ObjectName("NotDefined"),
        ObjectMgr(NULL)
    {
    }

    virtual ~Object()
    {
    }
    /// \brief Increment referencecount
    inline void capture() const
    {
        ReferenceCount++;
    }
    /// \brief decrement referencecount
    /// Decrement referencecount and delete object if ReferenceCount < 1
    inline void release() const
    {
        ReferenceCount--;
        if(ReferenceCount < 1)
        {
            if(ObjectMgr)
            {

                 if(ObjectMgr->object_release_request(this) == false)
                     {
                         capture();
                         return;
                     }
            }
            delete this;
        }
    }
    /// \brief Destroy object
    /// Destroy object instantly(ignoring ReferenceCount)
    inline void anihilate() const
    {
        delete this;
    }
    /// \brief Return ReferenceCount
    /// \return ReferenceCount
    inline int getReferenceCount() const
    {
        return ReferenceCount;
    }

    /// \brief Depricated Method
    inline bool isOk() const
    {
        if(ReferenceCount < 1)
            return false;
        return true;
    }
    /// \brief Set name for this object
    /// \param name Set name for this object
    inline void setObjectName(const char* name)
    {
        ObjectName = name;
    }
    /// \brief Get object name
    /// \return return object name
    inline const char* getObjectName()
    {
        return ObjectName;
    }
    /// \brief Set objectmanager for this object
    /// \param objmgr Set objectmanager = objmgr
    /// ObjectManager receive object_release_request if object will be destroyed
    inline void object_setmanager(ObjectManager* objmgr)
    {
        ObjectMgr = objmgr;
    }


protected:
private:

    mutable int ReferenceCount;
    const char* ObjectName;
    ObjectManager* ObjectMgr;
};

}
#endif // OBJECT_H
