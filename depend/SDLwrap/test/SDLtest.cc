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

	testlog.add(" Enabling SDL Video... ");
	Manager::enableVideo();
	Manager::manager()->debug();

//SDLDisplaySurface* display = SDLSurfaceFactory::createDisplay();
//system("pause");

  testlog.add(" Checking SDL Video Info... ");
	//Getting video informations
	Manager::manager()->getVideoInfo()->debug();

  testlog.add(" Creating the User Interface... ");
	//UI Creation
	MyUserInput ui;

  testlog.add(" Creating the SDL Cursor... ");
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
		testlog.add( "\nThe required mode (default) is not available !" );
		exit(1);
	}

	RGBSurface bitmap (bitmapname);

	int newW=bitmap.getWidth()+60;
	int newH=bitmap.getHeight()+60;

	DisplaySurface* display;
	if (! (display=Manager::manager()->setDisplay(newW,newH)))
    {
        testlog.add( "Display Creation FAILED !");
        exit(0);
    }
    else
    {
        display->debug();

		if (display->fill(Color(255,0,0)))
			display->blit(bitmap,Point(30,30));

		RGBSurface smiley("icon.bmp"/*,Color(255,255,255)*/); //doing the colorkey now break the clone...
//		if(!smileyFactory.cloneToDisplay(index)) std::cerr << "clone failed" << std::endl;
//
//		std::vector<RGBSurface*> slist=smileyFactory.getSurfaceList();
//		std::cout << "taille = " << slist.size() << std::endl;
//		RGBSurface* s=slist[slist.size()-1];
//		std::cout << "s : " <<s->getWidth() << " x " << s->getHeight() << std::endl;
//		if (s==NULL) {testlog.add("s is NULL!"); exit(1);}


		std::cout << std::boolalpha << display->blit(smiley,Point(50,50)) << std::endl;

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

	testlog.add(" OPENGL activation... ");


	if(!DisplaySurface::setFlags(true))
	{
		std::cout << "\nThe required mode is not available !" << std::endl;
	}

	MyUserInput ui2; // another ui, since the first is closed ( but not deleted )
	std::cout <<"display reset" << std::endl;

	//GLManager test
	std::cout << std::boolalpha <<
			"setRsize(5) " << GLManager::manager()->setRSize(5) << "\n" <<
			"setGSize(5) " << GLManager::manager()->setGSize(5) << "\n" <<
			"setBSize(5) " << GLManager::manager()->setBSize(5) << "\n" <<
			"setASize(5) " << GLManager::manager()->setASize(5) << "\n" <<
			"setBufferSize(5) " << GLManager::manager()->setBufferSize(12) << "\n" <<
			std::endl;

		//GLManager test
		GLManager::manager()->debug();

	if ((display = Manager::manager()->setDisplay()) != NULL)
	{

		//GLManager test
		GLManager::manager()->debug();

		std::cout << "calling display->debug() " << std::endl;
		display->debug();

		std::cout << std::boolalpha << " setDepthSize(16) " << GLManager::manager()->setDepthSize(16) << std::endl;

		GLManager::manager()->debug();

		std::cout << "loop... " << std::endl;
		while(!(ui2.closed()))
		{
			Event::handleEvents(ui2);
			//use the access method because of the resize event which modify the screen address
			Manager::manager()->getDisplay()->update();
		}
	}

	return 0;
}
