#ifndef INTERFACE3D_HH
#define INTERFACE3D_HH

/*******************************************************************************
 * Interface with other systems
 ******************************************************************************/

//Classes d'interface avec un moteur 3D...
// a voir si cette classe doit etre la scene, la camera ou les 2
//(cf UI interface)
#include "SDLConfig.hh"

#ifdef HAVE_OPENGL

class Interface3D
{
	public:
	virtual void render(void) const;
	virtual bool init(int width, int height);
	virtual bool resize(int width, int height);
};

class Object3D
{
	public:
	virtual void move()=0;
};
#endif

//Classes d'interface avec un moteur 2D
//Meme probleme que precedemment

#endif //INTERFACE3D_HH
