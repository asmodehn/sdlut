#ifndef SDL_EVENTMANAGER_HH
#define SDL_EVENTMANAGER_HH

#include "SDLEvent.hh"
//#include "SDLCriticalEvent.hh"

#include "SDLMouse.hh"
#include "SDLKeyboard.hh"
#include "SDLJoystick.hh"

#include <stdexcept>

namespace RAGE
{
    namespace SDL
    {

        /**
         * \class GeneralHandler
         *
         * \ingroup EventHandling
         *
         * \brief This class handles general event sin SDLwrap
         *
         * \author Alex
         *
         * \date 2005/12/27
         *
         * Contact: asmodehn@gna.org
         *
         */

        class GeneralHandler
        {
            friend class EventManager;
            bool _quitRequested;

        public:

            GeneralHandler() : _quitRequested(false)
            {}
            virtual ~GeneralHandler()
            {}

            //Callbacks on Window / Display events
            virtual bool handleActiveEvent(bool gain, bool active, bool inputfocus, bool mousefocus);
            virtual bool handleResizeEvent(int w, int h);
            virtual bool handleExposeEvent();
            //callback on platform-dependent windows manager event
            virtual bool handleSysWMEvent(void);

            //Callback on other Events
	    virtual bool handleUserEvent(Event::Type type, int code, void* data1, void* data2);

            //Callback on Quit Event
            virtual bool handleQuitEvent(void);

            //Catch-all callback
            virtual bool handleEvent(Event &event);
        };

        /**
        * \class EventManager
        *
        * \ingroup EventHandling
        *
        * \brief This class manages the event handling in SDLwrap
        *
        * There should always be one and only one EventManager
        *
        * \author Alex
        *
        * \date 2005/12/27
        *
        * Contact: asmodehn@gna.org
        *
        */
        class EventManager
        {
            friend class Window; // to build the unique instance of EventManager

        protected:
            //filter to decide if an event is set as critical or not
  //          Uint8 _criticaltypes;

            //WARNING : the handler must be initialized properly before setting a corresponding type as critical
            GeneralHandler * ghndlr;
            Mouse * mhndlr;
            Keyboard * khndlr;


	    EventManager()  : /*_criticaltypes( 0),*/ ghndlr(new GeneralHandler()),mhndlr(new Mouse()), khndlr(NULL)
            {}
            ~EventManager()
            {
				if (ghndlr != NULL)
					delete ghndlr, ghndlr = NULL;
				if (mhndlr != NULL)
					delete mhndlr, mhndlr = NULL;
				if (khndlr != NULL)
					delete khndlr, khndlr = NULL;
			}



        public :

            void setKeyboard(Keyboard * newkhndlr)
            {
                khndlr = newkhndlr;
            }
            void setGeneralHandler(GeneralHandler * newghndlr)
            {
                ghndlr = newghndlr;
            }
            void setMouse(Mouse * newmhndlr)
            {
                mhndlr = newmhndlr;
            }

            //method to trigger the app exiting of the mainloop...
            bool quitRequested()
            {
                bool res = false;
                if (khndlr != NULL)
                    res = res || khndlr->_quitRequested ;
                if (ghndlr !=NULL)
                    res = res || ghndlr->_quitRequested ;
                return res;
            }

            //Wait indefinitely for the next available event
            //return the event found or throw an exception if error.
            Event wait () throw(std::logic_error);
/*
            void setCriticalType(EventType type)
            {
                _criticaltypes |= type;
            }*/

            //handle all the critical events in the queue in a loop
            void handleAll();

            //handle the next critical event
            bool handleNext();

            //handle the next event of this type
	    bool handleNext(Event::Type type);

            //Pump the event loop.
            //Implicitely called by handleAll() or handleNext() but not by the "critical" methods
	    void pump();
	    
        };
    }
}

#endif

