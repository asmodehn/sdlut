#include "Base.hh"

//globals
int ALiVE_MONSTERS = 0;
int KiLLED_MONSTERS = 0;
int FiNiSH_TiME = 0;

//Default config def to solve extern's linker pb
	//Default user Cfg
int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600, SCREEN_BPP = 16, CURRENT_SCREEN_WIDTH = 800, CURRENT_SCREEN_HEIGHT = 600, CURRENT_SCREEN_BPP = 32;
int UP_1 = 0, DOWN_1 = 0, LEFT_1 = 0, RIGHT_1 = 0, ATTACK_1 = 0, CHANGE_ATTACK_MODE_1 = 0, MENU_CALL_1 = 0, WINDOW_MODE_1 = 0;
int UP_2 = 0, DOWN_2 = 0, LEFT_2 = 0, RIGHT_2 = 0, ATTACK_2 = 0, CHANGE_ATTACK_MODE_2 = 0, MENU_CALL_2 = 0, WINDOW_MODE_2 = 0;

	//Default dev cfg
int LEVEL_WIDTH = 0, LEVEL_HEIGHT = 0;
int FRAMES_PER_SECOND = 0;
int CH_WIDTH = 0, CH_HEIGHT = 0, MO_WIDTH = 0, MO_HEIGHT = 0;
int CH_INITIAL_X = 0, CH_INITIAL_Y = 0;
int CH_RIGHT = 0, CH_LEFT = 0, CH_DOWN = 0, CH_UP = 0, CH_RIGHT_DOWN = 0, CH_LEFT_DOWN = 0, CH_RIGHT_UP = 0, CH_LEFT_UP = 0;
int INITIAL_MONSTERS = 0, MAX_MONSTERS_SIMULTANEOUSLY = 0;
int LIFE_BAR_WIDTH = 0, LIFE_BAR_HEIGHT = 0;
int STATUS_BAR_H = 0;
int BATF_SPRITE_W = 0, BATF_SPRITE_H = 0;
int EMPTY_GROUND = 0, GRASS_GROUND = 0, SAND_GROUND = 0, RIVER_GROUND = 0, LAKE_GROUND = 0;
int NOTHING_ENV_ITEM = 0, TREE_ENV_ITEM = 0, ROCK_ENV_ITEM = 0, WALL_ENV_ITEM = 0, HOUSE_ENV_ITEM = 0, BRIDGE_ENV_ITEM = 0;
//int Humanoid = 0, Worm = 0;
int	GLOBAL_GAME_STATE = 3;
RAGE::Logger P0_Logger("P0:"); //prefix
string Log_Name = "P0.Log";
string Window_Name = "P0";

	//Anim dev config
long PLAYER_MOVE_ANIMATION_INTERVAL = 0, PLAYER_SWORD_ATTACK_ANIMATION_INTERVAL = 0, PLAYER_BOW_ATTACK_ANIMATION_INTERVAL = 0, PLAYER_ARROW_MOVE_ANIMATION_INTERVAL = 0;
int PLAYER_SWORD_ATTACK_ANIMATION_FRAME = 0, PLAYER_BOW_ATTACK_ANIMATION_FRAME = 0, PLAYER_ARROW_ATTACK_ANIMATION_FRAME = 0;

	//Daemons Dev Config
long MONSTERS_MOVEMENT_INTERVAL = 0, MONSTERS_GENERATION_INTERVAL = 0;

