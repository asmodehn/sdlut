#ifndef Render_Engine_HH
#define Render_Engine_HH

//#include "Monster_Factory.hh"
//#include "Player_Base.hh"
//#include "Menus.hh"
//#include "Base.hh"
#include "Input_Management.hh"

//Engine Class : that render the screen
class Render_Engine : public Engine
{
private:
	//Variable that need to be designed externally
	Player_Base* myPlayer;
	BackGround* myBackGround;
	std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector;
	Environment* myEnvironment;
	std::vector<BattleField_Sprite*>* Environment_Sprite_Vector;
	Monster_Factory<Monster_Skeleton>* Monster_Factory_Skeleton;
	Monster_Factory<Monster_Worm>* Monster_Factory_Worm;
	Escape_Menu* EscMenu;
	Victory_Screen* VictoryScreen;
	KeyboardInput* MyKeyboard;

	
public:

	//Accessor
	inline void Set_Player_Base(Player_Base* newPlayerBase)
	{
		myPlayer = newPlayerBase;
	}
	/*inline void Set_Global_Player_Vector(std::vector< std::vector<Character_Base*> *>* newGlobal_Player_Vector)
	{
		Global_Player_Vector = newGlobal_Player_Vector;
	}*/
	inline void Set_Esc_Menu(Escape_Menu* newEsc_Menu)
	{
		EscMenu = newEsc_Menu;
	}
	inline void Set_Victory_Screen(Victory_Screen* newVictory_Screen)
	{
		VictoryScreen = newVictory_Screen;
	}
	inline void Set_BackGround(BackGround* newBackGround)
	{
		myBackGround = newBackGround;
	}
	inline void Set_BackGround_Sprite_Vector(std::vector<BattleField_Sprite*>* newBackGround_Sprite_Vector)
	{
		BackGround_Sprite_Vector = newBackGround_Sprite_Vector;
	}
	inline void Set_Environment(Environment* newEnvironment)
	{
		myEnvironment = newEnvironment;
	}
	inline void Set_Environment_Sprite_Vector(std::vector<BattleField_Sprite*>* newEnvironment_Sprite_Vector)
	{
		Environment_Sprite_Vector = newEnvironment_Sprite_Vector;
	}
	inline void Set_Monster_Factory_Skeleton(Monster_Factory<Monster_Skeleton>* newMonster_Factory_Skeleton)
	{
		Monster_Factory_Skeleton = newMonster_Factory_Skeleton;
	}
	inline void Set_Monster_Factory_Worm(Monster_Factory<Monster_Worm>* newMonster_Factory_Worm)
	{
		Monster_Factory_Worm = newMonster_Factory_Worm;
	}
	inline void Set_Keyboard(KeyboardInput* newKeyboard)
	{
		MyKeyboard = newKeyboard;
	}

	/****Methods****/
	Render_Engine();

	//Methods that is used when resetdisplay is called and not to initialize the engine like is name could let think. Its used to update the engine only when the windows settings change
	bool init(int width, int height);
	//Called when the windows is resized and if the engine need to be updated
	bool resize(int width, int height);
	//Everything that must be calculated before the display of the screen must be defined in this method and then will be called by the mainloop each cycle
	void prerender(unsigned long deltaticks);
	//Draw the display. It will be called after the prerender by the mainloop and at the end of this method the screen will be flipped automatically to show everything
	void render(VideoSurface & screen) const;
	//Will be used by each cycle of mainloop after the draw of the screen. It designed to contain evrytinhg that will be updated after the render of the screen surface
	void postrender(void);
};

#endif
