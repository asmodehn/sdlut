#include "Sprite.hh"

//constructor : just pass the file containing the sprite
Sprite::Sprite(const std::string & filename)
{
	//TODO : manages sprites usong SDLSurfaceFactory properly...
	//HAVE TO FIND OUT HOW....
	//_graphic=SDLSurfaceFactory::createRGBSurface(filename);
	
}
//copy constructor : just pass the sprite to use as model
Sprite::Sprite(const Sprite & model)
{
	//_graphic=SDLSurfaceFactory::clone(model._graphic);
}
	
Sprite::~Sprite()
{
	//should be carefull 
	delete _graphic;
}