#ifndef SDLut_ScreenBuffer_hh
#define SDLut_ScreenBuffer_hh

#include "SDLManager.hh"
#include "Video/ScreenInfo.hh"

#include "Video/internal/SDLVideoSurface.hh"
#include "Video/internal/OpenGL/SDLVideoGLSurface.hh"
#include "Video/Image.hh"

#include "Video/internal/SDLEngine.hh"
#include "Functor.hh" //for callbacks stoSDLut...

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

#ifdef WK_SDLut_FOUND_OPENGL
    std::auto_ptr<internal::OGL::VideoGLSurface> m_screen;
#else
    std::auto_ptr<internal::VideoSurface> m_screen;
#endif

    bool fullRefreshNeeded;

    Manager* pm_manager;

    //Color m_background;
    //for SDL rendering only
    //std::auto_ptr<Image>m_bgsurf;
    //NO NEED !!!

    std::auto_ptr<ScreenInfo> m_scinfo;

    std::auto_ptr<internal::SDLEngine> m_engine;

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

    bool resize(unsigned int width, unsigned int height);

    unsigned int getWidth();
    unsigned int getHeight();
    unsigned short getBPP();

    bool renderpass(unsigned long framerate, unsigned long& lastframe);
    bool refresh( unsigned long framerate, unsigned long& lastframe);

    bool captureBMP(std::string filename) const;

    // direct pixel drawing function
    ///WARNING : Slow
    Color getColorAt(unsigned int x,unsigned int y);
    void setColorAt(unsigned int x, unsigned int y, const Color & pixel);
    void setColorAt(Rect& dest_rect, const Color & pixel);

    //Defines a 2D clippin Rect Area
    void resetClipRect( const Rect& clipr );
    Rect getClipRect( void ) const;

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
