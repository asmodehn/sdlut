#ifndef GRAPHICELEMENT_HH
#define GRAPHICELEMENT_HH

#include "AML_config.hh"

#include "Math2D.hh"

class GraphicElement
{
	protected : 
	
	Vector2 _position;
	
	Vector2 _halfSize;
	
	
	public :
  
  GraphicElement( const Vector2& position = Vector2( 0.0 , 0.0 ) , const Vector2& halfSize = Vector2( 0.0 , 0.0 ) );
  GraphicElement( const GraphicElement & ge );
  virtual ~GraphicElement(void);
  
  //position manipulators
  Vector2 getPosition(void);
  void setPosition(const Vector2& p);
  //this one might be derivated... and if so make some test about the possibility to update the position
  virtual bool updatePosition(const Vector2& deltap);
	
	Vector2 getHalfSize(void);
	Vector2 getSize(void);
	void setSize(const Vector2& s);
	void setHalfSize(const Vector2& hs);
	//these two might be derivated... and if so make some test about the possibility to update the position
  virtual bool updateSize(const Vector2& deltas);
  virtual bool updateHalfSize(const Vector2& deltahs);
	
};


#endif
