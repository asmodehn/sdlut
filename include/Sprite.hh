#ifndef SPRITE_HH
#define SPRITE_HH

#include "Config.hh"

#include "GraphicElement.hh"

class Sprite : public GraphicElement //TODO : NEED to prevent access to base class methods handling referee...
{
  static SDL::SurfaceFactory * _graphicMaster;
	static unsigned int _referencecount;
	
	unsigned int _graphicIndex;
	
  public:
	//constructor : just pass the file containing the sprite
	Sprite(const std::string & filename);
	//copy constructor : just pass the sprite to use as model
	Sprite(const Sprite & model);
	
	~Sprite();
	
  //to use the size
	SDL::Rect getSize(void);
	
	//this one predraw a bounding box and axis on top of _graphic.
	// TO DO AND IMPROVE
	bool drawBox(void) const;
	
	
 //to update my position (calling _referent->move(int, const Vector2&) )
	bool move(const Vector2& deltap);
	
	//TODO
	void render(unsigned int myPixCenterX, unsigned int myPixCenterY);
};


#endif
