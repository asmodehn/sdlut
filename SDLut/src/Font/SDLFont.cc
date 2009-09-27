#include "Font/SDLFont.hh"

#include "SDLConfig.hh"

#include "Default/SDLFontImpl.hh"
#include "TTF/SDLFontExtend.hh"

namespace RAGE
{
namespace SDL
{

Font::Font() throw (std::logic_error)
try :
    _font( new FontImpl())
{
    if (!_font.get())
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
    _font(0)
{
    bool ttfavailable = setTTF( filename, ptsize);
    if (!ttfavailable || !_font.get())
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
        : _font(0)
{
    if (font._font.get() != 0 ) // should always be the case, just need to make sure with default and other constructors
    {
        if ( font.isTTFAvailable() )
        {
            //duplicated
            _font.reset(new FontExtend(static_cast<const FontExtend&>(*font._font)));
        }
        else
        {
            //duplicated
            _font.reset(new FontImpl(*font._font));
        }
    }

}


Font::~Font()
{
}


std::auto_ptr<Image> Font::render(std::string text, RGBColor c, RenderMode mode, RGBColor bgc) const
{
    std::auto_ptr<Image> textimg( new Image(_font->render(text,c,bgc,mode)) );

    return textimg;
}

bool Font::setTTF(std::string filename, int ptsize)
{
    bool changed = false;
#ifdef WK_SDLTTF_FOUND
    try
    {
        _font.reset( new FontExtend(filename,ptsize) );
    }
    catch (std::exception& e)
    {
        Log << nl << "Error in TTF File Loading :"  << nl <<
        e.what() << std::endl;
    };

    changed = (_font.get() != 0);
#else
    Log << nl << "Feature not enabled. TTF loading is disabled.";
#endif
    return changed;
}

bool Font::isTTFAvailable() const
{
    return _font->isTTFImpl();
}

Font::Style Font::getStyle() const
{
    return _font->getStyle();
}

void Font::setStyle(Style s)
{
    _font->setStyle(s);
}

Rect Font::getSize(const std::string& text)
{
    //return (static_cast<FontExtend*>(_font.get()))->getSize(text);
    return _font.get()->getSize(text);
}

int Font::getHeight() const
{
    //return (static_cast<FontExtend*>(_font.get()))->height();
    return _font.get()->height();
}




}
}
