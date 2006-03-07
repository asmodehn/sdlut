#ifndef Base_HH
#define Base_HH


#include "SDL.hh"
#include "SDL_image.h"
#include "SDL_ttf.h"

//#include <ctime>
#include <string>
#include <vector>

//The attributes of the window
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The dimensions of the level
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 1280;

//The frame rate
const int FRAMES_PER_SECOND = 10;

//The dimensions of the Character
const int CH_WIDTH = 32;
const int CH_HEIGHT = 32;
const int MO_WIDTH = 32;
const int MO_HEIGHT = 32;

//The direction status of the character
const int CH_RIGHT = 0;
const int CH_LEFT = 1;
const int CH_DOWN = 2;
const int CH_UP = 3;

//monsters const
const int INITIAL_MONSTERS = 15;
const int MAX_MONSTERS_SIMULTANEOUSLY = 30;

//Enable UniCode
//SDL_EnableUNICODE()


//Create surface from an image function and optimized image to the desired format with white color as transparent color
SDL_Surface *create_surface( std::string filename );
//Surface blitting function wich blit a piece of a surface or the whole surface if no Rect area is defined
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
//To check colission (small beginning of a physical engine^^)
bool check_collision(SDL_Rect &A, SDL_Rect &B);
//random function
int random(int min, int max);

#endif
