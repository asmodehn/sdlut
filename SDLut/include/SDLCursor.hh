#ifndef SDL_CURSOR_HH
#define SDL_CURSOR_HH

#include "SDLPoint.hh"

#include <stdexcept>

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

struct SDL_Cursor;

namespace RAGE
{
    namespace SDL
    {

        typedef enum
        {
            arrow, blackArrow
        }
        CursorShape;

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

	    explicit Cursor(SDL_Cursor * c);

        public :
            //Constructor
            Cursor(CursorShape sh = arrow) throw (std::logic_error);

            //Destructor
	    ~Cursor();

            //Static Methods
	    static void setCurrent (const Cursor & cur);
	    static Cursor getCurrent (void);
	    static void warpCurrent (Point p);

            //Methods
	    void show(void); // show the current Cursor
	    void hide(void); // hide the current Cursor
	    bool isVisible(void); // query the cursor - return true if the cursor is visible

        };
    }
} //namespace RAGE::SDL

#endif
