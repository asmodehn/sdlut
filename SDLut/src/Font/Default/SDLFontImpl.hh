#ifndef SDLFONTIMPL_HH
#define SDLFONTIMPL_HH

#include "Font/SDLFont.hh"

#include <map>

namespace SDLut
{
namespace font
{
//Class implementing the default font character render (with alpha masks)
class FontImpl
{

    //this version keeps the right value for render
    std::auto_ptr<video::internal::RGBSurface> pvm_fontsurf;

    static std::map<char,video::Rect> alphalookup;
    static std::map<char,video::Rect> InitAlphaLookup();

public :

    //image 16x14 character, 225x225 pixels (all start at 0, not 1)
    FontImpl()  throw (std::logic_error);
    FontImpl(const FontImpl & font)   throw (std::logic_error);
    FontImpl & operator=(const FontImpl & font)   throw (std::logic_error);
    virtual ~FontImpl();

    virtual video::Rect getSize(const std::string & text) const;
    virtual int height();

    virtual Font::Style getStyle()
    {
        return Font::Default;
    }
    virtual void setStyle(Font::Style s) { } //does nothing only one style available in default mode.

    virtual bool isTTFImpl() const
    {
        return false;
    }
    //Rendering
    //bgc is used only if mode == shaded. Otherwise it s transparent
    virtual std::auto_ptr<video::internal::RGBSurface> render(const std::string & text,video::Color c, video::Color bgc = video::Color(), Font::RenderMode mode = Font::Solid ) const;

};
}
}
#endif //SDLFONTIMPL_HH
