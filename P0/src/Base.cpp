#include "Base.hh"

//Logger
RAGE::Logger P0_Logger("P0 Log");

//Default To solve extern's linker pb
int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600, SCREEN_BPP = 32, CURRENT_SCREEN_WIDTH = 800, CURRENT_SCREEN_HEIGHT = 600, CURRENT_SCREEN_BPP = 32, 
	GLOBAL_GAME_STATE = 3;
int UP_1 = 0, DOWN_1 = 0, LEFT_1 = 0, RIGHT_1 = 0, ATTACK_1 = 0, CHANGE_ATTACK_MODE_1 = 0, MENU_CALL_1 = 0, WINDOW_MODE_1 = 0;
int UP_2 = 0, DOWN_2 = 0, LEFT_2 = 0, RIGHT_2 = 0, ATTACK_2 = 0, CHANGE_ATTACK_MODE_2 = 0, MENU_CALL_2 = 0, WINDOW_MODE_2 = 0;

bool Set_Config()
{
try { //error management

	//User config
	std::ifstream fi("Config.ini") ;
	if (fi.fail()) //File does not exist so create it with default values
		Ini_Manager::Write_New_Ini_File("Config.ini",
		"#screen def\nSCREEN_WIDTH = 800\nSCREEN_HEIGHT = 600\nSCREEN_BPP = 32\n\n###KEYS NAMES ARE ALL CAPITALIZED EXCEPT LETTERS NAME###\n#Keys 1\nUP_1 = KKP8\nDOWN_1 = KKP5\nLEFT_1 = KKP7\nRIGHT_1 = KKP9\nATTACK_1 = KKPDIVIDE\nCHANGE_ATTACK_MODE_1 = KKPMULTIPLY\nMENU_CALL_1 = KESCAPE\nWINDOW_MODE_1 = KF11\n\n#Keys 2\nUP_2 = KUP\nDOWN_2 = KDOWN\nLEFT_2 = KLEFT\nRIGHT_2 = KRIGHT\nATTACK_2 = KRCTRL\nCHANGE_ATTACK_MODE_2 = KRSHIFT\nMENU_CALL_2 = \nWINDOW_MODE_2 = \n"
			);
	fi.close();

	std::stringstream( Ini_Manager::Get_Option_String("Config.ini", "SCREEN_WIDTH") ) >> (const int)SCREEN_WIDTH;
	std::stringstream( Ini_Manager::Get_Option_String("Config.ini", "SCREEN_HEIGHT") ) >> (const int)SCREEN_HEIGHT;
	std::stringstream( Ini_Manager::Get_Option_String("Config.ini", "SCREEN_BPP") ) >> (const int)SCREEN_BPP;

	UP_1 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "UP_1") );
	DOWN_1 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "DOWN_1") );
	LEFT_1 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "LEFT_1") );
	RIGHT_1 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "RIGHT_1") );
	ATTACK_1 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "ATTACK_1") );
	CHANGE_ATTACK_MODE_1 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "CHANGE_ATTACK_MODE_1") );
	MENU_CALL_1 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "MENU_CALL_1") );
	WINDOW_MODE_1 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "WINDOW_MODE_1") );
	
	UP_2 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "UP_2") );
	DOWN_2 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "DOWN_2") );
	LEFT_2 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "LEFT_2") );
	RIGHT_2 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "RIGHT_2") );
	ATTACK_2 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "ATTACK_2") );
	CHANGE_ATTACK_MODE_2 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "CHANGE_ATTACK_MODE_2") );
	MENU_CALL_2 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "MENU_CALL_2") );
	WINDOW_MODE_2 = Ini_Manager::Get_Key_Value_From_Key_Name( Ini_Manager::Get_Option_String("Config.ini", "WINDOW_MODE_2") );

	//Dev config

	//we begin the game as 'ingame' state
	GLOBAL_GAME_STATE = 3;

	//At the beginning the window as the initial attributes
	CURRENT_SCREEN_WIDTH = SCREEN_WIDTH;
	CURRENT_SCREEN_HEIGHT = SCREEN_HEIGHT;
	CURRENT_SCREEN_BPP = SCREEN_BPP;


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
