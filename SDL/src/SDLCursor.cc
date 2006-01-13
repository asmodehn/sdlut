#include "SDLCursor.hh"

namespace RAGE{
    namespace SDL {

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
  for ( row=0; row<32; ++row ) {
    for ( col=0; col<32; ++col ) {
      if ( col % 8 ) {
        data[i] <<= 1;
        mask[i] <<= 1;
      } else {
        ++i;
        data[i] = mask[i] = 0;
      }
      switch (image[4+row][col]) {
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
try : _cursor(init_system_cursor(shapes[sh]))
{
	if (_cursor == NULL)
		throw std::logic_error("SDL_CreateCursor returns NULL !");
}
catch (std::exception & e)
{
	Log << nl << "Exception catched on Cursor Constructor !!!" << nl <<
		e.what() << nl << GetError() << std::endl;
}
    }
} //namespace RAGE::SDL
