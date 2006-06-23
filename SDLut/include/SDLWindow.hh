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
#include "SDLEngine.hh"
#include "SDLVideoInfo.hh"
 #include "SDLVideoSurface.hh"
 #ifdef HAVE_OPENGL
 #include "SDLGLManager.hh"
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

            std::string _title, _iconname;
            Color _background;

            //here because Event are initialised along with video...
            EventManager * _eventmanager;
            VideoInfo * _videoinfo;

            bool _userengine;
            Engine* _engine;
#ifdef HAVE_OPENGL

            GLManager * _glmanager;
#endif

            VideoSurface * _screen;
			RGBSurface _icon;

            Window(std::string title); // TODO :: add the icon here

        public:
            ~Window();

            //create the screen or reset it if needed because some parameters changed
			//returns NULL if no screen available
			// calls Engine->init();
            VideoSurface * resetDisplay( int width = DEFAULT_DISPLAY_WIDTH, int height = DEFAULT_DISPLAY_HEIGHT);
            //just resize the screen (without changing flags, or bpp)
			//returns NULL if no screen available
			// calls Engine->resize();
            VideoSurface * resizeDisplay (int width, int height) const;

            VideoSurface * getDisplay( void )
            {
                return _screen;
            }
//            void setDisplay( VideoSurface * display)
//            {
//                _screen=display;
//            }

            VideoInfo * getVideoInfo( void )
            {
                return _videoinfo;
            }
            EventManager* getEventManager()
            {
                return _eventmanager;
            }


            //preset or "dynamically change" properies of the display...
            bool setResizable(bool val);
            bool setFullscreen(bool val);
#ifdef HAVE_OPENGL

            GLManager * getGLManager()
            {
                return _glmanager;
            }
            bool setOpenGL(bool val);
#endif
            bool setNoFrame(bool val);

			//to check the current properties of the display
			bool isFullscreen() {return _screen->isFullScreenset();}
			bool isResizable() {return _screen->isResizableset();}
			bool isOpenGL() {return _screen->isOpenGLset();}
			bool isNoFrame() {return _screen->isNoFrameset();}


            void setEngine(Engine * engine);
            void setBGColor(const Color & color)
			{
				_background = color;
			}
			
			//fill the VideoSurface with the BGColor
			void applyBGColor() const;

            Color getBGColor ()
            {
                return _background;
            }

            //return true on success, false otherwise
            bool iconify(void);
            void grabInput(void);
            void releaseInput(void);
            bool isInputGrabbed(void);

        protected:

            void setCaption(std::string title = DEFAULT_WINDOW_TITLE, std::string iconname = "");
            //oldversion
            void getCaption(std::string & title, std::string & iconname);

        public :
            inline void setTitle(std::string title)
            {
                setCaption(title);
            }
            std::string getTitle();

            void setIcon(const RGBSurface & icon);
            std::string getIconName();

			//Handles the event, and Call engine->prerender, engie ->render() and engine->postrender()
            bool mainLoop(unsigned int framerate = 60);

        };
    }
}
#endif
