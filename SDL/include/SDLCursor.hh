#ifndef SDL_CURSOR_HH
#define SDL_CURSOR_HH

#include "SDLConfig.hh"
#include "SDLPoint.hh"

/**
 * \class Cursor
 *
 * \ingroup Video
 *
 * \brief This class is a mouse Cursor
 *
 * This class wraps SDL_Cursor, and also provide a set of predefined cursors
 *
 * \note Feel free to add more cursors ;)
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

namespace RAGE{
    namespace SDL {

typedef enum { arrow, blackArrow } CursorShape;

class Cursor
{

	friend class Manager;

	//default shapes for cursor (XPM format)
	//corresponding to CursorShape
	static const char* _shape_arrow[];
	static const char* _shape_blackArrow[];
	static const char** shapes[2];
	//set Cursor from XPM
	static SDL_Cursor *init_system_cursor(const char *image[]);

	//The address of SDL_Cursor structure should not change
	SDL_Cursor * const _cursor;

	explicit Cursor(SDL_Cursor * c) : _cursor(c) {}

public :
	//Constructor
	Cursor(CursorShape sh = arrow) throw (std::logic_error);

	//Destructor
	~Cursor() {SDL_FreeCursor(_cursor);}

	//Static Methods
	static void setCurrent (const Cursor & cur)
	{
		SDL_SetCursor(cur._cursor);
	}

	static Cursor getCurrent (void)
	{
		return Cursor(SDL_GetCursor());

	}
	static void warpCurrent (Point p)
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
    }
} //namespace RAGE::SDL

#endif
