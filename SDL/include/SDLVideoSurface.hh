#ifndef SDL_VideoSurface_HH
#define SDL_VideoSurface_HH

/**
 * \class VideoSurface
 *
 * \ingroup Video
 * \ingroup WindowManager
 *
 * \brief This class is handle a video surface.
 *
 * This class has a derivative if your display is 3d (OpenGL).
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "SDLConfig.hh"
#include "SDLBaseSurface.hh"
#include "SDLRGBSurface.hh" //to help with backup of screen surface
#include "SDLEngine.hh"

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

        class VideoSurface : public BaseSurface
        {

            friend class Overlay;
            friend class Window;


        protected:
            static Uint32 _defaultflags;

            Color _background;

            Engine* _engine;



            //Constructor
            //Note : The user should not be able to set raw SDL flags manually.
            VideoSurface(int width, int height, int bpp) throw (std::logic_error);

        public:

            static std::vector<int> availableWidth,availableHeight;

            //Destructor
            virtual ~VideoSurface();
            //this kind of surface shouldnt be deleted by hand. the raw SDL methods takes care of it

            //to resize the display
            virtual bool resize (int width, int height);
            //to update the display
            virtual bool update(void);

            //set the background color
            virtual bool setBGColor(const Color & color);

            bool setEngine(Engine * engine);
           inline Engine * getEngine()
            {
                return _engine;
            }

            //Maybe in Window only ?
            bool update(Rect r);
            bool update(std::vector<Rect> rlist);
            //May be using a default value.. depending on what has to be done for GLWindow



            //those methods just changes the static flags used on display creation.
            //use the App::methods to also reset the display.
            static inline void setOpenGL(bool val)
            {
                if (val)
                    _defaultflags|= SDL_OPENGL;
                else
                    _defaultflags&= (~SDL_OPENGL) ;
            }
            static inline void setFullscreen(bool val)
            {
                if (val)
                    _defaultflags|= SDL_FULLSCREEN;
                else
                    _defaultflags&= (~SDL_FULLSCREEN) ;
            }
            static inline void setResizable(bool val)
            {
                if (val)
                    _defaultflags|= SDL_RESIZABLE;
                else
                    _defaultflags&= (~SDL_RESIZABLE) ;
            }
            static inline void setNoFrame(bool val)
            {
                if (val)
                    _defaultflags|= SDL_NOFRAME;
                else
                    _defaultflags&= (~SDL_NOFRAME) ;
            }
            static inline void setDoubleBuf(bool val)
            {
                if (val)
                    _defaultflags|= SDL_DOUBLEBUF;
                else
                    _defaultflags&= (~SDL_DOUBLEBUF) ;
            }
            static inline void setAnyFormat(bool val)
            {
                if (val)
                    _defaultflags|= SDL_ANYFORMAT;
                else
                    _defaultflags&= (~SDL_ANYFORMAT) ;
            }
            static inline void setSWSurface(bool val)
            {
                if (val)
                    _defaultflags|= SDL_SWSURFACE;
                else
                    _defaultflags&= (~SDL_SWSURFACE) ;
            }
            static inline void setHWSurface(bool val)
            {
                if (val)
                    _defaultflags|= SDL_HWSURFACE;
                else
                    _defaultflags&= (~SDL_HWSURFACE) ;
            }
            static inline void setHWPalette(bool val)
            {
                if (val)
                    _defaultflags|= SDL_HWPALETTE;
                else
                    _defaultflags&= (~SDL_HWPALETTE) ;
            }
            static inline void setAsyncBlit(bool val)
            {
                if (val)
                    _defaultflags|= SDL_ASYNCBLIT;
                else
                    _defaultflags&= (~SDL_ASYNCBLIT) ;
            }


            //Accessors
            inline bool isOpenGLset(void) const
            {
                return ( SDL_OPENGL & ((_surf!=NULL)?_surf->flags:_defaultflags )) != 0;
            }
            inline bool isFullScreenset(void) const
            {
                return ( SDL_FULLSCREEN & ((_surf!=NULL)?_surf->flags:_defaultflags )) != 0;
            }
            inline bool isResizableset(void) const
            {
                return ( SDL_RESIZABLE & ((_surf!=NULL)?_surf->flags:_defaultflags )) != 0;
            }
            inline bool isNoFrameset(void) const
            {
                return ( SDL_NOFRAME & ((_surf!=NULL)?_surf->flags:_defaultflags )) != 0;
            }
            inline bool isAnyFormatset(void) const
            {
                return ( SDL_ANYFORMAT & ((_surf!=NULL)?_surf->flags:_defaultflags )) != 0;
            }
            virtual inline bool isDoubleBufset(void) const
            {
                return ( SDL_DOUBLEBUF & ((_surf!=NULL)?_surf->flags:_defaultflags )) != 0;
            }
            //unused
            inline bool isASyncBlitset(void) const
            {
                return ( SDL_ASYNCBLIT & ((_surf!=NULL)?_surf->flags:_defaultflags )) != 0;
            }
            inline bool isHWPaletteset(void) const
            {
                return ( SDL_HWPALETTE & ((_surf!=NULL)?_surf->flags:_defaultflags )) != 0;
            }

            static bool checkAvailableSize( const PixelFormat * fmt );
            static bool checkAvailableSize( void);
            static int getSuggestedBPP(int width, int height);

            friend Logger & operator << (Logger & log, const VideoSurface & surf);
        };
    }
} //namespace RAGE::SDL

#endif
