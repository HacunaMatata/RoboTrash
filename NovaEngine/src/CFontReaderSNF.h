#ifndef CFONTREADERSNF_H
#define CFONTREADERSNF_H

#include "IFontReader.h"
#include "IFileSystem.h"
#include "IFile.h"
#include "Logger.h"

#include "IResourceManager.h"

namespace novaengine
{

//---------------------------------------
struct SFontHeader
{
        int   magic;
        short charset;

        short texture_width;
        short texture_height;

};
struct SLetter
{
        short              Letter;
        short              Letter_width;
        short              Letter_height;
        core::rect_t<u16>  Letter_coords;
};
//---------------------------------------
class CFontReaderSNF : public IFontReader
{
public:

    CFontReaderSNF(io::IFileSystem* FS,IResourceManager* rm);
    virtual ~CFontReaderSNF();

    bool isSupported(const char* file_extension);
    bool isSupported(io::IFile* file);

    gui::IFont* LoadFont(const char* path);
    gui::IFont* LoadFont(io::IFile* file);

    gui::IFont* LoadSNF(io::IFile* file);

protected:
private:

    io::IFileSystem* FileSys;
    IResourceManager* ResMgr;
};


}


#endif // CFONTREADERSNF_H
