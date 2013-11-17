#include "CFileSystem.h"

namespace novaengine
{
namespace io
{
CFileSystem::CFileSystem():
    UseNativeFiles(false)
{
}
//--------------------------------------------------------------------------------------------------------
CFileSystem::~CFileSystem()
{
    //dtor
}
//--------------------------------------------------------------------------------------------------------
IFile* CFileSystem::open_file(const s8* filename,bool NativeFile)
{

    FILE* stream = fopen(filename,"rb");

    if(!stream)
    {
        io::Log::println("Cannot open file",filename,ELL_ERROR);
        return NULL;
    }

    u32  FileLenght   = 0;
    u32  FilePosition = 0;

    fseek (stream, 0, SEEK_END);
    FileLenght = ftell(stream);
    fseek (stream, 0, SEEK_SET);

    //Load file in ram and use(Virtual) or use directly from hdd(Native)
    if(NativeFile || UseNativeFiles)
    {
        return new CNativeFile(stream,FileLenght,FilePosition,filename);
    }
    else
    {
        u8* FileData = new u8[FileLenght];

        fread(FileData,FileLenght,1,stream);

        fclose(stream);

        return  new CVirtualFile(FileLenght,FilePosition,FileData,filename);
    }
}
//--------------------------------------------------------------------------------------------------------
IFile* CFileSystem::open_stream(const s8* filename, u8* filedata, u32 datasize)
{
    u32  FileLenght   = datasize;
    u32  FilePosition = 0       ;

    return new CVirtualFile(FileLenght,FilePosition,filedata,filename);
}
//--------------------------------------------------------------------------------------------------------
IFile* CFileSystem::create(const char* filename,bool NativeFile)
{
    FILE* stream = fopen(filename,"wb");
    if(!stream)
    {
        io::Log::println("Cannot open file",filename,ELL_ERROR);
        return NULL;
    }

    //Load file in ram and use(Virtual) or use directly from hdd(Native)
    if(NativeFile || UseNativeFiles)
    {
        return new CNativeFile(stream,0,0,filename);
    }
    else
    {
        fclose(stream);
        return  new CVirtualFile(0,0,0,filename);
    }
}
//--------------------------------------------------------------------------------------------------------
void   CFileSystem::save(const char* filename,IFile* File)
{
    if(File->getFilePointerType() == EFPT_VIRTUAL)
    {
        FILE* stream = fopen(filename,"wb");
        if(!stream)
        {
            io::Log::println("Cannot open file",filename,ELL_ERROR);
            return ;
        }
        fwrite(File->getData(),File->getSize(),1,stream);
        fclose(stream);
    }
    else
    {
       return;
    }
}
//--------------------------------------------------------------------------------------------------------
void CFileSystem::useNativeFileLoadMethod(bool mode)
{
    UseNativeFiles = mode;
}
//--------------------------------------------------------------------------------------------------------
}
}
