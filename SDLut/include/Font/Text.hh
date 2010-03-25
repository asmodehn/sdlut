#ifndef SDLUT_TEXT_HH
#define SDLUT_TEXT_HH

#include "Video/Image.hh"
#include "Font/SDLFont.hh"

#include <stdexcept>

namespace SDLut
{
namespace font
{

/*****************
 *
 * Text is an Image that hold the render of a Text
 * but also provides an interface to its own font
 *
 **************/

class Text : public video::Image
{
    //TODO : need to manage fonts, shared, different styles and so on...
    //Simple for now
    Font m_font;
    std::string m_text;

    video::Color m_fgc,m_bgc;

    Font::RenderMode m_mode;

public:
    inline std::string Get_String()
    {
        return m_text;
    }

    Text(std::string = "",Font fnt = Font(),video::Color fg = video::Color(255,255,255),video::Color bgc = video::Color(0,0,0)) throw (std::logic_error);

    ///Copy Constructor
    Text(const Text & txt) throw (std::logic_error);

    ///Assignement Operator
    Text & operator=(const Text&);

    ~Text();

    void changeColor(video::Color c);
    void changeBGColor(video::Color c);

    void changeRendermode(Font::RenderMode rm = Font::Solid);

private:
    bool render();
};








}
}





#endif
