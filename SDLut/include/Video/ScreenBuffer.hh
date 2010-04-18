#ifndef SDLut_ScreenBuffer_hh
#define SDLut_ScreenBuffer_hh

#include "SDLManager.hh"
#include "Video/ScreenInfo.hh"

#include "Video/internal/SDLVideoSurface.hh"
#include "Video/internal/OpenGL/SDLVideoGLSurface.hh"
#include "Video/Image.hh"

#include "Video/internal/SDLEngine.hh"
#include "Functor.hh" //for callbacks stoSDLut...

//Default Setup
#define DEFAULT_DISPLAY_WIDTH 640 // TODO not needed , can default to 4/3 mode or advised mode or desktop if nothing given...
#define DEFAULT_DISPLAY_HEIGHT 480
#define DEFAULT_DISPLAY_BPP 0 //0 for current display pixel mode

namespace SDLut
{
namespace video
{


/**
 * \class ScreenBuffer
 * \ingroup SDLut_Video
 *
 * \brief This class handles the displayed zone stored on memory...
 *
 * This class hides the details of implementation of 2D display and
 * the details of refreshing only the parts of the screen needed...( coming soon... )
 *
 * \author Alex
 *
 * \date 2009\06\24
 *
 * contact : asmodehn@gna.org
 */

class ScreenBuffer
{
    std::vector<Rect> refreshlist;
    std::vector<Rect> oldlist;

protected:

#ifdef WK_OPENGL_FOUND
    std::auto_ptr<internal::OGL::VideoGLSurface> m_screen;
#else
    std::auto_ptr<internal::VideoSurface> m_screen;
#endif

    bool fullRefreshNeeded;

    Manager* pm_manager;

    Color m_background;

    std::auto_ptr<ScreenInfo> m_scinfo;

    std::auto_ptr<internal::SDLEngine> m_engine; // for now only one engine... later multiple engines will be possible

public:
    ///creates a screenbuffer with ScreenInfo as requested parameters
    ///Manager is passed as an accessor
    ScreenBuffer( const ScreenInfo & , Manager* manager) throw (std::logic_error);
    ScreenBuffer( const ScreenBuffer & );
    ~ScreenBuffer();

    void requestFullRefresh()
    {
        fullRefreshNeeded = true;
    }

    inline const ScreenInfo & getScreenInfo()
    {
        return *m_scinfo;
    }

    void setBGColor(const Color & color)
    {
        m_background = color;
    }
    Color getBGColor()
    {
        return m_background;
    }

    //fill the VideoSurface with the BGColor
    void applyBGColor() const;

    bool resize(int width, int height);

    unsigned int getWidth();
    unsigned int getHeight();
    unsigned short getBPP();

    bool renderpass(unsigned long framerate, unsigned long& lastframe);
    bool refresh( unsigned long framerate, unsigned long& lastframe);

    bool captureBMP(std::string filename) const;

    // direct pixel drawing function
    ///WARNING : Slow
    Color getpixel(int x, int y);
    void setpixel(int x, int y, const Color & pixel);

    //Defines a 2D clippin Rect Area
    void resetClipRect( const Rect& clipr );
    Rect getClipRect( void ) const;

    // Useless and confusing function.
    // bgcolor should be enough, no need to fill screen.
    // Or put a rect on top of everything else
    //filling function for screen
    //bool fill (const Color& color)
    //{
    //    Rect dest_rect(0,0,getWidth(), getHeight());
    //    return fill( color, dest_rect );
    //}
    //bool fill (const Color& color, const Rect& dest_rect);

    //Blit src image on the screen.
    //Beware ! The final blitting rectangle is saved in dest_rect.
    inline bool blit ( const Image& src, Rect& dest_rect)
    {
        Rect src_rect(0,0,src.getWidth(), src.getHeight());
        return blit(src, dest_rect, src_rect);
    }
    //Blit src into the screen
    bool blit ( const Image& src, Rect& dest_rect, const Rect& src_rect);



};

} // SDL

} // SDLut

#endif // SDLut_ScreenBuffer_hh
