#include "Layer.hh"

Layer::Layer()
{
	
}
	
Layer::~Layer()
{
	
}

unsigned int Layer::add(Sprite * sprite, const Vector2& position)
{
  return GraphicElement::add(sprite,position);
}

bool Layer::update(unsigned int index,  Sprite * sprite, const Vector2& position)
{
  return GraphicElement::update(index,sprite,position);
}

