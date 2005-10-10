#include "GraphicElement.hh"

GraphicElement::GraphicElement( )
{
}

GraphicElement::GraphicElement( const GraphicElement & ge )
{
}

GraphicElement::~GraphicElement (void)
{
}

bool GraphicElement::setreferent(GraphicElement * referent)
{
	_referent=referent;
	return true;
}

void GraphicElement::delreferent(void)
{
	_referent=NULL;
}

//methods to handle the Graphic referee (scene tree from root to nodes)
//virtual or not ???
unsigned int GraphicElement::add(GraphicElement * referee, const Vector2& position)
{
	_referee.push_back(referee);
	_position.push_back(position);
	referee->setreferent(this);
	return _referee.size()-1;
}

bool GraphicElement::update(unsigned int index, GraphicElement * referee, const Vector2& position)
{
	_referee.at(index)->delreferent();
	_referee.at(index)=referee;
	_position.at(index)=position;
	referee->setreferent(this);
	return true;
}

void GraphicElement::remove(unsigned int index)
{
	_referee.at(index)->delreferent();
	std::vector<GraphicElement*>::iterator it=_referee.begin()+index;
	_referee.erase(it);
}

//to update the position
bool GraphicElement::translate(unsigned int index, const Vector2& deltap)
{
	_position.at(index)+=deltap;
	return true;
}


bool GraphicElement::move(const Vector2& deltap)
{
	bool res=false;
	//only if we have a referent
	if (_referent!=NULL)
    res=_referent->translate(_referentID,deltap);
	return res;
}

void GraphicElement::render(unsigned int myPixCenterX, unsigned int myPixCenterY)
{
	for ( unsigned int i=0;  i<_referee.size(); i++ )
	{
		Vector2 pos=_position[i];
		std::cerr << "calling _referee[" <<i <<"]->render(" << myPixCenterX-static_cast<int>(pos.x())<< "," <<myPixCenterY-static_cast<int>(pos.y()) <<")"<<std::endl;
		_referee[i]->render(myPixCenterX-static_cast<int>(pos.x()),myPixCenterY-static_cast<int>(pos.y()));
  }
}


