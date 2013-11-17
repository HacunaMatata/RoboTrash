#ifndef CNATIVEFILE_H
#define CNATIVEFILE_H



#include "IFile.h"

#include "Logger.h"

namespace novaengine
{
namespace io
{


class CNativeFile : public IFile
{
public:

    CNativeFile(void* file_pointer,u32 file_size,u32 file_pos,const char* name = NULL)
    {
        FileSize    = file_size;
        FilePos     = file_pos;
        LastFilePos = file_pos;
        FilePointer = (FILE*)file_pointer;

        if(name)
        {
            int len = strlen(name);
            FileName = new char[len];
            memcpy(FileName,name,sizeof(char)*len);
        }
    }
    virtual ~CNativeFile()
    {
        if(FilePointer)
            fclose(FilePointer);
        if(FileName)
            delete FileName;
    }

    int read(void* ptr,u32 Len)
    {
        if(Len+FilePos > FileSize)
            return 0;

        u32 Readed = fread(ptr,Len,1,FilePointer);
        LastFilePos = FilePos;
        FilePos+=Len;

        return Readed;
    }

    int read(void* ptr,u32 pos,u32 Len)
    {
        if(pos >= FileSize || (Len+pos) > FileSize)
            return 0;

        fseek(FilePointer,pos,SEEK_SET);
        u32 Readed = fread(ptr,Len,1,FilePointer);
        fseek(FilePointer,FilePos,SEEK_SET);

        return Readed;
    }
    int write(void* ptr,u32 Len)
    {

        u32 Writed = fwrite(ptr,Len,1,FilePointer);

        update_size();
        LastFilePos = FilePos;
        FilePos+=Len;

        return Writed;
    }

    int write(void* ptr,u32 pos,u32 Len)
    {

        fseek(FilePointer,pos,SEEK_SET);
        u32 Writed = fwrite(ptr,Len,1,FilePointer);
        fseek(FilePointer,FilePos,SEEK_SET);

        update_size();

        return Writed;
    }
    void seek(u32 pos)
    {
        if(pos > FileSize || pos < 0)
            return;
        LastFilePos = FilePos;
        FilePos = pos;
        fseek(FilePointer,pos,SEEK_SET);
    }

    int getFilePointerType()
    {
        return EFPT_NATIVE;
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
        return FilePointer;
    }

    char* getName()
    {
        return FileName;
    }

protected:
private:

    void update_size()
    {
        fseek (FilePointer, 0, SEEK_END);
        FileSize = ftell(FilePointer);
        fseek (FilePointer, FilePos, SEEK_SET);
    }

    u32 FileSize;
    u32 FilePos;
    u32 LastFilePos;
    FILE* FilePointer;
    char* FileName;

};

}
}


#endif // CNATIVEFILE_H
