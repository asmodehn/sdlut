#include "SDLwrap.hh"

#include <unistd.h>
#include <iostream>
using namespace std;

#ifdef __MINGW32__
#ifdef main
#undef main
#endif
#endif

//global variable
SDLRGBSurface bitmap("sample.bmp");

//global function :
void resetDisplay(int newW, int newH)
{
	SDLSurfaceFactory::getScreen()->resize(newW,newH);
	SDLSurfaceFactory::getScreen()->debug();
/*  if ( ! SDLSurfaceFactory::getScreen()->isOpenGLset() ) //2D specific resize code
  {
  SDLSurfaceFactory::getScreen()->fill(SDLColor(255,0,0));
	SDLSurfaceFactory::getScreen()->blit(
    bitmap,SDLPoint(	(SDLSurfaceFactory::getScreen()->getWidth()-bitmap.getWidth())/2,
      (SDLSurfaceFactory::getScreen()->getHeight()-bitmap.getHeight())/2
			)
    );
	}*/
}



//Defining UserInput
class MyUserInput : public SDLEventHandler
{
	bool closing;

public:
	MyUserInput() : closing(false) {}
	virtual bool handleKeyboardEvent (SDL_keysym &keysym, bool pressed)
	{
		switch( keysym.sym ) {
    		case SDLK_ESCAPE: if (pressed==false) closing=true; break;
    		case SDLK_F5: if (pressed==true) SDLDisplaySurface::iconify(); break;
    		case SDLK_F6: if (pressed==true) SDLDisplaySurface::toggleFullScreen(); break;
	    default: break;
		}
		return true;
	}
	virtual bool handleResizeEvent(int w, int h) { resetDisplay(w,h); }
	virtual bool handleQuitEvent(void) { closing=true; return true; }
	bool closed(void) { return closing; }
};

//Main Program
int main(int argc, char** argv)
{
	//Setup example

	SDLManager::enableVideo();
	SDLManager::manager()->debug();

	//Getting video informations
	SDLVideoInfo::Info()->debug();

	//UI Creation
	MyUserInput ui;

	SDLCursor cursor(blackArrow);
	cursor.show();
	SDLCursor::setCurrent(cursor);
	
/* We cannot activate SDLDisplay and SDLGLWindow in the same time...
This is due to sdl design for portability : only one window at the same time
Be carefull when you use them...
SGE should completely hide this from the user.
SGE should also switch from one to the other with exec() and quit,
when the configuration file changed...*/

	
	//Checking available video Modes
	if(!SDLSurfaceFactory::setDisplayFlags())
	{
		std::cout << "\nThe required mode is not available !" << std::endl;
	}
	else
	{
		vector<int> h=SDLSurfaceFactory::getAvailableDisplayHeight();
		vector<int> w=SDLSurfaceFactory::getAvailableDisplayWidth();
		
		std::cout << "\nAvailable Modes : " ;
		if ( h[0] == -1 || w[0] == -1 ) std::cout << "all";
		else
		{
			for (unsigned int i=0; i<h.size() ; i++)
			{
				std::cout <<  "- " << h[i] << "x" << w[i] << "\n";
			}	
		}
		std::cout << std::endl ;
	}

	int newW=bitmap.getWidth()+60;
	int newH=bitmap.getHeight()+60;
	
	if (!SDLSurfaceFactory::setDisplaySize(newW,newH))
		std::cout << "\nThis Video Mode is not available !" << std::endl;
		
	int newBPP=SDLSurfaceFactory::checkVideoMode();
	if (!newBPP) std::cout << "Video Mode not usable !" << std::endl;
	else std::cout << "SDL will use " << newW << "x" << newH << "@" <<newBPP << std::endl;

	SDLDisplaySurface* display;
	// Window creation
	if ((display = SDLSurfaceFactory::createDisplay()) != NULL)
	{
		display->debug();
		
		if (display->fill(SDLColor(255,0,0)))
			display->blit(bitmap,SDLPoint(30,30));
		
		SDLSurfaceFactory smileyFactory;
		smileyFactory.createRGBSurface("icon.bmp");
		if(!smileyFactory.cloneToDisplay()) std::cerr << "clone failed" << std::endl;
		
		std::vector<SDLRGBSurface*> slist=smileyFactory.getSurfaceList();
		std::cout << "taille = " << slist.size() << std::endl;
		SDLRGBSurface* s=slist[slist.size()-1];
		std::cout << "s : " <<s->getWidth() << " x " << s->getHeight() << std::endl;
		if (s==NULL) {LIB_ERROR("s is NULL!"); exit(1);}
		

		std::cout << std::boolalpha << display->blit(*s,SDLPoint(50,50)) << std::endl;
		
		SDLCursor::warpCurrent(SDLPoint(50,50));
		
		while(!(ui.closed()))
		{
			SDLEvent::handleEvents(ui);
			//TODO : moving 10 smileys randomly
			
			//use the access method because of the resize event which modify the screen address
			SDLSurfaceFactory::getScreen()->update();

		}		
	}
	
	//First test ended : go on to test OPENGL
	
	std::cout << " OPENGL activation... " << std::endl;
	if(!SDLSurfaceFactory::setDisplayFlags(true))
	{
		std::cout << "\nThe required mode is not available !" << std::endl;
	}
	else
	{
		vector<int> h=SDLSurfaceFactory::getAvailableDisplayHeight();
		vector<int> w=SDLSurfaceFactory::getAvailableDisplayWidth();
		
		std::cout << "\nAvailable Modes : " ;
		if ( h[0] == -1 || w[0] == -1 ) std::cout << "all";
		else
		{
			for (unsigned int i=0; i<h.size() ; i++)
			{
				std::cout <<  "- " << h[i] << "x" << w[i] << "\n";
			}	
		}
		std::cout << std::endl ;
	}
	
	MyUserInput ui2; // another ui, since the first is closed ( but not deleted )
	std::cout <<"display reset" << std::endl;
	
	//GLManager test
	std::cout << std::boolalpha <<
			"setRsize(5) " << SDLGLManager::manager()->setRSize(5) << "\n" <<
			"setGSize(5) " << SDLGLManager::manager()->setGSize(5) << "\n" <<
			"setBSize(5) " << SDLGLManager::manager()->setBSize(5) << "\n" <<
			"setASize(5) " << SDLGLManager::manager()->setASize(5) << "\n" <<
			"setBufferSize(5) " << SDLGLManager::manager()->setBufferSize(12) << "\n" <<
			std::endl;

		//GLManager test
		SDLGLManager::manager()->debug();
	
	if ((display = SDLSurfaceFactory::createDisplay()) != NULL)
	{
		
		//GLManager test
		SDLGLManager::manager()->debug();
	
		std::cout << "calling display->debug() " << std::endl;
		display->debug();
		
		std::cout << std::boolalpha << " setDepthSize(16) " << SDLGLManager::manager()->setDepthSize(16) << std::endl;
		
		SDLGLManager::manager()->debug();
		
		std::cout << "loop... " << std::endl;
		while(!(ui2.closed()))
		{
			SDLEvent::handleEvents(ui2);
			//use the access method because of the resize event which modify the screen address
			SDLSurfaceFactory::getScreen()->update();
		}		
	}

	return 0;
}
