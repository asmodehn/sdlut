#ifndef SDLFONTEXTEND_HH
#define SDLFONTEXTEND_HH

#include "Font/Default/SDLFontImpl.hh"

typedef struct _TTF_Font TTF_Font;

namespace RAGE
{
namespace SDL
{

//if SDL_TTF used, provide a class to be used as a bridge.
//this way the client doesnt have to take care of which function is available
#ifdef WK_SDLTTF_FOUND

class FontExtend : public FontImpl
{
    int ptsize;
    long index;
    std::auto_ptr<RWOps> pvm_OriginalData;
    TTF_Font * _ttfstruct;

public:
    //Constructor
    FontExtend(std::string filename, int ptsize = 16, long index = 0) throw (std::logic_error);

    //Copy Constructor
    //copy completely the content of *_ttfstruct
    FontExtend(const FontExtend & );
    //Assignement operator
    FontExtend & operator=(const FontExtend &);

    //Destructor
    ~FontExtend();


    //Attributes Access
    static void byteSwapUNICODE(bool swapped);

    Font::Style getStyle();
    void setStyle(Font::Style s);

    bool isTTFImpl() const
    {
        return true;
    }

    int height();
    int ascent();
    int descent();
    int lineskip();
    long faces();
    bool faceIsFixedWidth();
    std::string faceFamilyName();
    std::string faceStyleName();

    Rect getSize(const std::string& text) const;

    //The Background color is used only if RenderMode = Shaded otherwise the background is transparent.
    std::auto_ptr<RGBSurface> render(const std::string& text, Color c, Color bgc = Color(), Font::RenderMode mode = Font::Solid) const;
};


#endif //HAVE_SDLTTF

}
}
#endif // SDLFONTEXTEND_HH
