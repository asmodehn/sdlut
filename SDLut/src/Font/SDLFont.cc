#include "Font/SDLFont.hh"

#include "SDLConfig.hh"

#include "Default/SDLFontImpl.hh"
#include "TTF/SDLFontExtend.hh"

//#define DEBUG 2
using namespace RAGE;

namespace SDLut
{
namespace font
{

Font::Font() throw (std::logic_error)
try :
    pvm_font( new FontImpl())
{
    if (!pvm_font.get())
    {
        throw std::logic_error("Font Support not available");
    }
}
catch (std::exception& e)
{
    Log << nl << "Exception catched in Font Constructor :"  << nl <<
    e.what() << std::endl;
    //TODO : much more explicit error message...
}

Font::Font(std::string filename , int ptsize )
try :
    pvm_font(0)
{
    bool ttfavailable = setTTF( filename, ptsize);
    if (!ttfavailable || !pvm_font.get())
    {
        throw std::logic_error("Font Support not available");
    }
}
catch (std::exception& e)
{
    Log << nl << "Exception catched in Font Constructor :"  << nl <<
    e.what() << std::endl;
    //TODO : much more explicit error message...
}


//Copy Constructor
Font::Font(const Font &font)
        : pvm_font(0)
{
    if (font.pvm_font.get() != 0 ) // should always be the case, just need to make sure with default and other constructors
    {
        if ( font.isTTFAvailable() )
        {
            //duplicated
            pvm_font.reset(new FontExtend(static_cast<const FontExtend&>(*font.pvm_font)));
        }
        else
        {
            //duplicated
            pvm_font.reset(new FontImpl(*font.pvm_font));
        }
    }

}

Font& Font::operator=(const Font & font)
{
    if (font.pvm_font.get() != 0 ) // should always be the case, just need to make sure with default and other constructors
    {
        if ( font.isTTFAvailable() )
        {
            //duplicated
            pvm_font.reset(new FontExtend(static_cast<const FontExtend&>(*font.pvm_font)));
        }
        else
        {
            //duplicated
            pvm_font.reset(new FontImpl(*font.pvm_font));
        }
    }

    return *this;
}

Font::~Font()
{
}

std::auto_ptr<video::internal::RGBSurface> Font::render(std::string text, video::Color c, RenderMode mode, video::Color bgc) const
{
    std::auto_ptr<video::internal::RGBSurface> textimg = pvm_font->render(text,c,bgc,mode);

#if( DEBUG == 2)
    textimg->saveBMP( text + ".bmp");
#endif
    return textimg;
}

bool Font::setTTF(std::string filename, int ptsize)
{
    bool changed = false;
#ifdef WK_SDLTTF_FOUND
    try
    {
        pvm_font.reset( new FontExtend(filename,ptsize) );
    }
    catch (std::exception& e)
    {
        Log << nl << "Error in TTF File Loading :"  << nl <<
        e.what() << std::endl;
    };

    changed = (pvm_font.get() != 0);
#else
    Log << nl << "Feature not enabled. TTF loading is disabled.";
#endif
    return changed;
}

bool Font::isTTFAvailable() const
{
    return pvm_font->isTTFImpl();
}

Font::Style Font::getStyle() const
{
    return pvm_font->getStyle();
}

void Font::setStyle(Style s)
{
    pvm_font->setStyle(s);
}

video::Rect Font::getSize(const std::string& text)
{
    //return (static_cast<FontExtend*>(_font.get()))->getSize(text);
    return pvm_font.get()->getSize(text);
}

int Font::getHeight() const
{
    //return (static_cast<FontExtend*>(_font.get()))->height();
    return pvm_font.get()->height();
}




}
}
