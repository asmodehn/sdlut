#ifndef SDLCURSOR_HH
#define SDLCURSOR_HH

#include "SDLConfig.hh"
#include "SDLPoint.hh"

typedef enum { arrow, blackArrow } SDLCursorShape;

class SDLCursor
{
	
	friend class SDLManager;
	
	//default shapes for cursor (XPM format)
	//corresponding to SDLCursorShape
	static const char** shapes[2];
	//set Cursor from XPM
	static SDL_Cursor *init_system_cursor(const char *image[]);
	
	//The address of SDL_Cursor structure should not change
	SDL_Cursor * const _cursor;

	explicit SDLCursor(SDL_Cursor * c) : _cursor(c) {}

public :
	//Constructor
	SDLCursor(SDLCursorShape sh = arrow) throw (std::logic_error);
	
	//Destructor
	~SDLCursor() {SDL_FreeCursor(_cursor);}

	//Static Methods
	static void setCurrent (const SDLCursor & cur)
	{
		SDL_SetCursor(cur._cursor);
	}

	static SDLCursor getCurrent (void)
	{
		return SDLCursor(SDL_GetCursor());
		
	}
	static void warpCurrent (SDLPoint p)
	{
		SDL_WarpMouse(p.getx(),p.gety());
		std::cout << "Mouse warped !" << std::endl;
	}
	
	//Methods
	void show(void) // show the current Cursor
	{
		SDL_ShowCursor(SDL_ENABLE);
	}
	void hide(void) // hide the current Cursor
	{
		SDL_ShowCursor(SDL_DISABLE);
	}
	bool isVisible(void) // query the cursor - return true if the cursor is visible
	{
		return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
	}

};
#endif
