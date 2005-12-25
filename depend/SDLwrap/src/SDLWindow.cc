#include "SDLWindow.hh"


namespace SDL {

Window::Window(int width, int height, int bpp) throw (std::logic_error)
: DisplaySurface( width, height, bpp, flags & (~SDL_OPENGL))
{
    _backupscreen = NULL;
}
Window::~Window()
{
    if (_backupscreen !=NULL ) delete _backupscreen;
}

bool Window::update(void)
{
	return SDL_Flip(_surf) == 0;
}

Logger & operator << (Logger & ostr, const Window & win)
{
	//log << static_cast<DisplaySurface> (win);
	return ostr;
}

//SaveScreen -> backup the screen content in a RGBSurface...
bool Window::saveContent(void)
{
    if (_backupscreen != NULL ) delete _backupscreen;

	Log << nl << "Window::saveContent()" << std::endl;
	// we create a new RGB surface to clone the display...
	_backupscreen= new RGBSurface(*this);

	return _backupscreen!=NULL;
}

//restoreScreen -> blit the saved surface to the center of the screen
bool Window::restoreContent(void)
{
  bool res;

 Log << nl << "Window::restoreContent()" << std::endl;

//to restore the content in the middle of the window
  Point newpos;
  newpos.setx( (getWidth()-_backupscreen->getWidth()) / 2 );
  newpos.sety( (getHeight()-_backupscreen->getHeight()) / 2 );

  Log << nl << "Blitting backupscreen at " << newpos << std::endl;
  res = blit(*_backupscreen, newpos);

	return res;
}



bool Window::resize(int width, int height)
{
    bool res = false;
    //BEWARE : should match DisplaySurface Constructor code
  SDL_Surface * newSurf = SDL_SetVideoMode(width,height,getBPP(),getFlags());

	if (newSurf==NULL) //SetVideoMode has failed
	{
		Log << "Unable to resize to " << width << " x " << height << " 2D display surface " << nl << GetError();
	}
	else //setvideoMode successfull
    {
        _surf=newSurf;
        res = true;
        //BEWARE : According to the doc, the display surface should never be freed by the caller of SetVideoMode. SDL_Quit will handle that.
    }

	return res;
}

} //namespace SDL