bool Set_Config()
{
try { //error management

	///*******User config*******///
	std::ifstream fi_usr("Config.ini") ;
	if (fi_usr.fail()) //File does not exist so create it with default values
		Ini_Manager::Write_New_Ini_File("Config.ini",
		"#screen def\nSCREEN_WIDTH = 800\nSCREEN_HEIGHT = 600\nSCREEN_BPP = 16\n\n###KEYS NAMES ARE ALL CAPITALIZED EXCEPT LETTERS NAME###\n#Keys 1\nUP_1 = KKP8\nDOWN_1 = KKP5\nLEFT_1 = KKP7\nRIGHT_1 = KKP9\nATTACK_1 = KKPDIVIDE\nCHANGE_ATTACK_MODE_1 = KKPMULTIPLY\nMENU_CALL_1 = KESCAPE\nWINDOW_MODE_1 = KF11\n\n#Keys 2\nUP_2 = KUP\nDOWN_2 = KDOWN\nLEFT_2 = KLEFT\nRIGHT_2 = KRIGHT\nATTACK_2 = KRCTRL\nCHANGE_ATTACK_MODE_2 = KRSHIFT\nMENU_CALL_2 = \nWINDOW_MODE_2 = \n"
			);
	fi_usr.close();

		//Windows
	std::stringstream( Ini_Manager::Get_Option_String("Config.ini", "SCREEN_WIDTH") ) >> (const int)SCREEN_WIDTH;
	std::stringstream( Ini_Manager::Get_Option_String("Config.ini", "SCREEN_HEIGHT") ) >> (const int)SCREEN_HEIGHT;
	std::stringstream( Ini_Manager::Get_Option_String("Config.ini", "SCREEN_BPP") ) >> (const int)SCREEN_BPP;

		//At the beginning the window as the initial attributes
	CURRENT_SCREEN_WIDTH = SCREEN_WIDTH;
	CURRENT_SCREEN_HEIGHT = SCREEN_HEIGHT;
	CURRENT_SCREEN_BPP = SCREEN_BPP;

		//Keys #1
	UP_1 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "UP_1") );
	DOWN_1 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "DOWN_1") );
	LEFT_1 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "LEFT_1") );
	RIGHT_1 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "RIGHT_1") );
	ATTACK_1 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "ATTACK_1") );
	CHANGE_ATTACK_MODE_1 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "CHANGE_ATTACK_MODE_1") );
	MENU_CALL_1 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "MENU_CALL_1") );
	WINDOW_MODE_1 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "WINDOW_MODE_1") );
		//Keys #2
	UP_2 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "UP_2") );
	DOWN_2 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "DOWN_2") );
	LEFT_2 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "LEFT_2") );
	RIGHT_2 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "RIGHT_2") );
	ATTACK_2 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "ATTACK_2") );
	CHANGE_ATTACK_MODE_2 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "CHANGE_ATTACK_MODE_2") );
	MENU_CALL_2 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "MENU_CALL_2") );
	WINDOW_MODE_2 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "WINDOW_MODE_2") );

	///*******DeV config*******///
		///***Global***///
	std::ifstream fi_dev("Config/Dev_Config.ini") ;
	if (fi_dev.fail()) //File does not exist so create it with default values
		Ini_Manager::Write_New_Ini_File("Config/Dev_Config.ini",
		"#frame rate\nFRAMES_PER_SECOND = 60\n\n#Windows\nWindow_Name = \"Project 0 - 2D v0.03\"\n\n#level dimensions\nLEVEL_WIDTH = 1280\nLEVEL_HEIGHT = 1280\n\n#Characters sprite dimensions\nCH_WIDTH = 32\nCH_HEIGHT = 32\nMO_WIDTH = 32\nMO_HEIGHT = 32\n\n#character initial position\nCH_INITIAL_X = 192\nCH_INITIAL_Y = 224\n\n#Directions representation\nCH_RIGHT = 0\nCH_RIGHT_DOWN = 1\nCH_DOWN = 2\nCH_LEFT_DOWN = 3\nCH_LEFT = 4\nCH_LEFT_UP = 5\nCH_UP = 6\nCH_RIGHT_UP = 7\n\n#monsters level const\nINITIAL_MONSTERS = 15\nMAX_MONSTERS_SIMULTANEOUSLY = 30\n\n#status bar dimension\nSTATUS_BAR_H = 32\n\n#Life Bar dimensions\nLIFE_BAR_WIDTH = 32\nLIFE_BAR_HEIGHT = 6\n\n#Battlefield sprite dimensions\nBATF_SPRITE_W = 32\nBATF_SPRITE_H = 32\n\n#BackGround Types\nEMPTY_GROUND = 00\nGRASS_GROUND = 01\nSAND_GROUND = 10\nRIVER_GROUND = 20\nLAKE_GROUND = 25\n\n#Environment Types\nNOTHING_ENV_ITEM = 00;\nTREE_ENV_ITEM = 01;\nROCK_ENV_ITEM = 10;\nWALL_ENV_ITEM = 20;\nHOUSE_ENV_ITEM = 30;\nBRIDGE_ENV_ITEM = 40;\n\n#State of the game at the begining: 'ingame' state\nGLOBAL_GAME_STATE = 3\n\n#Name of the log file\nLog_Name = \"P0_Log.log\""
			);
	fi_dev.close();
	
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "FRAMES_PER_SECOND") ) >> (const int)FRAMES_PER_SECOND;
	
	Window_Name = Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "Window_Name");

	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "LEVEL_WIDTH") ) >> (const int)LEVEL_WIDTH;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "LEVEL_HEIGHT") ) >> (const int)LEVEL_HEIGHT;
	
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "CH_WIDTH") ) >> (const int)CH_WIDTH;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "CH_HEIGHT") ) >> (const int)CH_HEIGHT;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "MO_WIDTH") ) >> (const int)MO_WIDTH;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "MO_HEIGHT") ) >> (const int)MO_HEIGHT;
	
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "CH_INITIAL_X") ) >> (const int)CH_INITIAL_X;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "CH_INITIAL_Y") ) >> (const int)CH_INITIAL_Y;
	
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "CH_RIGHT") ) >> (const int)CH_RIGHT;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "CH_RIGHT_DOWN") ) >> (const int)CH_RIGHT_DOWN;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "CH_DOWN") ) >> (const int)CH_DOWN;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "CH_LEFT_DOWN") ) >> (const int)CH_LEFT_DOWN;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "CH_LEFT") ) >> (const int)CH_LEFT;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "CH_LEFT_UP") ) >> (const int)CH_LEFT_UP;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "CH_UP") ) >> (const int)CH_UP;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "CH_RIGHT_UP") ) >> (const int)CH_RIGHT_UP;
	
	
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "INITIAL_MONSTERS") ) >> (const int)INITIAL_MONSTERS;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "MAX_MONSTERS_SIMULTANEOUSLY") ) >> (const int)MAX_MONSTERS_SIMULTANEOUSLY;
	
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "STATUS_BAR_H") ) >> (const int)STATUS_BAR_H;

	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "LIFE_BAR_WIDTH") ) >> (const int)LIFE_BAR_WIDTH;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "LIFE_BAR_HEIGHT") ) >> (const int)LIFE_BAR_HEIGHT;
	
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "BATF_SPRITE_W") ) >> (const int)BATF_SPRITE_W;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "BATF_SPRITE_H") ) >> (const int)BATF_SPRITE_H;
	
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "EMPTY_GROUND") ) >> (const int)EMPTY_GROUND;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "GRASS_GROUND") ) >> (const int)GRASS_GROUND;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "SAND_GROUND") ) >> (const int)SAND_GROUND;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "RIVER_GROUND") ) >> (const int)RIVER_GROUND;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "LAKE_GROUND") ) >> (const int)LAKE_GROUND;
	
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "NOTHING_ENV_ITEM") ) >> (const int)NOTHING_ENV_ITEM;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "TREE_ENV_ITEM") ) >> (const int)TREE_ENV_ITEM;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "ROCK_ENV_ITEM") ) >> (const int)ROCK_ENV_ITEM;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "WALL_ENV_ITEM") ) >> (const int)WALL_ENV_ITEM;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "HOUSE_ENV_ITEM") ) >> (const int)HOUSE_ENV_ITEM;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "BRIDGE_ENV_ITEM") ) >> (const int)BRIDGE_ENV_ITEM;
	
	//std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "Humanoid") ) >> (const int)Humanoid;
	//std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "Worm") ) >> (const int)Worm;

	std::stringstream( Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "GLOBAL_GAME_STATE") ) >> (const int)GLOBAL_GAME_STATE;

	Log_Name = Ini_Manager::Get_Option_String("Config/Dev_Config.ini", "Log_Name");
	//define log filename
	P0_Logger.enableFileLog(Log_Name);

		
		///***Animations***///
	std::ifstream fi_anim("Config/Anim_Config.ini") ;
	if (fi_anim.fail()) //File does not exist so create it with default values
		Ini_Manager::Write_New_Ini_File("Config/Anim_Config.ini",
		"#Animations timers (ms)\nPLAYER_MOVE_ANIMATION_INTERVAL = 150\nPLAYER_SWORD_ATTACK_ANIMATION_INTERVAL = 130\nPLAYER_BOW_ATTACK_ANIMATION_INTERVAL = 130\nPLAYER_ARROW_MOVE_ANIMATION_INTERVAL = 75\n\n#Animations frame numbers\nPLAYER_SWORD_ATTACK_ANIMATION_FRAME = 3\nPLAYER_BOW_ATTACK_ANIMATION_FRAME = 3\nPLAYER_ARROW_ATTACK_ANIMATION_FRAME = 1\n"
			);
	fi_anim.close();

	std::stringstream( Ini_Manager::Get_Option_String("Config/Anim_Config.ini", "PLAYER_MOVE_ANIMATION_INTERVAL") ) >> (const long)PLAYER_MOVE_ANIMATION_INTERVAL;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Anim_Config.ini", "PLAYER_SWORD_ATTACK_ANIMATION_INTERVAL") ) >> (const long)PLAYER_SWORD_ATTACK_ANIMATION_INTERVAL;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Anim_Config.ini", "PLAYER_BOW_ATTACK_ANIMATION_INTERVAL") ) >> (const long)PLAYER_BOW_ATTACK_ANIMATION_INTERVAL;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Anim_Config.ini", "PLAYER_ARROW_MOVE_ANIMATION_INTERVAL") ) >> (const long)PLAYER_ARROW_MOVE_ANIMATION_INTERVAL;

	std::stringstream( Ini_Manager::Get_Option_String("Config/Anim_Config.ini", "PLAYER_SWORD_ATTACK_ANIMATION_FRAME") ) >> (const int)PLAYER_SWORD_ATTACK_ANIMATION_FRAME;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Anim_Config.ini", "PLAYER_BOW_ATTACK_ANIMATION_FRAME") ) >> (const int)PLAYER_BOW_ATTACK_ANIMATION_FRAME;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Anim_Config.ini", "PLAYER_ARROW_ATTACK_ANIMATION_FRAME") ) >> (const int)PLAYER_ARROW_ATTACK_ANIMATION_FRAME;
	
		///***Deamons***///
	std::ifstream fi_daemons("Config/Daemons_Config.ini") ;
	if (fi_daemons.fail()) //File does not exist so create it with default values
		Ini_Manager::Write_New_Ini_File("Config/Daemons_Config.ini",
		"#Daemons Intervals\nMONSTERS_MOVEMENT_INTERVAL = 1000\nMONSTERS_GENERATION_INTERVAL = 20000"
			);
	fi_daemons.close();

	std::stringstream( Ini_Manager::Get_Option_String("Config/Daemons_Config.ini", "MONSTERS_MOVEMENT_INTERVAL") ) >> (const long)MONSTERS_MOVEMENT_INTERVAL;
	std::stringstream( Ini_Manager::Get_Option_String("Config/Daemons_Config.ini", "MONSTERS_GENERATION_INTERVAL") ) >> (const long)MONSTERS_GENERATION_INTERVAL;

	


	return true; //no error

} catch (...) {
    return false;
}
}

