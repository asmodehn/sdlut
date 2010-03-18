#include "Input/SDLCursor.hh"
#include "SDLConfig.hh"

using namespace RAGE;

namespace SDLut
{
namespace input
{

/* XPMs */
//TODO : hand & time & reticulum & ...
//TODO : manage inverse pixel, without XPM maybe ??
// --> find a way to do this properly... (which cursor format to choose ?)

const char* Cursor::_shape_arrow[] =
{
    /* width height num_colors chars_per_pixel */
    "    32    32        3            1",
    /* colors */
    "X c #000000",
    ". c #ffffff",
    "  c None",
    /* pixels */
    "X                               ",
    "XX                              ",
    "X.X                             ",
    "X..X                            ",
    "X...X                           ",
    "X....X                          ",
    "X.....X                         ",
    "X......X                        ",
    "X.......X                       ",
    "X........X                      ",
    "X.....XXXXX                     ",
    "X..X..X                         ",
    "X.X X..X                        ",
    "XX  X..X                        ",
    "X    X..X                       ",
    "     X..X                       ",
    "      X..X                      ",
    "      X..X                      ",
    "       XX                       ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "0,0"
};

const char* Cursor::_shape_blackArrow[] =
{
    /* width height num_colors chars_per_pixel */
    "    32    32        3            1",
    /* colors */
    "X c #000000",
    ". c #ffffff",
    "  c None",
    /* pixels */
    "X                               ",
    "XX                              ",
    "XXX                             ",
    "XXXX                            ",
    "XXXXX                           ",
    "XXXXXX                          ",
    "XXXXXXX                         ",
    "XXXXXXXX                        ",
    "XXXXXXXXX                       ",
    "XXXXXXXXXX                      ",
    "XXXXXXXXXXX                     ",
    "XXXXXXX                         ",
    "XXX XXXX                        ",
    "XX  XXXX                        ",
    "X    XXXX                       ",
    "     XXXX                       ",
    "      XXXX                      ",
    "      XXXX                      ",
    "       XX                       ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "0,0"
};

const char** Cursor::shapes[2] =
{
    _shape_arrow,
    _shape_blackArrow
};

//set Cursor from XPM
SDL_Cursor * Cursor::init_system_cursor(const char *image[])
{
    int i, row, col;
    Uint8 data[4*32];
    Uint8 mask[4*32];
    int hot_x, hot_y;

    i = -1;
    for ( row=0; row<32; ++row )
    {
        for ( col=0; col<32; ++col )
        {
            if ( col % 8 )
            {
                data[i] <<= 1;
                mask[i] <<= 1;
            }
            else
            {
                ++i;
                data[i] = mask[i] = 0;
            }
            switch (image[4+row][col])
            {
            case 'X':
                data[i] |= 0x01;
                mask[i] |= 0x01;
                break;
            case '.':
                mask[i] |= 0x01;
                break;
            case ' ':
                break;
            }
        }
    }
    sscanf(image[4+row], "%d,%d", &hot_x, &hot_y);
    return SDL_CreateCursor(data, mask, 32, 32, hot_x, hot_y);
}

Cursor::Cursor(CursorShape sh) throw (std::logic_error)
try :
    _cursor(init_system_cursor(shapes[sh]))
{
    if (_cursor == NULL)
        throw std::logic_error("SDL_CreateCursor returns NULL !");
}
catch (std::exception & e)
{
    Log << nl << "Exception catched on Cursor Constructor !!!" << nl <<
    e.what() << nl << GetError() << std::endl;
}


Cursor::Cursor(SDL_Cursor * c) : _cursor(c)
{
}


Cursor::~Cursor()
{
    SDL_FreeCursor(_cursor);
}

//Static Methods
void Cursor::setCurrent (const Cursor & cur)
{
    SDL_SetCursor(cur._cursor);
}

Cursor Cursor::getCurrent (void)
{
    return Cursor(SDL_GetCursor());

}
void Cursor::warpCurrent (video::Rect p)
{
    SDL_WarpMouse((Uint16)p.getx(),(Uint16)p.gety());
    std::cout << "Mouse warped !" << std::endl;
}

//Methods
void Cursor::show(void) // show the current Cursor
{
    SDL_ShowCursor(SDL_ENABLE);
}
void Cursor::hide(void) // hide the current Cursor
{
    SDL_ShowCursor(SDL_DISABLE);
}
bool Cursor::isVisible(void) // query the cursor - return true if the cursor is visible
{
    return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
}



}
} //namespace SDLut::SDL
