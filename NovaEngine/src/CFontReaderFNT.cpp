#include "CFontReaderFNT.h"
#include "CFont.h"

#include "CImage.h"
#include <vector>

namespace novaengine
{

int read_string(io::IFile* file,char* out_string)
{
    u64 start_pos = file->getPos();

    u32 str_len = 0;
    char   byte = 0;
    bool eof = false;

    while(byte != '\n' && eof != true)
    {
        if(file->read(&byte,1) == 0)
        {
            eof = true;
            break;
        }
        str_len++;
    }
    file->seek(start_pos);
    if(file->read(out_string,str_len) < str_len )
    {
        file->seek(start_pos);
        out_string = NULL;
        return 0;
    }
    out_string[str_len] = '\0';
    return str_len;
}

CFontReaderFNT::CFontReaderFNT(io::IFileSystem* FS,IResourceManager* RM)
{
    FileSys = FS;
    ResMgr =  RM;
}
//---------------------------------------------------------------------------------------
CFontReaderFNT::~CFontReaderFNT()
{
    //dtor
}
//---------------------------------------------------------------------------------------
bool CFontReaderFNT::isSupported(const char* file_extension)
{
    if(strcmp(file_extension,".fnt") == 0)
        return 1;
    return 0;
}
//---------------------------------------------------------------------------------------
bool CFontReaderFNT::isSupported(io::IFile* file)
{
    char* str;
    file->read(&str,9);
    file->seek(file->getLastPos());
    if(strcmp(str,"textures:") == 0)
        return true;
    return false;
}
//---------------------------------------------------------------------------------------
gui::IFont* CFontReaderFNT::LoadFont(const char* path)
{
    io::IFile* fnt_file = FileSys->open_file(path);

    if(!fnt_file)
        return NULL;

    gui::IFont* font = LoadFont(fnt_file);

    fnt_file->release();

    if(!font)
        return NULL;

    return font;
}
//---------------------------------------------------------------------------------------
gui::IFont* CFontReaderFNT::LoadFont(io::IFile* file)
{
    u32 FileStart = file->getPos();
    gui::IFont* snf = LoadFNT(file);
    file->seek(FileStart);
    return snf;
}
//---------------------------------------------------------------------------------------
gui::IFont* CFontReaderFNT::LoadFNT(io::IFile* file)
{
    char str_buf[256];
    u32  str_len = 0;

    gui::SFontParams font_params;
    font_params.Font_MaxHeight = 0;
    //------------------------------------------
    str_len = read_string(file,str_buf);
    char texture_name[256];
    sscanf(str_buf,"textures: %255s",texture_name);
    renderer::IImage* image = ResMgr->loadImage(texture_name);
    if(image == NULL)
        return NULL;
    //------------------------------------------
    str_len = read_string(file,str_buf);
    char font_name[256];
    sscanf(str_buf,"%255s %d",font_name,&font_params.Font_Size);
    //------------------------------------------
    std::vector<gui::SGlyph> Glyphs;

    bool done = false;
    while(!done)
    {

        s16 Char   = 0;
        u32 Xpos   = 0;
        u32 Ypos   = 0;
        u32 Width  = 0;
        u32 Height = 0;
        u32 Xoff   = 0;
        u32 Yoff   = 0;
        u32 Worg   = 0;
        u32 Horg   = 0;

        str_len = read_string(file,str_buf);
        if(sscanf(str_buf,"%hd %d %d %d %d %d %d %d %d",&Char,&Xpos,&Ypos,&Width,&Height,&Xoff,&Yoff,&Worg,&Horg) < 9)
        {
            done=true;
            break;
        }

        if(font_params.Font_MaxHeight <= Worg)
            font_params.Font_MaxHeight = Worg;

        gui::SGlyph newGlyph;
        newGlyph.Glyph       = Char;
        newGlyph.Glyph_width = Width;
        newGlyph.Glyph_height= Height;
        newGlyph.Glyph_x_offset = Xoff;
        newGlyph.Glyph_y_offset = Yoff;
        newGlyph.Glyph_location.X1 = float(Xpos)          / float(image->getImageDimension().width);
        newGlyph.Glyph_location.X2 = float(Xpos + Width)  / float(image->getImageDimension().width);
        newGlyph.Glyph_location.Y1 = float(Ypos)          / float(image->getImageDimension().height);
        newGlyph.Glyph_location.Y2 = float(Ypos + Height) / float(image->getImageDimension().height);
        //printf("%f %f %f %f\n.",newGlyph.Glyph_location.X1,newGlyph.Glyph_location.Y1,newGlyph.Glyph_location.X2,newGlyph.Glyph_location.Y2);
        Glyphs.push_back(newGlyph);
    }


    font_params.isMono = false;

    gui::IFont * font = new gui::CFont(image,font_params,&Glyphs.front(),Glyphs.size());
    image->release();

    return font;
}
//---------------------------------------------------------------------------------------
}


