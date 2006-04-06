#ifndef Base_HH
#define Base_HH

#include "SDL.hh"

using namespace RAGE::SDL;

#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>

//The initial attributes of the window
const int SCREEN_WIDTH = 800;//640;
const int SCREEN_HEIGHT = 600;//480;
const int SCREEN_BPP = 32;

//The current attributes of the window
extern int CURRENT_SCREEN_WIDTH;
extern int CURRENT_SCREEN_HEIGHT;
extern int CURRENT_SCREEN_BPP;

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

//Initial Chracter position
const int CH_INITIAL_X = 192;
const int CH_INITIAL_Y = 224;

//The direction status of the character
const int CH_RIGHT = 0;
const int CH_LEFT = 1;
const int CH_DOWN = 2;
const int CH_UP = 3;

//monsters const
const int INITIAL_MONSTERS = 15;
const int MAX_MONSTERS_SIMULTANEOUSLY = 30;


//BackGround Type Const
const int EMPTY_GROUND = 00;
const int GRASS_GROUND = 01;
const int SAND_GROUND = 10;
const int RIVER_GROUND = 20;
const int LAKE_GROUND = 25;

//Environment Item Type Const
const int NOTHING_ENV_ITEM = 00;
const int TREE_ENV_ITEM = 01;
const int ROCK_ENV_ITEM = 10;
const int WALL_ENV_ITEM = 20;
const int HOUSE_ENV_ITEM = 30;
const int BRIDGE_ENV_ITEM = 40;


//This variable defined the global game state 1: Initial Menu (future dev), 2: Character Creation/Selection (future dev), 3: Ingame, 4: On Escape menu
extern int GLOBAL_GAME_STATE;

//Logger windows
extern RAGE::Logger P0_Logger;

//To check colission (small beginning of a physical engine^^)
bool check_collision(Rect A, Rect B);
//random function
int random(int min, int max);

#endif
