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
	Player* myPlayer;
	NPCs* myNPC; //The NPC Definition
	BackGround* myBackGround;
	Environment* myEnvironment;
	Monster_Factory<Monster_Skeleton>* Monster_Factory_Skeleton;
	Monster_Factory<Monster_Worm>* Monster_Factory_Worm;
	Escape_Menu* myEsc_Menu;
	Victory_Screen* myVictory_Screen;
	KeyboardInput* myKeyboardInput;

	
public:
/****Def****/
	Render_Engine(Player* &myPlayer, NPCs* &myNPC, BackGround* &myBackGround, Environment* &myEnvironment, Monster_Factory<Monster_Skeleton>* &Monster_Factory_Skeleton,
				Monster_Factory<Monster_Worm>* &Monster_Factory_Worm, Escape_Menu* &myEsc_Menu, Victory_Screen* &myVictory_Screen, KeyboardInput* &myKeyboardInput
				);
	~Render_Engine();

/****Methods****/
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
