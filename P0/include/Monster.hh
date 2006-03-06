#ifndef Monster_HH
#define Monster_HH

#include "Base.hh"

//The Monster
class Monster
{
    private:
    //The X and Y offsets of the Monster
    int x, y;

	//Display Surface
	SDL_Surface *screen;

	//Monster Tile
	SDL_Surface *_monsters_list;

	//Monster Tile Clip
	SDL_Rect _monster[1];

	//The velocity of the Monster
    int xVel, yVel;
    
	public:
	//The collision boxes of the Monster
    SDL_Rect collision_box;

	//Default construtor
	Monster();

    //Constructor that initialize the variables
    Monster(int X, int Y, SDL_Surface *screen);

	//Copy construtor
	Monster(const Monster& ToCopy);

	//Destructor
	~Monster();

	//Surface Initialiation
	bool Init();
    
    //Move the Monster and check collision with the collision box of the character in parameter
    void move(SDL_Rect &_CharacterCollisionbox);
    
    //Shows the Monster movement on the screen
    void move_animation( SDL_Rect camera);
};

#endif

