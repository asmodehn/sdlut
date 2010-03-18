#ifndef SDLut_ScreenBuffer_hh
#define SDLut_ScreenBuffer_hh

/**
 * \class ScreenBuffer
 * \ingroup Video
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

#include "SDLManager.hh"
#include "Video/internal/SDLVideoInfo.hh"
#include "Video/internal/SDLVideoSurface.hh"
#include "Video/internal/OpenGL/SDLVideoGLSurface.hh"
#include "Video/Image.hh"

#ifdef WK_OPENGL_FOUND
#include "Video/internal/OpenGL/OGLVideoInfo.hh"
#endif //WK_OPENGL_FOUND
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


class ScreenBuffer
{
    std::vector<Rect> refreshlist;
    std::vector<Rect> oldlist;

    int m_width;
    int m_height;
    int m_bpp;

protected:

    #ifdef WK_OPENGL_FOUND
    std::auto_ptr<internal::OGL::VideoGLSurface> m_screen;
    #else
    std::auto_ptr<internal::VideoSurface> m_screen;
    #endif


    bool fullRefreshNeeded;

    Manager* pm_manager;
#ifdef WK_OPENGL_FOUND
    internal::OGL::OGLVideoInfo m_oglvideoinfo;
#endif // WK_OPENGL_FOUND
    Color m_background;

    std::auto_ptr<internal::SDLEngine> m_engine; // for now only one engine... later multiple engines will be possible

public:
    ScreenBuffer(int width, int height, int bpp, Manager* manager) throw (std::logic_error);
    ScreenBuffer( const ScreenBuffer & );
    ~ScreenBuffer();

    ///Set size and BPP for next shown ScreenBuffer
    ///Warning : different from resize which resize dynamically.
    void setSize(int width, int height);
    void setBPP(int bpp);

    int getWidth()
    {
        return m_width;
    }
    int getHeight()
    {
        return m_height;
    }
    int getBPP()
    {
        return m_bpp;
    }

    void requestFullRefresh()
    {
        fullRefreshNeeded = true;
    }

    //preset or "dynamically change" properties of the display...
    bool setResizable(bool val);
    bool setFullscreen(bool val);
#ifdef WK_OPENGL_FOUND

    inline internal::OGL::OGLVideoInfo & getOGLVideoInfo()
    {
        return m_oglvideoinfo;
    }
    bool setOpenGL(bool val);
#endif // WK_OPENGL_FOUND
    bool setNoFrame(bool val);

    //to check the current properties of the display
    bool isFullscreen();
    bool isResizable();
    bool isOpenGL();
    bool isNoFrame();

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

    internal::VideoSurface & getDisplay( void )
    {
        //if (!pvm_screen.get()) resetDisplay();
        return *m_screen;
    }

    bool resize(int width, int height);
    bool show(); // return true if the screenbuffer is displayed. creates the Videosurface if needed.
    bool hide();

    bool renderpass(unsigned long framerate, unsigned long& lastframe);
    bool refresh( unsigned long framerate, unsigned long& lastframe);

    //pixel drawing function
    Color getpixel(int x, int y)
    {
        return m_screen->getPixelFormat().getColor(m_screen->getpixel(x, y));
    }

    void setpixel(int x, int y, const Color & pixel)
    {
        m_screen->setpixel(x, y, m_screen->getPixelFormat().getPixelColor(pixel));
    }

    //Defines a clippin Area
    void setClipRect( const Rect& clipr );
    Rect getClipRect( void ) const;

    //filling function for screen
    bool fill (const Color& color)
    {
        Rect dest_rect(0,0,getWidth(), getHeight());
        return fill( color, dest_rect );
    }
    bool fill (const Color& color, const Rect& dest_rect);


    //These functions are same as the ones in Image
    //Maybe we can privately inherit from a common base class... TODO
    //TO THINK ABOUT : interest of having an overlayer on top of RGBSurface and BaseSurface ???
    // Is the State pattern really useful here ?

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
