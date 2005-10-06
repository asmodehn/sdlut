#ifndef SPRITE_HH
#define SPRITE_HH

#include "Config.hh"

#include "GraphicElement.hh"

class Sprite : public GraphicElement
{
	int refnumber;
	
  public:
	//constructor : just pass the file containing the sprite
	Sprite(const std::string & filename);
	//copy constructor : just pass the sprite to use as model
	Sprite(const Sprite & model);
	
	~Sprite();
	
};


#endif
