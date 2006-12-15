#ifndef Render_Engine_HH
#define Render_Engine_HH

#include "Monster_Factory.hh"
#include "Character_Base.hh"
#include "Menus.hh"
#include "Base.hh"

//Engine Class : that render the screen
class Render_Engine : public Engine
{
private:
	//Variable that need to be designed externally
	Character_Base* myCharacter;
	BackGround* myBackGround;
	std::vector<BattleField_Sprite*> BackGround_Sprite_Vector;
	Environment* myEnvironment;
	std::vector<BattleField_Sprite*> Environment_Sprite_Vector;
	Monster_Factory<Monster_Skeleton>* Monster_Factory_Skeleton;
	Monster_Factory<Monster_Worm>* Monster_Factory_Worm;
	Escape_Menu* EscMenu;

	
public:

	//Accessor
	void Set_Character_Base(Character_Base* newCharacterBase)
	{
		myCharacter = newCharacterBase;
	}
	void Set_Esc_Menu(Escape_Menu* newEsc_Menu)
	{
		EscMenu = newEsc_Menu;
	}
	void Set_BackGround(BackGround* newBackGround)
	{
		myBackGround = newBackGround;
	}
	void Set_BackGround_Sprite_Vector(std::vector<BattleField_Sprite*> newBackGround_Sprite_Vector)
	{
		BackGround_Sprite_Vector = newBackGround_Sprite_Vector;
	}
	void Set_Environment(Environment* newEnvironment)
	{
		myEnvironment = newEnvironment;
	}
	void Set_Environment_Sprite_Vector(std::vector<BattleField_Sprite*> newEnvironment_Sprite_Vector)
	{
		Environment_Sprite_Vector = newEnvironment_Sprite_Vector;
	}
	void Set_Monster_Factory_Skeleton(Monster_Factory<Monster_Skeleton>* newMonster_Factory_Skeleton)
	{
		Monster_Factory_Skeleton = newMonster_Factory_Skeleton;
	}
	void Set_Monster_Factory_Worm(Monster_Factory<Monster_Worm>* newMonster_Factory_Worm)
	{
		Monster_Factory_Worm = newMonster_Factory_Worm;
	}

	/****Methods****/
	Render_Engine();
	virtual ~Render_Engine();
	//Methods that is used when resetdisplay is called and not to initialize the engine like is name could let think. Its used to update the engine only when the windows settings change
	bool init(int width, int height);
	//Called when the windows is resized and if the engine need to be updated
	bool resize(int width, int height);
	//Everything that must be calculated before the display of the screen must be defined in this method and then will be called by the mainloop each cycle
	void prerender(void);
	//Draw the display. It will be called after the prerender by the mainloop and at the end of this method the screen will be flipped automatically to show everything
	void render(VideoSurface & screen) const;
	//Will be used by each cycle of mainloop after the draw of the screen. It designed to contain evrytinhg that will be updated after the render of the screen surface
	void postrender(void);
};

#endif
