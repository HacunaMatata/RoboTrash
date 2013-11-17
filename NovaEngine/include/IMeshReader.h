#ifndef IMESHREADER_H
#define IMESHREADER_H

#include "Object.h"
#include "IFile.h"
#include "IMesh.h"

namespace novaengine
{

class IMeshReader : public Object
{
public:

    virtual bool isSupported(const char* file_extension) = 0;
    virtual bool isSupported(io::IFile* file) = 0;

    virtual scene::IMesh* LoadMesh(const char* path) = 0;
    virtual scene::IMesh* LoadMesh(io::IFile* file) = 0;

protected:
private:
};

}

#endif // IMESHREADER_H
