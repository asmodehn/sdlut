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
#include "Video/SDLVideoInfo.hh"
#include "Video/SDLVideoSurface.hh"
#include "Video/SDLVideoGLSurface.hh"
#include "Video/Image.hh"
#include "Video/Scene.hh"

#ifdef WK_OPENGL_FOUND
#include "Video/SDLGLManager.hh"
#endif //WK_OPENGL_FOUND
#include "Video/SDLEngine.hh"
#include "Functor.hh" //for callbacks storage...

//Default Setup
#define DEFAULT_DISPLAY_WIDTH 640 // TODO not needed , can default to 4/3 mode or advised mode or desktop if nothing given...
#define DEFAULT_DISPLAY_HEIGHT 480
#define DEFAULT_DISPLAY_BPP 0 //0 for current display pixel mode

namespace RAGE
{
namespace SDL
{


class ScreenBuffer
{
    std::vector<Rect> refreshlist;
    std::vector<Rect> oldlist;

    int m_width;
    int m_height;
    int m_bpp;

protected:
    VideoInfo m_videoinfo;
    std::auto_ptr<VideoSurface> m_screen;

    Manager* pm_manager;
#ifdef WK_OPENGL_FOUND
    GLManager m_glmanager;
#endif // WK_OPENGL_FOUND
    RGBColor m_background;

    SDLEngine m_engine; // for now only one engine... later multiple engines will be possible

public:
    ScreenBuffer(int width, int height, int bpp, Manager* manager) throw (std::logic_error);
    ScreenBuffer( const ScreenBuffer & );
    ~ScreenBuffer();

//warning no protection offered here in case of wrong / unsupported size ( TODO )
    void setWidth(int width)
    {
        m_width = width;
    }
    void setHeight(int height)
    {
        m_height = height;
    }
    void setBPP(int bpp)
    {
        m_bpp = bpp;
    }
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


    //preset or "dynamically change" properties of the display...
    bool setResizable(bool val);
    bool setFullscreen(bool val);
#ifdef WK_OPENGL_FOUND

    inline GLManager & getGLManager()
    {
        return m_glmanager;
    }
    bool setOpenGL(bool val);
#endif // WK_OPENGL_FOUND
    bool setNoFrame(bool val);

    //to check the current properties of the display
    bool isFullscreen();
    bool isResizable();
    bool isOpenGL();
    bool isNoFrame();

    void setBGColor(const RGBColor & color)
    {
        m_background = color;
    }
    RGBColor getBGColor()
    {
        return m_background;
    }

    //fill the VideoSurface with the BGColor
    void applyBGColor() const;

    VideoSurface & getDisplay( void )
    {
        //if (!pvm_screen.get()) resetDisplay();
        return *m_screen;
    }

    inline VideoInfo & getVideoInfo( void )
    {
        return m_videoinfo;
    }

    bool resize(int width, int height);
    bool show(); // return true if the screenbuffer is displayed. creates the Videosurface if needed.
    bool hide();

    bool renderpass(unsigned long framerate, unsigned long& lastframe);
    bool refresh( unsigned long framerate, unsigned long& lastframe);



    //
    //function to be used in the render callback... We should make a separate object for that...
    //TODO
    //

    //Blit src image on the screen.

    inline bool blit ( const Image& src, const Point& dest_pos=Point())
    {
        //bydefault we blit the entire image
        Rect dest_rect(dest_pos,src.getWidth(), src.getHeight());
        return blit(src, dest_rect);
    }
    inline bool blit ( const Image& src, const Point& dest_pos, const Rect& src_rect)
    {
        Rect dest_rect(dest_pos,src_rect.getw(), src_rect.geth());
        return blit(src, dest_rect, src_rect);
    }
    //Beware ! The final blitting rectangle is saved in dest_rect.
    inline bool blit ( const Image& src, Rect& dest_rect)
    {
        Rect src_rect(src.getWidth(), src.getHeight());
        return blit(src, dest_rect, src_rect);
    }
    //Blit src into the screen
    bool blit ( const Image& src, Rect& dest_rect, const Rect& src_rect);



};

} // SDL

} // RAGE

#endif // SDLut_ScreenBuffer_hh
