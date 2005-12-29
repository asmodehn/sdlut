#ifndef SDL_APP_HH
#define SDL_APP_HH

/**
 * \class App
 *
 * \ingroup General
 *
 * \brief Principal class that handle the Application ( Lead Manager , Manage EventHandlers,the main window, the video Info, etc.)
 *
 * This class is a Meyer's Singleton, therefore should not be derivated.
 *
 * \author Alex
 *
 * \date 2005/12/24
 *
 * Contact: asmodehn@gna.org
 *
 */

 #include "SDLConfig.hh"

#include "SDLEventManager.hh"
#include "SDLManager.hh"
#include "SDLWindow.hh"


 namespace SDL
 {

     class App
     {

        Manager * _manager;
        EventManager * _eventmanager;
        Window* _window;



    std::string _name,_icon;

        App(std::string logfilename = "SDLWrap.log");
        ~App();

        // undefined just here to prevent copies...
        App( const App & );
        App& operator=( App);

public:

  static App& getInstance();


        //systems initialisation...
        void setName(std::string appName = DEFAULT_WINDOW_TITLE) { _name = appName; }
        std::string getName() { return _name;}
        void setIcon(std::string appIcon = DEFAULT_WINDOW_ICON) {_icon = appIcon;}
        std::string getIcon() { return _icon;}

        bool initWindow(bool fullscreen = false,bool opengl = false,  bool resizable = true, bool noframe = false);

        //Add more when they are tested and working...
        //bool initAudio();
        //bool initTimer();

        //Accessors
        // may return NULL => always test the returned value!
        EventManager* getEventManager() {return _eventmanager;}
        Window * getWindow() { return _window;}
        Manager* getManager() { return _manager;}




        //mainloop with the default minimal eventhandler
        //calls closeDisplay at the end.
        bool mainLoop();

     };
 }

 #endif
