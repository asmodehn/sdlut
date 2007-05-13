#ifndef SDL_EVENT_HH
#define SDL_EVENT_HH

#include "Logger.hh"

#include <vector>
#include <map>

union SDL_Event;


namespace RAGE
{
    namespace SDL
{

        //further reference
	class GeneralHandler;
	class Keyboard;
	class Mouse;


    class Event
    {
        //friend class EventManager;

	    public :
		    
		//TODO : put that in class after merge between Event and Critical Event
		//defining all the events provided by SDL
	typedef enum {  Active,
		KeyDown,
		KeyUp,
		MouseMotion,
		MouseButtonDown,
		MouseButtonUp,
		JoyAxis,
		JoyBall,
		JoyHat,
		JoyButtonDown,
		JoyButtonUp,
		User,
		Quit,
		SysWM,
		Resize,
		Expose
	} Type;

	    protected :
		    std::auto_ptr<SDL_Event> const _event;

		    explicit Event(SDL_Event * const event);
	    
		    static std::vector<short> EventTyperage2sdl;
		    static std::map<short,Event::Type> EventTypesdl2rage;
		    static std::map<std::string,Event::Type> EventTypestr2rage;
		    static std::vector<short> InitEventMapping();
	    public :
		    static short Type2sdl(Type t);
		    static Type sdl2Type(short sdlt);
		    static Type str2Type(std::string strt);
	

        public:

	Event(Type type = User );
	Event(const Event & e);

	//list of accessors to make the event we want
        //    set...
	//
	//

	~Event();
	
        //push this event onto the queue
	bool push (void);
        //add this event to the queue a number of times
	int push (int times);

            //Peek number of currently pending event of the same type. (not removed from the queue)
            //std::vector<CriticalEvent> peek(int number);

            //Get number of currently pending event of the same type. (removed from the queue)
            //std::vector<CriticalEvent> get(int number);

            //retrive the tye of this CriticalEvent
	Type getType();


            //calls the handler coresponding to the event
	bool callHandler(GeneralHandler * ghndlr, Keyboard * khndlr, Mouse *  mhndlr);

	SDL_Event get_SDL();
	SDL_Event* get_pSDL() { return _event.get(); }

	
	friend Logger & operator << (Logger & log, const Type & type);
	
    };
}
}
#endif
