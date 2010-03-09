#ifndef SDL_VideoGLSurface_HH
#define SDL_VideoGLSurface_HH

/**
 * \class VideoGLSurface
 *
 * \ingroup Video
 * \ingroup WindowManager
 *
 * \brief This class is handle a video OpenGL surface.
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "Video/SDLVideoSurface.hh"
#include "Video/SDLGLSurface.hh"

#include <iostream>
#include <vector>
#include <list>

namespace RAGE
{
namespace SDL
{


/**
 * \class Videosurface
 *
 * \ingroup Video
 *
 * \brief A class to wrap SDL_Surface only when it is a Video one
 *
 * This class code hte behaviour for a VideoSurface, when built with WK_OPENGL_FOUND
 * Note that it doesnt mean that the OpenGL flag is set on the surface.
 * Therefore it must be checked before any OpenGL call, and if not, equivalent Base Function
 * should be called instead.
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

class VideoGLSurface : public VideoSurface
{

    friend class Overlay;
    friend class ScreenBuffer;


public:
    virtual Renderer getRenderer()
    {
        if (isOpenGLset() )
            {
                return OpenGL;
            }
        else
        {
            return SDL;
        }
    }

    //Constructor
    //Note : The user should not be able to set raw SDL flags manually.
    VideoGLSurface(int width, int height, int bpp) throw (std::logic_error);

public:

    //Destructor
    virtual ~VideoGLSurface();
    //this kind of surface shouldnt be deleted by hand. the raw SDL methods takes care of it


    virtual Color getpixel(int x, int y);
    virtual void setpixel(int x, int y, Color pixel);


    //Blit src into the current surface.
    //emergency handling : surface might not be GLSurface, and if so, needs to be converted...
    virtual bool blit (RGBSurface& src, Rect& dest_rect, const Rect& src_rect);

    inline bool blit (GLSurface& src, Rect& dest_rect)
    {
        Rect src_rect(0,0,src.getWidth(), src.getHeight());
        return blit(src, dest_rect, src_rect);
    }
    bool blit (GLSurface& src, Rect& dest_rect, const Rect& src_rect);

    //Fill
    virtual bool fill (const PixelColor& pcolor);

    virtual bool fill (const PixelColor& pcolor, Rect dest_rect);




    //to resize the display
    virtual bool resize (int width, int height, bool keepcontent = false);

    //to flip the videosurface
    virtual bool refresh(void);


    virtual bool update(Rect r);

    virtual bool update(std::vector<Rect> rlist);


    friend Logger & operator << (Logger & log, const VideoSurface & surf);
};

}
} //namespace RAGE::SDL

#endif
