#ifndef GRAPHICELEMENT_HH
#define GRAPHICELEMENT_HH

#include "Config.hh"

#include "Math2D.hh"



class GraphicElement
{
	
  protected : 
	
	//implementing a sort of dependency tree for GraphicElements :
	
	//to manage calls and UPWARDS dependencies in the tree
	GraphicElement * _referent;
	unsigned int _referentID;
	
	
	//methods to handle the Graphic referent calls(scene tree from nodes to root)
  virtual bool setreferent(GraphicElement * referent);
  void delreferent(void);
		
	//to manage calls and DOWNWARDS dependencies in the tree
	//TODO : think about KDTree to handle that more efficiently... LATER
  std::vector<GraphicElement * >_referee;
	std::vector<Vector2>_position;


  //to update the referee position
  bool translate(unsigned int index, const Vector2& deltap);
  
  
  
  
  
  
	public :
  
  //default constructor
  GraphicElement( );
  //copy constructor
  GraphicElement( const GraphicElement & ge );
  //Default destructor
  virtual ~GraphicElement(void);
  
  
//to update my position (calling _referent->move(int, const Vector2&) )
	bool move(const Vector2& deltap);
  
  //methods to handle the Graphic referee calls(scene tree from root to nodes)
  virtual unsigned int add(GraphicElement * referee,const Vector2& position = Vector2 (0.0,0.0));
  virtual bool update(unsigned int index, GraphicElement * referee,const Vector2& position = Vector2 (0.0,0.0));
  void remove(unsigned int index);
	
  void render(unsigned int myPixCenterX, unsigned int myPixCenterY);

};


#endif
