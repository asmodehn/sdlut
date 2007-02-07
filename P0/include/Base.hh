#ifndef Base_HH
#define Base_HH

#include <ctime>
//#include <string>
#include <vector>
//#include <fstream>
#include <math.h>
#include <stdarg.h> //for methods with an unllimited number of parameters

#include "Sounds.hh"
#include "Ini_Manager.hh"

///*******Usr config*******///
//The initial attributes of the window
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int SCREEN_BPP;

//The current attributes of the window
extern int CURRENT_SCREEN_WIDTH;
extern int CURRENT_SCREEN_HEIGHT;
extern int CURRENT_SCREEN_BPP;

//KEYS 1
extern int UP_1;
extern int DOWN_1;
extern int LEFT_1;
extern int RIGHT_1;
extern int ATTACK_1;
extern int CHANGE_ATTACK_MODE_1;
extern int MENU_CALL_1;
extern int WINDOW_MODE_1;

//Keys 2
extern int UP_2;
extern int DOWN_2;
extern int LEFT_2;
extern int RIGHT_2;
extern int ATTACK_2;
extern int CHANGE_ATTACK_MODE_2;
extern int MENU_CALL_2;
extern int WINDOW_MODE_2;


///*******DeV config*******///
	///***Globals***/
//The dimensions of the level
extern int LEVEL_WIDTH;
extern int LEVEL_HEIGHT;

//The frame rate
extern int FRAMES_PER_SECOND;

//Windows
extern string Window_Name;

//The dimensions of the Character
extern int CH_WIDTH;
extern int CH_HEIGHT;
extern int MO_WIDTH;
extern int MO_HEIGHT;

//Initial Chracter position
extern int CH_INITIAL_X;
extern int CH_INITIAL_Y;

//The direction status of the character
extern int CH_RIGHT;
extern int CH_LEFT;
extern int CH_DOWN;
extern int CH_UP;
extern int CH_RIGHT_DOWN;
extern int CH_LEFT_DOWN;
extern int CH_RIGHT_UP;
extern int CH_LEFT_UP;

//monsters const
extern int INITIAL_MONSTERS;
extern int MAX_MONSTERS_SIMULTANEOUSLY;

//Console const
extern int STATUS_BAR_H;

//Life Bar dims
extern int LIFE_BAR_WIDTH;
extern int LIFE_BAR_HEIGHT;

//Battlefield const
extern int BATF_SPRITE_W;
extern int BATF_SPRITE_H;

//BackGround Type Const
extern int EMPTY_GROUND;
extern int GRASS_GROUND;
extern int SAND_GROUND;
extern int RIVER_GROUND;
extern int LAKE_GROUND;

//Environment Item Type Const
extern int NOTHING_ENV_ITEM;
extern int TREE_ENV_ITEM;
extern int ROCK_ENV_ITEM;
extern int WALL_ENV_ITEM;
extern int HOUSE_ENV_ITEM;
extern int BRIDGE_ENV_ITEM;


//Monsters ID which defined type of monsters (used in coordination with battlefield cutting)
enum Monsters_Type {Humanoid = 1, Worm = 2};

//This variable defined the global game state 1: Initial Menu (future dev), 2: Character Creation/Selection (future dev), 3: Ingame, 4: On Escape menu, 5: Victory
extern int GLOBAL_GAME_STATE;

//Logger windows
extern RAGE::Logger P0_Logger;
extern string Log_Name;

	///***Animations***///
extern long PLAYER_MOVE_ANIMATION_INTERVAL;
extern long PLAYER_SWORD_ATTACK_ANIMATION_INTERVAL;
extern long PLAYER_BOW_ATTACK_ANIMATION_INTERVAL;
extern long PLAYER_ARROW_MOVE_ANIMATION_INTERVAL;

extern int PLAYER_SWORD_ATTACK_ANIMATION_FRAME;
extern int PLAYER_BOW_ATTACK_ANIMATION_FRAME;
extern int PLAYER_ARROW_ATTACK_ANIMATION_FRAME;

	///***Daemons***///
extern long MONSTERS_MOVEMENT_INTERVAL;
extern long MONSTERS_GENERATION_INTERVAL;

///*******Base variable & methods*******///
extern int ALiVE_MONSTERS;
extern int KiLLED_MONSTERS;
extern int FiNiSH_TiME;

//Define configuration from files or set the default config
bool Set_Config();

//To check colission (small beginning of a physical engine^^)
bool check_collision(Rect A, Rect B);

//random function
int random(int min, int max);

//Convert Int To String
std::string Int_To_String(int to_convert);

//Style the time to "Xd Xh Xmin Xs"
std::string Time_Style(int time);

#endif
