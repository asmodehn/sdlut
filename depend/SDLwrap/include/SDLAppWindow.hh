#ifndef SDL_APPWINDOW_HH
#define SDL_APPWINDOW_HH

/**
 * \class AppWindow
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


 #include "SDLWindow.hh"
 #ifdef HAVE_OPENGL
 #include "SDLGLWindow.hh"
 #endif //HAVE_OPENGL


 namespace SDL
 {

//further reference to break dependency cycles
class EventHandler;

class AppWindow
{
        friend class App; //to access the constructor

        std::string _title, _icon;

        protected:

       int  _bpp;
       DisplaySurface * _screen;

         AppWindow(std::string title, std::string iconname,int bpp = DEFAULT_DISPLAY_BPP);

         public:


        bool reset( int width = DEFAULT_DISPLAY_WIDTH, int height = DEFAULT_DISPLAY_HEIGHT);
        bool resize (int width, int height);
        DisplaySurface * getDisplay( void ) {return _screen;}

        bool setResizable(bool val);
        bool setFullscreen(bool val);
        bool setOpenGL(bool val);
        bool setNoFrame(bool val);


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
	inline void setTitle(std::string title) { setCaption(title); }
	std::string getTitle();
	//to improve (mask, colorkey, loading wrapped Surface, etc.)
	bool setIcon(std::string iconfilename);// MAYBE version check here ?? { setCaption(_title,icon); }
	std::string getIconName();

    bool mainLoop(EventHandler & handler);

};

 }
 #endif
