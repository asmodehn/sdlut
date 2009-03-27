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
         * This class is meant to be used along with a engine. If there is no Engine provided it will use its own.
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
            friend class Window;


        protected:
            static unsigned long _defaultflags;

            RGBColor _background;




            //Constructor
            //Note : The user should not be able to set raw SDL flags manually.
            VideoGLSurface(int width, int height, int bpp) throw (std::logic_error);

        public:

            //Destructor
            virtual ~VideoGLSurface();
            //this kind of surface shouldnt be deleted by hand. the raw SDL methods takes care of it

			//Blit src into the current surface.
            bool blit (const BaseSurface& src, Rect& dest_rect, const Rect& src_rect);

            //to resize the display
            virtual bool resize (int width, int height, bool keepcontent = false);
            //to flip the videosurface
            virtual bool refresh(void);

            friend Logger & operator << (Logger & log, const VideoSurface & surf);
        };
    }
} //namespace RAGE::SDL

#endif
