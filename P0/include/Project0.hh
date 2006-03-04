#ifndef Project0_HH
#define Project0_HH


#include "SDL.hh"
#include "SDL_image.h"
#include <string>

#include "Timer.hh"
#include "Monster.hh"
#include "Character.hh"


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


////The surfaces that will be used
//SDL_Surface *_monsters_list = NULL;
//SDL_Surface *_characters_list = NULL;
//SDL_Surface *_background = NULL;
//SDL_Surface *_screen = NULL;
//
////The portions of the sprite map to be blitted
//SDL_Rect _monster[1];
//
//SDL_Rect _character_right_attack[3];
//SDL_Rect _character_left_attack[3];
//SDL_Rect _character_down_attack[3];
//SDL_Rect _character_up_attack[3];
//
//SDL_Rect _bg[1];
//
//
////Collisions Box
//SDL_Rect Character_collision_box;
//SDL_Rect Monster_collision_box;
//
////The event structure that will be used
//SDL_Event event;

//Camera def initialized in the top right corner and with the width and height of the screen
//SDL_Rect camera;// = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

//Enable UniCode
//SDL_EnableUNICODE()


//Create surface from an image function and optimized image to the desired format with white color as transparent color
SDL_Surface *create_surface( std::string filename );
//Surface blitting function wich blit a piece of a surface or the whole surface if no Rect area is defined
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
//To check colission (small beginning of a physical engine^^)
bool check_collision(SDL_Rect &A, SDL_Rect &B);
//Gnerate Background
void generate_bg();
//Initialization
bool InitWindows();
//Load Images Files
bool Load_Files();
//Clean Up Surface
void Clean_Up();


#endif
