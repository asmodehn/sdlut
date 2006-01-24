#include "SDL.hh"
using namespace RAGE;
using namespace RAGE::SDL;

//Defining UserInput
class MyUserInput : public Keyboard
{
public:

	virtual bool handleKeyEvent (SDL_keysym &keysym, bool pressed)
	{
	    bool res = false;
	    if (! (res = Keyboard::handleKeyEvent(keysym,pressed)))
		switch( keysym.sym ) {
		    case SDLK_ESCAPE:
            if (pressed==false)
            {
#ifdef DEBUG
    Log << nl << "Quit requested !" << std::endl;
#endif
                _quitRequested=true;
                res=true;
            }
            break;
    		case SDLK_F5: if (pressed==true) App::getInstance().getWindow()->iconify(); res = true; break;
    		case SDLK_F6: if (pressed==true) App::getInstance().getWindow()->toggleFullScreen(); res = true; break;
	    default: res = false;
		}
		return res;
	}
};

//Main Program
int main(int argc, char** argv)
{

    Logger testlog("Test Log");

	//Setup example

    testlog << nl << " Enabling SDL Video... " << std::endl;
	App::getInstance().setName ("SDLtest");
	App::getInstance().initVideo(false,false,true,false);

	//Getting video informations
	testlog << nl << *App::getInstance().getWindow()->getVideoInfo() << std::endl;

	testlog << nl << " Creating the User Interface... " << std::endl;
	//UI Creation
	MyUserInput ui;
    App::getInstance().getWindow()->getEventManager()->setKeyboard(&ui);

    testlog << nl << " Creating the SDL Cursor... " << std::endl;
	Cursor cursor(blackArrow);
	cursor.show();
	Cursor::setCurrent(cursor);

//	RGBSurface bitmap (bitmapname);
//
//	int newW=bitmap.getWidth()+60;
//	int newH=bitmap.getHeight()+60;

    App::getInstance().getWindow()->setBGColor(Color (128,0,0));
    //App::getInstance().getWindow()->setEngine(new Engine());

	if (! (App::getInstance().getWindow()->reset()))
    {
		testlog << nl << "Display Creation FAILED !"<< std::endl;
        exit(0);
    }
    else
    {
        VideoSurface* display=App::getInstance().getWindow()->getDisplay();
        testlog << nl << *display << std::endl;

//		display->blit(bitmap,Point(30,30));
//
//		RGBSurface smiley("icon.bmp",Color(255,255,255));
//        smiley.optimise(true);
//
//		testlog << nl << std::boolalpha << display->blit(smiley,Point(50,50)) << std::endl;

		Cursor::warpCurrent(Point(50,50));

        App::getInstance().getWindow()->mainLoop();

	}

	//First test ended : go on to test OPENGL

	testlog << nl << " OPENGL activation... " << std::endl;

	MyUserInput ui2; // another ui, since the first is closed ( but not deleted )
	App::getInstance().getWindow()->getEventManager()->setKeyboard(&ui2);
	testlog << nl <<"display reset" << std::endl;

    //App::getInstance().getWindow()->setGLEngine(new GLEngine());
	//GLManager test
	GLManager * glman=App::getInstance().getWindow()->getGLManager();
	testlog << nl<<std::boolalpha <<
			"setRsize(5) " << glman->setRSize(5) << nl <<
			"setGSize(5) " << glman->setGSize(5) << nl <<
			"setBSize(5) " << glman->setBSize(5) << nl <<
			"setASize(5) " << glman->setASize(5) << nl <<
			"setBufferSize(5) " << glman->setBufferSize(12) << nl <<
			std::endl;

App::getInstance().getWindow()->setOpenGL(true);

if(App::getInstance().getWindow()->reset())
	{


		//GLManager test
		testlog << nl << *glman << std::endl;

        VideoSurface* display=App::getInstance().getWindow()->getDisplay();
		testlog << nl << "calling display->debug() " << std::endl;
		testlog << nl << *display <<std::endl;

		testlog << nl << std::boolalpha << " setDepthSize(16) " << glman->setDepthSize(16) << std::endl;

		testlog << nl << *glman << std::endl;

		testlog << nl << "loop... " << std::endl;
			App::getInstance().getWindow()->mainLoop();
	}

	return 0;
}


