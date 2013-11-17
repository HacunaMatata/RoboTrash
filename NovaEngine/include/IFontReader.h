#ifndef IFONTREADER_H
#define IFONTREADER_H

#include "Object.h"
#include "IFile.h"
#include "IFont.h"

namespace novaengine
{

class IFontReader : public Object
{
public:

    virtual bool isSupported(const char* file_extension) = 0;
    virtual bool isSupported(io::IFile* file) = 0;

    virtual gui::IFont* LoadFont(const char* path) = 0;
    virtual gui::IFont* LoadFont(io::IFile* file) = 0;

protected:
private:
};

}
#endif // IFONTREADER_H
