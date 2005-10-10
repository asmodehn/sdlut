#include "Sprite.hh"

SDLSurfaceFactory * Sprite::_graphicMaster=NULL;

unsigned int Sprite::_referencecount=0;

//constructor : just pass the file containing the sprite
Sprite::Sprite(const std::string & filename)
{
	if (_graphicMaster==NULL || _referencecount == 0)
    _graphicMaster=new SDLSurfaceFactory();
  _referencecount++;
  //creating the surface in memory
  _graphicIndex=_graphicMaster->createRGBSurface(filename);
  //optimizing for display
  _graphicIndex=_graphicMaster->cloneToDisplay(_graphicIndex);
}
//copy constructor : just pass the sprite to use as model
Sprite::Sprite(const Sprite & model)
{
	//shouldnt be neeeded, but...
	if (_graphicMaster==NULL || _referencecount == 0)
    _graphicMaster=new SDLSurfaceFactory();
  _referencecount++;
  _graphicIndex=model._graphicIndex;
}
	
Sprite::~Sprite()
{
	_referencecount--;
	//only if we are the last sprite to be deleted
	if (_referencecount == 0)
	delete _graphicMaster;
	//maybe it is useless to do that... TO CHECK !
}

//to get the size
SDLRect Sprite::getSize(void)
{
	return SDLRect(_graphicMaster->getSurface(_graphicIndex)->getWidth(),_graphicMaster->getSurface(_graphicIndex)->getHeight());
}
	
//this one predraw a bounding box and axis on top of _graphic. Up to the derivative class to use it or not.
bool Sprite::drawBox(void) const
{
	//TODO
	
	
	return false;
}

bool Sprite::move(const Vector2& deltap)
{
	return GraphicElement::move(deltap);
}

void Sprite::render(unsigned int myPixCenterX, unsigned int myPixCenterY)
{
	
  //put the center of the sprite at his position
	SDLPoint destPos ( myPixCenterX,myPixCenterY);
	destPos.setx(destPos.getx() - getSize().getw() /2) ;
	destPos.sety(destPos.gety() - getSize().geth() /2) ;
  std::cerr<<"Calling _screen->blit(*"<<(_graphicMaster->getSurface(_graphicIndex))<<","<< destPos<<")"<<std::endl;
  std::cerr << " returns " <<std::boolalpha<< Config::_screen->blit(*(_graphicMaster->getSurface(_graphicIndex)), destPos) << std::endl;
}

