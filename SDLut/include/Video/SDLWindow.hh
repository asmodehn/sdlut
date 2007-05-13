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

#include "Video/SDLEngine.hh"
#include "Video/SDLVideoInfo.hh"
#include "Video/SDLVideoSurface.hh"
#include "Video/SDLColor.hh"
#ifdef HAVE_OPENGL
 #include "Video/SDLGLManager.hh"
#endif //HAVE_OPENGL
#include "System/SDLEventManager.hh"

#include <memory>

//Default Setup
#define DEFAULT_DISPLAY_WIDTH 640
#define DEFAULT_DISPLAY_HEIGHT 480
#define DEFAULT_DISPLAY_BPP 0 //0 for current display pixel mode
#define DEFAULT_WINDOW_TITLE "RAGE::SDL"

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
            EventManager pvm_eventmanager;
	    
            VideoInfo pvm_videoinfo;

            bool _userengine;
            Engine* _engine;
#ifdef HAVE_OPENGL

            GLManager pvm_glmanager;
#endif

            std::auto_ptr<VideoSurface> pvm_screen;
		RGBSurface _icon;

            Window(std::string title); // TODO :: add the icon here

        public:

            ~Window();

            //create the screen or reset it if needed because some parameters changed
			//returns NULL if no screen available
			// calls Engine->init();
			// bpp = 0 means autodetect best bpp
            bool resetDisplay( int width = DEFAULT_DISPLAY_WIDTH, int height = DEFAULT_DISPLAY_HEIGHT, int bpp = 0 );
            //just resize the screen (without changing flags, or bpp)
			//returns NULL if no screen available
			// calls Engine->resize();
            bool resizeDisplay (int width, int height) const;

            VideoSurface & getDisplay( void )
            {
		    //if (!pvm_screen.get()) resetDisplay();
                return *pvm_screen;
            }
//            void setDisplay( VideoSurface * display)
//            {
//                _screen=display;
//            }

            inline VideoInfo & getVideoInfo( void )
            {
                return pvm_videoinfo;
            }

	    inline EventManager & getEventManager()
            {
                return pvm_eventmanager;
            }


            //preset or "dynamically change" properies of the display...
            bool setResizable(bool val);
            bool setFullscreen(bool val);
#ifdef HAVE_OPENGL

            inline GLManager & getGLManager()
            {
                return pvm_glmanager;
            }
            bool setOpenGL(bool val);
#endif
            bool setNoFrame(bool val);

			//to check the current properties of the display
			bool isFullscreen();
			bool isResizable();
			bool isOpenGL();
			bool isNoFrame();


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
