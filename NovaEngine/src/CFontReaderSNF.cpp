#include "CFontReaderSNF.h"
#include "CFont.h"

#include "CImage.h"

namespace novaengine
{
CFontReaderSNF::CFontReaderSNF(io::IFileSystem* FS,IResourceManager* RM)
{
    FileSys = FS;
    ResMgr =  RM;
}
//---------------------------------------------------------------------------------------
CFontReaderSNF::~CFontReaderSNF()
{

}
//---------------------------------------------------------------------------------------
bool CFontReaderSNF::isSupported(const char* file_extension)
{
    if(strcmp(file_extension,".snf") == 0)
        return 1;
    return 0;
}
//---------------------------------------------------------------------------------------
bool CFontReaderSNF::isSupported(io::IFile* file)
{
    SFontHeader header;
    file->read(&header,sizeof(SFontHeader));
    file->seek(file->getLastPos());
    if(header.magic == 0x666e7300)
        return true;
    return false;
}
//---------------------------------------------------------------------------------------
gui::IFont* CFontReaderSNF::LoadFont(const char* path)
{
    io::IFile* snf_file = FileSys->open_file(path);

    if(!snf_file)
        return NULL;

    gui::IFont* font = LoadFont(snf_file);

    snf_file->release();

    if(!font)
        return NULL;

    return font;
}
//---------------------------------------------------------------------------------------
gui::IFont* CFontReaderSNF::LoadFont(io::IFile* file)
{
    u32 FileStart = file->getPos();
    gui::IFont* snf = LoadSNF(file);
    file->seek(FileStart);
    return snf;
}
//---------------------------------------------------------------------------------------
gui::IFont* CFontReaderSNF::LoadSNF(io::IFile* file)
{

    SFontHeader header;

    file->read(&header,sizeof(SFontHeader));

    if(header.magic != 0x666e7300)
    {
        io::Log::println("Failed to load font - corrupted header[not snf]",ELL_DEBUG_APP);
        return NULL;
    }

    //-------------------------------------
    /* load font texture */
    u32 width  = header.texture_width;
    u32 height = header.texture_height;
    u32 img_data_len = width * height * 4;
    u8* img_data = new u8[img_data_len];
    file->read(img_data,img_data_len);
    renderer::IImage* img= new renderer::CImage(renderer::EPF_R8G8B8A8,core::dimension2du(width,height),img_data);
    delete[] img_data;
    //-------------------------------------
    SLetter        Letter[256];
    gui::SGlyph*   Glyph = new gui::SGlyph[256];
    //-------------------------------------
    u32 MaxHeight = 0;

    for(u32 i = 0; i < 255;i++)
    {
        u32 r = file->read(&Letter[i],sizeof(SLetter));
        if(r != sizeof(SLetter))
        {
            char buf[256];
            sprintf(buf,"Filed to load font - letter count is not 256");
            io::Log::println(buf,ELL_DEBUG_APP);
            return NULL;
        }
        if(Letter[i].Letter_height>MaxHeight)
            MaxHeight=Letter[i].Letter_height;
        //-------------------
        Glyph[i].Glyph       = Letter[i].Letter;
        Glyph[i].Glyph_width = Letter[i].Letter_width;
        Glyph[i].Glyph_height= Letter[i].Letter_height;
        Glyph[i].Glyph_x_offset = 0;
        Glyph[i].Glyph_y_offset = 0;


        core::rectf Glyph_location;

        Glyph_location.X1 = float(Letter[i].Letter_coords.X1) / (float)width;
        Glyph_location.Y1 = float(Letter[i].Letter_coords.Y1) / (float)height;
        Glyph_location.X2 = float(Letter[i].Letter_coords.X2) / (float)width;
        Glyph_location.Y2 = float(Letter[i].Letter_coords.Y2) / (float)height;

        Glyph[i].Glyph_location = Glyph_location;
        //-------------------
    }

    gui::SFontParams fparams;
    fparams.Font_Size =0;
    fparams.Font_MaxHeight=MaxHeight;
    fparams.isMono = false;

    gui::IFont * font = new gui::CFont(img,fparams,Glyph,256);
    img->release();
    delete[] Glyph;
    return font;
}
//---------------------------------------------------------------------------------------
}

