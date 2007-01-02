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
#include "SDLMixer.hh"

namespace RAGE
{
    namespace SDL
    {

        class App
        {
            Manager * _manager;

            Window* _window; // for video
            JoystickPool* _jpool; //for joystick
            Mixer* _mixer; // for audio framework

            Version _sdlversion;

            std::string _name,_icon;

            App(std::string logfilename = "RAGE_SDL.log");
            ~App();

            // undefined just here to prevent copies...
            App( const App & );
            App& operator=( App);

			//to work around SDLNet limitation
			bool _netInitialized;

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

            void setIcon(std::string appIcon = "")
            {
                _icon = appIcon;
            }
            std::string getIcon()
            {
                return _icon;
            }

			//just init SDL
			bool init();
            ///this is mandatory to get a display and event handling (window manager, mouse, keyboard)
            bool initVideo(bool fullscreen = false,bool opengl = false,  bool resizable = true, bool noframe = false);
            ///this is mandatory to get joystick event handling
            bool initJoystick();
			bool initCDRom();
            bool initTimer();
	    bool initAudio();

            //Add more when they are tested and working...
			bool initText();
            
			bool initNet();

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

	Mixer * getMixer()
	{
		return _mixer;
	}

            const Version & getVersion()
            {
                return _sdlversion;
            }

        };
    }
}
#endif
