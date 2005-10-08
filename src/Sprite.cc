#include "Sprite.hh"

SDLSurfaceFactory * Sprite::_graphics=NULL;

unsigned int Sprite::_referencecount=0;

//constructor : just pass the file containing the sprite
Sprite::Sprite(const std::string & filename)
{
	if (_graphics==NULL || _referencecount == 0)
    _graphics=new SDLSurfaceFactory();
  _referencecount++;
  //creating the surface in memory
  _graphicIndex=_graphics->createRGBSurface(filename);
  //optimizing for display
  _graphicIndex=_graphics->cloneToDisplay(_graphicIndex);

}
//copy constructor : just pass the sprite to use as model
Sprite::Sprite(const Sprite & model)
{
	//shouldnt be neeeded, but...
	if (_graphics==NULL || _referencecount == 0)
    _graphics=new SDLSurfaceFactory();
  _referencecount++;
  _graphicIndex=model._graphicIndex;
	
}
	
Sprite::~Sprite()
{
	_referencecount--;
	//only if we are the last sprite to be deleted
	if (_referencecount == 0)
	delete _graphic;
}
