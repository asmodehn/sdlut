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


#include "SDLManager.hh"
#include "SDLWindow.hh"
#include "SDLJoystick.hh"

namespace RAGE
{
    namespace SDL
    {

        class App
        {
            Manager * _manager;

            Window* _window; // for video
            JoystickPool* _jpool; //for joystick

            Version _sdlversion;

            std::string _name,_icon;

            App(std::string logfilename = "RAGE_SDL.log");
            ~App();

            // undefined just here to prevent copies...
            App( const App & );
            App& operator=( App);

        public:

            static App& getInstance();


            //systems initialisation...
            void setName(std::string appName = DEFAULT_WINDOW_TITLE)
            {
                _name = appName;
            }
            std::string getName()
            {
                return _name;
            }
            void setIcon(std::string appIcon = DEFAULT_WINDOW_ICON)
            {
                _icon = appIcon;
            }
            std::string getIcon()
            {
                return _icon;
            }

            ///this is mandatory to get a display and event handling (window manager, mouse, keyboard)
            bool initVideo(bool fullscreen = false,bool opengl = false,  bool resizable = true, bool noframe = false);
            ///this is mandatory to get joystick event handling
            bool initJoystick();

            //Add more when they are tested and working...
            //bool initAudio();
            //bool initTimer();

            //Accessors
            // may return NULL => always test the returned value!
            Window * getWindow()
            {
                return _window;
            }
            Manager* getManager()
            {
                return _manager;
            }
            JoystickPool * getJoystickPool()
            {
                return _jpool;
            }
            void setJoystickPool( JoystickPool * jpool)
            {
                _jpool=jpool;
            }

            const Version & getVersion()
            {
                return _sdlversion;
            }

        };
    }
}
#endif
