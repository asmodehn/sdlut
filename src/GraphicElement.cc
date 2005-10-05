#include "GraphicElement.hh"

GraphicElement::GraphicElement( const Vector2& position, const Vector2& halfSize)
:_position(position),_halfSize(halfSize)
{
}

GraphicElement::GraphicElement( const GraphicElement & ge )
:_position(ge._position),_halfSize(ge._halfSize)
{
}
GraphicElement::~GraphicElement (void)
{
}

Vector2 GraphicElement::getPosition(void)
{
	return _position;
}

void GraphicElement::setPosition(const Vector2& p)
{
	_position = p;
}

bool GraphicElement::updatePosition(const Vector2& deltap)
{
	_position += deltap;
	return true;
}

Vector2 GraphicElement::getHalfSize(void)
{
	return _halfSize;
}

Vector2 GraphicElement::getSize(void)
{
	return 2 * _halfSize;
}

void GraphicElement::setSize(const Vector2& s)
{
	_halfSize = s / 2;
}

void GraphicElement::setHalfSize(const Vector2& hs)
{
	_halfSize = hs;
}

//these two might be derivated... and if so make some test about how to update the position
bool GraphicElement::updateSize(const Vector2& deltas)
{
	_halfSize+= deltas / 2;
	return true;
}

bool GraphicElement::updateHalfSize(const Vector2& deltahs)
{
	_halfSize+= deltahs;
	return true;
}

bool GraphicElement::predraw(void) const
{
	//draw square
	
	//draw X Y axis (before any transformation)
}


