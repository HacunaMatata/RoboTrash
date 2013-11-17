#ifndef CMESHREADERNEM_H
#define CMESHREADERNEM_H

#include "IMeshReader.h"
#include "IFileSystem.h"
#include "IFile.h"
#include "Logger.h"

namespace novaengine
{

struct SNEMFileHeader
{
    int magic;
    int version;

    int dataheader_offset;
    int vertdata_offset;
};
//NEM_dataheader version 1
struct SNEMDataHeaderV1
{
    int vertex_count;
    int vertex_struct;
};

class CMeshReaderNEM : public IMeshReader
{
public:
    CMeshReaderNEM(io::IFileSystem* fs);
    virtual ~CMeshReaderNEM();

    bool isSupported(const char* file_extension);
    bool isSupported(io::IFile* file);

    scene::IMesh* LoadMesh(const char* path);
    scene::IMesh* LoadMesh(io::IFile* file);

    scene::IMesh* LoadNEM(io::IFile* file);

protected:
private:
    io::IFileSystem* FileSys;
};


};
#endif // CMESHREADERNEM_H
