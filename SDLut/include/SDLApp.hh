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

#include "SDLManager.hh"
#include "SDLWindow.hh"
#include "SDLJoystick.hh"
#include "SDLMixer.hh"

#ifndef LOGFILENAME
#define LOGFILENAME "RAGE_SDLut.log"
#endif //LOGFILENAME

namespace RAGE
{
    namespace SDL
    {

	extern std::string GetError();
	    
        class App
        {
	    ///Managing the underlying SDL library
            Manager * pvm_manager;

	    ///Handling Video Ouput related behaviour
            Window* pvm_window; // for video

	    ///Handling Jostick Pool for input
            JoystickPool* pvm_jpool; //for joystick

	    ///Handling Audio Ouput related behaviour
            Mixer* pvm_mixer; // for audio framework

	    ///Storing name and icon for this application
            std::string pvm_name,pvm_icon;

	    ///Constructor called privately by the static instanciator.
	    ///setting default name and icons
            App();
	    ///Destructor
            ~App();

            /// undefined. just here to prevent copies...
            App( const App & );
            App& operator=( App);

        public:

		///static instanciator to create App if needed or return its unique instance
            static App& getInstance();


	    ///Setting name for the application
            void setName(std::string appName)
            {
                pvm_name = appName;
            }
	    ///name accessor.
            std::string getName()
            {
                return pvm_name;
            }

	    ///Setting icon filename for the application
            void setIcon(std::string appIcon)
            {
                pvm_icon = appIcon;
            }
	    ///icon filename accessor
            std::string getIcon()
            {
                return pvm_icon;
            }

	    ///Minimal init for SDL
	    bool init();
			
	    ///Initializing Video
            ///this is mandatory to get a display and event handling (window manager, mouse, keyboard)
            bool initVideo(bool fullscreen = false,bool opengl = false,  bool resizable = true, bool noframe = false);

	    ///Initializing Joystick-like inputs
            ///this is mandatory to get joystick event handling
            bool initJoystick();

	    ///Initializing CDRom
	    bool initCDRom();

	    ///Initializing Timers
            bool initTimer();

	    ///Initializing Audio
	    bool initAudio();

	    ///Initializing Text
	    bool initText();

	    ///Initializing Network
            bool initNet();

            ///Accessor to the Window
            Window * getWindow()
            {
		assert (pvm_window);
                return pvm_window;
            }
	    
	    
	    ///Accessor to the Mixer
	    Mixer * getMixer()
	    {
		    assert (pvm_mixer);
		    return pvm_mixer;
	    }
	    
	    ///Accessor to the Manager
            Manager* getManager()
            {
		assert (pvm_manager);
                return pvm_manager;
            }

	    ///Accessor to the JoystickPool
            JoystickPool * getJoystickPool()
            {
		assert (pvm_jpool);
                return pvm_jpool;
            }

	    ///to change the joystick pool
            void setJoystickPool( JoystickPool * jpool)
            {
                pvm_jpool=jpool;
            }


        };
    }
}
#endif
