#ifndef IVERTEXBUFFEROBJECT_H
#define IVERTEXBUFFEROBJECT_H

#include "Types.h"
#include "Object.h"

namespace novaengine
{
namespace renderer
{

class IVertexBufferObject : public Object
{
public:
    virtual void request_rebuild()  = 0;
    virtual bool required_rebuild() = 0;
protected:
private:
};

}
}

#endif // IVertexBufferObject_H
