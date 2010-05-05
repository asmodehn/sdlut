#include "Font/Text.hh"

#include "SDLConfig.hh"

using namespace Core;

namespace SDLut
{

namespace font
{

Text::Text(std::string txt,Font fnt,video::Color fgc, video::Color bgc) throw ( std::logic_error )
try :
    m_font(fnt),m_text(txt),m_fgc(fgc),m_bgc(bgc),m_mode(Font::Solid)
{

    //default
#ifdef WK_OPENGL_FOUND
    m_img.reset(new video::internal::OGL::GLSurface(*(m_font.render(m_text,m_fgc,m_mode,m_bgc))));
#else
    m_img.reset(m_font.render(m_text,m_fgc,m_mode,m_bgc));
#endif

    if (m_img.get() == NULL) throw std::logic_error("m_img NULL in Text");

}
catch ( std::exception & e)
{
    Log << nl << e.what();
}

Text::Text(const Text & txt) throw ( std::logic_error)
try :
    m_font(txt.m_font),m_text(txt.m_text),m_fgc(txt.m_fgc),m_bgc(txt.m_bgc),m_mode(txt.m_mode)
{
    //we copy the surface, in case it gets changed later on...
#ifdef WK_OPENGL_FOUND
    m_img.reset(new video::internal::OGL::GLSurface(*(txt.m_img)));
#else
    m_img.reset(new video::internal::RGBSurface(*(txt.m_img)));
#endif

    if (m_img.get() == NULL) throw std::logic_error("m_img NULL in Text");
}
catch ( std::exception &e )
{
    Log << nl << e.what();
}

Text & Text::operator=(const Text& txt)
{
    m_font = txt.m_font;
    m_text = txt.m_text;
    m_fgc = txt.m_fgc;
    m_bgc = txt.m_bgc;
    m_mode = txt.m_mode;

    //we copy the surface, in case it gets changed later on...
#ifdef WK_OPENGL_FOUND
    m_img.reset(new video::internal::OGL::GLSurface(*(txt.m_img)));
#else
    m_img.reset(new video::internal::RGBSurface(*(txt.m_img)));
#endif

    return *this;
}

Text::~Text()
{
}

void Text::changeColor(video::Color c)
{
    m_fgc = c;
    render();
}

void Text::changeBGColor(video::Color c)
{
    m_bgc = c;
    render();
}

void Text::changeRendermode(Font::RenderMode rm)
{
    m_mode = rm;
    render();
}

bool Text::render()
{
    std::auto_ptr<video::internal::RGBSurface> surf = m_font.render(m_text,m_fgc,m_mode,m_bgc);

    //we release the auto_ptr, and change m_img.
#ifdef WK_OPENGL_FOUND
    m_img.reset(new video::internal::OGL::GLSurface(*surf));
#else
    m_img = surf;
#endif

    return m_img.get() != NULL;
}


}
}




