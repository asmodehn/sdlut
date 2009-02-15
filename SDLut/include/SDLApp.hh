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
#include "Video/SDLWindow.hh"
#include "Input/SDLJoystick.hh"
#include "Audio/SDLMixer.hh"

#include <memory>
#include <cassert>

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
			bool m_quitRequested;

	    ///Managing the underlying SDL library
            std::auto_ptr<Manager> pvm_manager;

	    ///Handling Video Ouput related behaviour
            std::auto_ptr<Window> pvm_window; // for video

	    ///Handling Audio Ouput related behaviour
            std::auto_ptr<Mixer> pvm_mixer; // for audio framework

	    ///Handling Jostick Pool for input
            std::auto_ptr<JoystickPool> pvm_jpool; //for joystick

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

	    /*
		 * Initializing Audio
		 * warning: the init audio parameters must be linked files that will be played else it cause pbs (speed too fast, cracks, ...)
		 *
		 * @frequency, default files frequency
		 * @channels, default files nb of channels
		 * @buffer_size, default files buffer size
		 */ 
	    bool initAudio(int frequency = 44100,unsigned short channels = 2,unsigned short buffer_size = 2048);

	    ///Initializing Text
	    bool initText();

	    ///Initializing Network
            bool initNet();

            ///Accessor to the Window
            Window & getWindow()
            {
		assert (pvm_window.get() && "The Window has not been created yet.To do that, use the initVideo() function before calling getWindow()." );
                return *pvm_window;
            }
	    
	    
	    ///Accessor to the Mixer
	    Mixer & getMixer()
	    {
		    assert (pvm_mixer.get() && "The Mixer has not been created yet.To do that, use the initAudio() function before calling getMixer()." );
		    return *pvm_mixer;
	    }
	    
	    ///Accessor to the Manager
            Manager & getManager()
            {
		assert (pvm_manager.get() && "The Manager has not been created yet.To do that, use one of the initXXXXX() functions before calling getManager().");
                return *pvm_manager;
            }

	    ///Accessor to the JoystickPool
            JoystickPool & getJoystickPool()
            {
		assert (pvm_jpool.get() && "The JoystickPool has not been created yet.To do that, use the initJoystick() function before calling getJoystickPool()." );
                return *pvm_jpool;
            }
			
			bool requestTermination(bool emergencyBreak = false );
			bool isTerminating () { return m_quitRequested; }


        };
    }
}
#endif
