#include "SDLWindow.hh"


namespace SDL {

Window::Window(int width, int height, int bpp) throw (std::logic_error)
: DisplaySurface( width, height, bpp, flags & (~SDL_OPENGL))
{ }


bool Window::update(void)
{
	return SDL_Flip(_surf) == 0;
}

void Window::debug(void) const
{
	DisplaySurface::debug();
	std::cout << std::endl;
}

//SaveScreen -> backup the screen content in a RGBSurface...
RGBSurface* Window::save(void)
{
	Log << "Window::save()" ;
	// we create a new RGB surface to clone the display...
	RGBSurface * backupScreen= new RGBSurface(*this,true,true,false);

	return backupScreen;
}

//restoreScreen -> blit the saved surface to the center of the screen
bool Window::restore(const RGBSurface& savedScreen)
{
  bool res;

 Log << "Window::restore()";

  Point newpos;
  newpos.setx( (getWidth()-savedScreen.getWidth()) / 2 );
  newpos.sety( (getHeight()-savedScreen.getHeight()) / 2 );

  std::cerr << "blit savedScreen at " << newpos << std::endl;
  res = blit(savedScreen, newpos);

	return res;
}



bool Window::resize(int width, int height)
{

  std::cerr << "Resize start" << std::endl;
	bool res = false;
	//proper way to do that :
	// 1 - save the current display surface

	//AUTO_PTR to manage the delete at the end ??
	RGBSurface * backup=save();

	std::cerr << "Saved Surface debug :" << std::endl;
	backup->debug();

	// 2 - create a new one similar, with new size
  //BEWARE : should match DisplaySurface Constructor code
  SDL_Surface * newSurf = SDL_SetVideoMode(width,height,getBPP(),getFlags());



	if (newSurf==NULL) //SetVideoMode has failed
	{
		Log << "Unable to resize to " << width << " x " << height << " 2D display surface " << nl << GetError();
	}
	else //setvideoMode successfull
	{
		// 3 - restore the screen
    restore(*backup);

    //update the pointer
    _surf=newSurf;

    res = true;
    //BEWARE : According to the doc, the display surface should never be freed by the caller of SetVideoMode. SDL_Quit will handle that.
	}

  std::cerr << "New Display Surface debug :" << std::endl;
	debug();

	//TODO : backup should be freed / deleted anyway !!

	return res;
}

} //namespace SDL