//To check colission (small beginning of a physical engine^^)
bool check_collision(Rect A, Rect B)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.getx();
    rightA = A.getx() + A.getw();
    topA = A.gety();
    bottomA = A.gety() + A.geth();
        
    //Calculate the sides of rect B
    leftB = B.getx();
    rightB = B.getx() + B.getw();
    topB = B.gety();
    bottomB = B.gety() + B.geth();
            
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}
//random function between min and max
int random(int min, int max)
{
	//srand( (unsigned)time( NULL ) );
	return min + (rand()%(max+1-min));
}

std::string Int_To_String(int to_convert)
{
	std::stringstream s;
    if (s << to_convert) // conversion worked
        return s.str();

	//failed
	return NULL;
}

//Style the time to "Xd Xh Xmin Xs"
std::string Time_Style(int time)
{
	int day=0, hour=0, minute=0, second=0;
	
	if (time < 60)
	{
		return Int_To_String(time) + "s";
	} else if ( (time >= 60) && (time < 3600) ) 
	{
		minute = (int)(time / 60);
		second = time - (minute*60);
		return Int_To_String(minute) + "mn " + Int_To_String(second) + "s";
	} else if ( (time >=3600) && (time < 86400) )
	{
		hour = (int)(time / 3600);
		minute = (int)( (time - (hour*3600))/60 );
		second = time - (hour*3600) - (minute*60);
		return Int_To_String(hour) + "hr " + Int_To_String(minute) + "mn " + Int_To_String(second) + "s";
	} else if (time >=86400)
	{
		day = (int)(time / 86400);
		hour = (int)( (time - (day*86400))/3600);
		minute = (int) ( (time -(day*86400) -(hour*3600))/60);
		second = time -(day*86400) -(hour*3600) -(minute*60);
		return Int_To_String(day) + "day " + Int_To_String(hour) + "hr " + Int_To_String(minute) + "mn " + Int_To_String(second) + "s";

	}

	return NULL; //error
}
