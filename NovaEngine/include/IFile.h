#ifndef IFILE_H
#define IFILE_H

#include "Object.h"
#include "Types.h"

namespace novaengine
{
namespace io
{
enum E_FILE_POINTER_TYPE
{
    EFPT_VIRTUAL,
    EFPT_NATIVE
};
class IFile : public Object
{
public:
    virtual int read(void* ptr,u32 Len) = 0;
    virtual int read(void* ptr,u32 pos,u32 Len) = 0;
    virtual int write(void* ptr,u32 Len) = 0;
    virtual int write(void* ptr,u32 pos,u32 Len) = 0;
    virtual void seek(u32 pos) = 0;

    virtual int getFilePointerType() = 0;

    virtual u32 getSize() = 0;
    /// \return Return file position
    virtual u32 getPos()     = 0;
    /// \return Return file position before last read/write/seek calls...
    virtual u32 getLastPos() = 0;

    virtual void* getData() = 0;
    virtual char* getName() = 0;

protected:
private:

};

}
}


#endif // IFILE_H
