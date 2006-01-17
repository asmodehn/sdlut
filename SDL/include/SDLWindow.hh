#ifndef SDL_WINDOW_HH
#define SDL_WINDOW_HH

/**
 * \class Window
 *
 * \ingroup General
 *
 * \brief Class that handle the Application Window
 *
 *
 * \author Alex
 *
 * \date 2005/12/24
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "SDLConfig.hh"

#include "SDLVideoInfo.hh"
 #include "SDLVideoSurface.hh"
 #ifdef HAVE_OPENGL
 #include "SDLGLManager.hh"
 #include "SDLGLSurface.hh"
 #endif //HAVE_OPENGL


namespace RAGE
{
    namespace SDL
    {

        //further reference to break dependency cycles
        class EventManager;

        class Window
        {
            friend class App; //to access the constructor



        protected:

            std::string _title, _icon;
            Color _background;

            //here because Event are initialised along with video...
            EventManager * _eventmanager;
            VideoInfo * _videoinfo;

            bool _userengine;
            Engine* _engine;
#ifdef HAVE_OPENGL

            GLManager * _glmanager;
            bool _userglengine;
            GLEngine* _glengine;
#endif



            VideoSurface * _screen;

            Window(std::string title, std::string iconname);

        public:
            ~Window();

            //create the screen
            bool reset( int width = DEFAULT_DISPLAY_WIDTH, int height = DEFAULT_DISPLAY_HEIGHT);
            //just resize the screen (without changing flags, or bpp)
            bool resize (int width, int height) const;

            VideoSurface * getDisplay( void )
            {
                return _screen;
            }
            void setDisplay( VideoSurface * display)
            {
                _screen=display;
            }

            VideoInfo * getVideoInfo( void )
            {
                return _videoinfo;
            }
            EventManager* getEventManager()
            {
                return _eventmanager;
            }

            //preset the flags
            bool setResizable(bool val);
            bool setFullscreen(bool val);
#ifdef HAVE_OPENGL

            GLManager * getGLManager()
            {
                return _glmanager;
            }
            bool setOpenGL(bool val);
            void setGLEngine(GLEngine * glengine);
#endif

            void setEngine(Engine * engine);
            bool setNoFrame(bool val);

            //BGColor works only on 2DWindow
            void setBGColor(const Color & color)
            {
                _background = color;
            }
            Color getBGColor ()
            {
                return _background;
            }

            //return true on success, false otherwise
            bool iconify(void);
            bool toggleFullScreen(void);
            void grabInput(void);
            void releaseInput(void);
            bool isInputGrabbed(void);

            //WM methods
        protected:

            void setCaption(std::string title = DEFAULT_WINDOW_TITLE, std::string icon = DEFAULT_WINDOW_ICON);
            //oldversion
            void getCaption(std::string & title, std::string & icon);
        public :
            inline void setTitle(std::string title)
            {
                setCaption(title);
            }
            std::string getTitle();
            //to improve (mask, colorkey, loading wrapped Surface, etc.)
            bool setIcon(std::string iconfilename);// MAYBE version check here ?? { setCaption(_title,icon); }
            std::string getIconName();

            bool mainLoop();

        };
    }
}
#endif
