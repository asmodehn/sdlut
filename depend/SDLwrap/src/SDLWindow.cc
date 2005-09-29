#include "SDLWindow.hh"

SDLWindow::SDLWindow(int width, int height, int bpp, Uint32 flags) throw (std::logic_error)
: SDLDisplaySurface( width, height, bpp, flags)
{ }



bool SDLWindow::update(void)
{
	return SDL_Flip(_surf) == 0;
}

void SDLWindow::debug(void) const
{
	SDLDisplaySurface::debug();
	std::cout << std::endl;
}

//SaveScreen -> backup the screen content in a RGBSurface...
SDLRGBSurface* SDLWindow::save(void)
{
	std::cerr << "SDLWindow::save()" << std::endl;
	// we create a new RGB surface to clone the display...
	SDLRGBSurface * backupScreen= new SDLRGBSurface(*this,true,true,false);
	
	return backupScreen;
}

//restoreScreen -> blit the saved surface to the center of the screen
bool SDLWindow::restore(const SDLRGBSurface& savedScreen)
{
  bool res;
  
  std::cerr << "SDLWindow::restore()" << std::endl;
  
  SDLPoint newpos;
  newpos.setx( (getWidth()-savedScreen.getWidth()) / 2 );
  newpos.sety( (getHeight()-savedScreen.getHeight()) / 2 );
  
  std::cerr << "blit savedScreen at " << newpos << std::endl;
  res = blit(savedScreen, newpos);

	return res;	
}
	
	

bool SDLWindow::resize(int width, int height)
{
	
  std::cerr << "Resize start" << std::endl;
	bool res;
	//proper way to do that :
	// 1 - save the current display surface
	
	//AUTO_PTR to manage the delete at the end ??
	SDLRGBSurface * backup=save();
	
	std::cerr << "Saved Surface debug :" << std::endl;
	backup->debug();
	
	// 2 - create a new one similar, with new size
  //BEWARE : should match SDLDisplaySurface Constructor code
  SDL_Surface * newSurf = SDL_SetVideoMode(width,height,getBPP(),getFlags());


	
	if (newSurf==NULL) //SetVideoMode has failed
	{
		std::cerr << "Unable to resize to " << width << " x " << height << " 2D display surface " << std::endl;
		SDLERROR;
	}
	else //setvideoMode successfull
	{
		// 3 - restore the screen
    restore(*backup);
    
    //update the pointer
    _surf=newSurf;
    
    //BEWARE : According to the doc, the display surface should never be freed by the caller of SetVideoMode. SDL_Quit will handle that.
	}

  std::cerr << "New Display Surface debug :" << std::endl;	
	debug();
	
	//TODO : backup should be freed / deleted anyway !!
	
	return res;
}
