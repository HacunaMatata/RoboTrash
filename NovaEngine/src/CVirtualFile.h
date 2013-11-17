#ifndef CVIRTUALFILE_H
#define CVIRTUALFILE_H

#include "IFile.h"

#include <malloc.h>
#include "Logger.h"

namespace novaengine
{
namespace io
{


class CVirtualFile : public IFile
{
public:

    CVirtualFile(u32 size,u32 pos,u8* data,const char* name = NULL)
    {
        FileSize    = size;
        FilePos     = pos;
        LastFilePos = pos;
        FileData    = data;

        if(name)
        {
            int len = strlen(name)+1;
            FileName = new char[len];
            memcpy(FileName,name,sizeof(char)*len);
        }
    }
    virtual ~CVirtualFile()
    {
        //if(FileData)
        //    delete[] FileData;
        if(FileName)
            delete[] FileName;
    }

    int read(void* ptr,u32 Len)
    {
        if(Len+FilePos > FileSize)
            return 0;

        memcpy(ptr,FileData + FilePos,Len);
        LastFilePos = FilePos;
        FilePos+=Len;

        return Len;
    }
    int read(void* ptr,u32 pos,u32 Len)
    {
        if(pos >= FileSize || (Len+pos) > FileSize)
            return 0;

        memcpy(ptr,FileData + pos,Len);

        return Len;
    }
    int write(void* ptr,u32 Len)
    {

        if(FilePos > FileSize)
            return 0;
        if(FilePos+Len > FileSize)
        {
            u32 newFileLenght = FilePos+Len;
            u8* new_stream = new byte[newFileLenght];
            memcpy(new_stream,FileData,FileSize);
            delete FileData;
            FileData = new_stream;
            FileSize = newFileLenght;
        }
        memcpy(FileData + FilePos,ptr,Len);
        LastFilePos = FilePos;
        FilePos+=Len;
        return Len;
    }

    int write(void* ptr,u32 pos,u32 Len)
    {

        if(pos > FileSize)
            return 0;
        if(pos+Len > FileSize)
        {
            u32 newFileLenght = pos+Len;
            u8* new_stream = new u8[newFileLenght];
            memcpy(new_stream,FileData,FileSize);
            delete FileData;
            FileData = new_stream;
            FileSize = newFileLenght;
        }
        memcpy(FileData + pos,ptr,Len);
        return Len;
    }
    void seek(u32 pos)
    {
        if(pos > FileSize || pos < 0)
            return;
        LastFilePos = FilePos;
        FilePos = pos;
    }

    int getFilePointerType()
    {
        return EFPT_VIRTUAL;
    }
    u32 getSize()
    {
        return FileSize;
    }
    u32 getPos()
    {
        return FilePos;
    }
    u32 getLastPos()
    {
        return LastFilePos;
    }
    void* getData()
    {
        return FileData;
    }

    char* getName()
    {
        return FileName;
    }

protected:
private:

    u32 FileSize;
    u32 FilePos;
    u32 LastFilePos;
    u8* FileData;
    char* FileName;

};

}
}


#endif // CFILE_H
