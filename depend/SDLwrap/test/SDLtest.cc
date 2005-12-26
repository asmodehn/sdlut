#include "SDLwrap.hh"
#include "Logger.hh"

//#include <unistd.h>
#include <iostream>
using namespace std;
using namespace SDL;


//global variable
std::string bitmapname("sample.bmp");

//Defining UserInput
class MyUserInput : public EventHandler
{
public:
	MyUserInput() : EventHandler(App::getInstance().getAppWindow()) {}
	virtual bool handleKeyboardEvent (SDL_keysym &keysym, bool pressed)
	{
		switch( keysym.sym ) {
    		case SDLK_ESCAPE: if (pressed==false) _quitRequested=true; break;
    		case SDLK_F5: if (pressed==true) App::getInstance().getAppWindow()->iconify(); break;
    		case SDLK_F6: if (pressed==true) App::getInstance().getAppWindow()->toggleFullScreen(); break;
	    default: break;
		}
		return true;
	}
};

//Main Program
int main(int argc, char** argv)
{

    Logger testlog("Test Log");

	//Setup example

    testlog << nl << " Enabling SDL Video... " << std::endl;
	App::getInstance().setName ("SDLtest");
	App::getInstance().initWindow(false,false,true,false);

	//Getting video informations
	testlog << nl << *App::getInstance().getAppWindow()->getVideoInfo() << std::endl;

	testlog << nl << " Creating the User Interface... " << std::endl;
	//UI Creation
	MyUserInput ui;
    App::getInstance().setEventHandler(&ui);

    testlog << nl << " Creating the SDL Cursor... " << std::endl;
	Cursor cursor(blackArrow);
	cursor.show();
	Cursor::setCurrent(cursor);

	RGBSurface bitmap (bitmapname);

	int newW=bitmap.getWidth()+60;
	int newH=bitmap.getHeight()+60;

    App::getInstance().getAppWindow()->setBGColor(Color (128,0,0));


	if (! (App::getInstance().getAppWindow()->reset(newW,newH)))
    {
		testlog << nl << "Display Creation FAILED !"<< std::endl;
        exit(0);
    }
    else
    {
        DisplaySurface* display=App::getInstance().getAppWindow()->getDisplay();
        testlog << nl << *display << std::endl;

		display->blit(bitmap,Point(30,30));

		RGBSurface smiley("icon.bmp",Color(255,255,255));
        smiley.optimise(true);

		testlog << nl << std::boolalpha << display->blit(smiley,Point(50,50)) << std::endl;

		Cursor::warpCurrent(Point(50,50));

        App::getInstance().mainLoop();

	}

	//First test ended : go on to test OPENGL

	testlog << nl << " OPENGL activation... " << std::endl;

	MyUserInput ui2; // another ui, since the first is closed ( but not deleted )
	App::getInstance().setEventHandler(&ui2);
	testlog << nl <<"display reset" << std::endl;

	//GLManager test
	GLManager * glman=App::getInstance().getAppWindow()->getGLManager();
	testlog << nl<<std::boolalpha <<
			"setRsize(5) " << glman->setRSize(5) << nl <<
			"setGSize(5) " << glman->setGSize(5) << nl <<
			"setBSize(5) " << glman->setBSize(5) << nl <<
			"setASize(5) " << glman->setASize(5) << nl <<
			"setBufferSize(5) " << glman->setBufferSize(12) << nl <<
			std::endl;

App::getInstance().getAppWindow()->setOpenGL(true);

if(App::getInstance().getAppWindow()->reset())
	{


		//GLManager test
		testlog << nl << *glman << std::endl;

        DisplaySurface* display=App::getInstance().getAppWindow()->getDisplay();
		testlog << nl << "calling display->debug() " << std::endl;
		testlog << nl << *display <<std::endl;

		testlog << nl << std::boolalpha << " setDepthSize(16) " << glman->setDepthSize(16) << std::endl;

		testlog << nl << *glman << std::endl;

		testlog << nl << "loop... " << std::endl;
			App::getInstance().mainLoop();
	}

	std::cout << "blabla" << std::endl;

	return 0;
}
