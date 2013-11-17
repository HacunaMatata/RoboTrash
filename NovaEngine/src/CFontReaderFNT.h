#ifndef CFONTREADERFNT_H
#define CFONTREADERFNT_H


#include "IFontReader.h"
#include "IFileSystem.h"
#include "IFile.h"
#include "Logger.h"

#include "IResourceManager.h"

namespace novaengine
{

//---------------------------------------
class CFontReaderFNT : public IFontReader
{
public:

    CFontReaderFNT(io::IFileSystem* FS,IResourceManager* rm);
    virtual ~CFontReaderFNT();

    bool isSupported(const char* file_extension);
    bool isSupported(io::IFile* file);

    gui::IFont* LoadFont(const char* path);
    gui::IFont* LoadFont(io::IFile* file);

    gui::IFont* LoadFNT(io::IFile* file);

protected:
private:

    io::IFileSystem* FileSys;
    IResourceManager* ResMgr;
};


}
#endif // CFONTREADERFNT_H
