#include "SDLwrap.hh"
#include "Logger.hh"

//#include <unistd.h>
#include <iostream>
using namespace std;
using namespace SDL;

//would be nice if we can put that in SDLwrap.hh
#ifdef __MINGW32__
#ifdef main
#undef main
#endif
#endif


//global variable
std::string bitmapname("sample.bmp");

//global function :
void resetDisplay(int newW, int newH)
{
	Manager::manager()->getDisplay()->resize(newW,newH);
	Manager::manager()->getDisplay()->debug();
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
class MyUserInput : public EventHandler
{
	bool closing;

public:
	MyUserInput() : closing(false) {}
	virtual bool handleKeyboardEvent (SDL_keysym &keysym, bool pressed)
	{
		switch( keysym.sym ) {
    		case SDLK_ESCAPE: if (pressed==false) closing=true; break;
    		case SDLK_F5: if (pressed==true) Manager::manager()->getDisplay()->iconify(); break;
    		case SDLK_F6: if (pressed==true) Manager::manager()->getDisplay()->toggleFullScreen(); break;
	    default: break;
		}
		return true;
	}
	virtual bool handleResizeEvent(int w, int h) { resetDisplay(w,h); return true;}
	virtual bool handleQuitEvent(void) { closing=true; return true; }
	bool closed(void) { return closing; }
};

//Main Program
int main(int argc, char** argv)
{

  Logger testlog("Test Log");

	//Setup example

  testlog << nl << " Enabling SDL Video... " << std::endl;
	Manager::enableVideo();
	Manager::manager()->debug();

	testlog << nl <<  " Checking SDL Video Info... " << std::endl;
	//Getting video informations
	Manager::manager()->getVideoInfo()->debug();

	testlog << nl << " Creating the User Interface... " << std::endl;
	//UI Creation
	MyUserInput ui;

  testlog << nl << " Creating the SDL Cursor... " << std::endl;
	Cursor cursor(blackArrow);
	cursor.show();
	Cursor::setCurrent(cursor);

/* We cannot activate SDLDisplay and SDLGLWindow in the same time...
This is due to sdl design for portability : only one window at the same time
Be carefull when you use them...
SGE should completely hide this from the user.
SGE should also switch from one to the other with exec() and quit,
when the configuration file changed...*/


	//Checking available video Modes
	if(!DisplaySurface::setFlags())
	{
		testlog << nl << "The required mode (default) is not available !" << std::endl;
		exit(1);
	}

	RGBSurface bitmap (bitmapname);

	int newW=bitmap.getWidth()+60;
	int newH=bitmap.getHeight()+60;

	DisplaySurface* display;
	if (! (display=Manager::manager()->setDisplay(newW,newH)))
    {
		testlog << nl << "Display Creation FAILED !"<< std::endl;
        exit(0);
    }
    else
    {
        display->debug();

		if (display->fill(Color(255,0,0)))
			display->blit(bitmap,Point(30,30));

		RGBSurface smiley("icon.bmp",Color(255,255,255)); //doing the colorkey now break the clone...
    //smiley.optimise(true);

		testlog << nl << std::boolalpha << display->blit(smiley,Point(50,50)) << std::endl;

		Cursor::warpCurrent(Point(50,50));

		while(!(ui.closed()))
		{
			Event::handleEvents(ui);
			//TODO : moving 10 smileys randomly

			//use the access method because of the resize event which modify the screen address
			Manager::manager()->getDisplay()->update();

		}
	}

	//First test ended : go on to test OPENGL

	testlog << nl << " OPENGL activation... " << std::endl;


	if(!DisplaySurface::setFlags(true))
	{
		testlog << nl << "\nThe required mode is not available !" << std::endl;
	}

	MyUserInput ui2; // another ui, since the first is closed ( but not deleted )
	testlog << nl <<"display reset" << std::endl;

	//GLManager test
	testlog << nl<<std::boolalpha <<
			"setRsize(5) " << Manager::manager()->getGLManager()->setRSize(5) << nl <<
			"setGSize(5) " << Manager::manager()->getGLManager()->setGSize(5) << nl <<
			"setBSize(5) " << Manager::manager()->getGLManager()->setBSize(5) << nl <<
			"setASize(5) " << Manager::manager()->getGLManager()->setASize(5) << nl <<
			"setBufferSize(5) " << Manager::manager()->getGLManager()->setBufferSize(12) << nl <<
			std::endl;

	if ((display = Manager::manager()->resetDisplay()) != NULL)
	{

		//GLManager test
		Manager::manager()->getGLManager()->debug();

		testlog << nl << "calling display->debug() " << std::endl;
		display->debug();

		testlog << nl << std::boolalpha << " setDepthSize(16) " << Manager::manager()->getGLManager()->setDepthSize(16) << std::endl;

		Manager::manager()->getGLManager()->debug();

		testlog << nl << "loop... " << std::endl;
		while(!(ui2.closed()))
		{
			Event::handleEvents(ui2);
			//use the access method because of the resize event which modify the screen address
			Manager::manager()->getDisplay()->update();
		}
	}

	return 0;
}
