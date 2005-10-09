#ifndef LAYER_HH
#define LAYER_HH

#include "Config.hh"

#include "GraphicElement.hh"

#include "Sprite.hh"

class Layer : public GraphicElement
{
	
  public:
	Layer();
	
	~Layer();
	
  unsigned int add(Sprite * sprite, const Vector2& position = Vector2 (0.0,0.0));
  bool update(unsigned int index, Sprite * sprite, const Vector2& position = Vector2 (0.0,0.0));
	
};


#endif
