
/**
 * Test program to test Loading Screen...
 **/


#include "SDL.hh"
using namespace RAGE;
using namespace RAGE::SDL;

//Globals
Logger testlog("testApp");
short GLOBAL_STATE = 1;

std::string Int_To_String(const int &to_convert)
{
	std::stringstream s;
    if (s << to_convert) // conversion worked
        return s.str();

	//failed
	return NULL;
}

 //User Input
class KeyboardInput : public Keyboard
{
private:
	std::string LSBGFn;
public:
	KeyboardInput (const std::string& LoadingScreenBg_Filename) : LSBGFn(LoadingScreenBg_Filename)
	{}
	~KeyboardInput() {}

    virtual bool handleKeyEvent (const Sym &s, bool pressed)
    {
        switch( s.getKey() )
        {
            case KEscape:
				if (pressed)
				{
					if (GLOBAL_STATE == 1)
					{						
						GLOBAL_STATE = 2;						
					}
					else if (GLOBAL_STATE == 2)
					{
						App::getInstance().getWindow().HideLoadingScreen();
						GLOBAL_STATE = 3;
					}
					else if (GLOBAL_STATE == 3)
					{
						App::getInstance().requestTermination();
						//_quitRequested=true;
					}
				}
				break;
           
            default:
				break;;
        }
        return true;
    }
};

//Mouse input: to disable boring show position from default Mouse class
class MouseInput : public Mouse
{
private:
public:
	MouseInput() {}
	~MouseInput() {}
	bool handleMouseButtonEvent (Button button, unsigned int x, unsigned int y, bool pressed){return true;}
	bool handleMouseMotionEvent (bool button_pressed, unsigned int x, unsigned int y, signed int xrel, signed int yrel){return true;}	
};

//render Engine: show Default Engine render but when GLOBAL_STATE == 2, show Loading Screen
class RenderEngine : public DefaultEngine
{
private:
	std::string LSBGFn;
public:
	RenderEngine(const std::string& LoadingScreenBg_Filename) : LSBGFn(LoadingScreenBg_Filename)
	{}

    ~RenderEngine() {}
			
    bool init(int width, int height)
	{
		return true;
	}

	bool resize(int width, int height)
	{
		return true;
	}

	void render(VideoSurface & screen) const
    {
		if (GLOBAL_STATE == 1 || GLOBAL_STATE == 3)
			DefaultEngine::render(screen);
		else if (GLOBAL_STATE == 2)
		{
			App::getInstance().getWindow().ShowLoadingScreen( LSBGFn, "YOU ARE INSIDE THE MAAAATRIX", std::auto_ptr<Font>(new Font("data/ECHELON.TTF", 25)), "", std::auto_ptr<Font>( new Font("data/ECHELON.TTF", 14)), Rect(100, 400, 600, 25) );
			App::getInstance().getWindow().UpdateLoadingScreen(100, "Washing Your Brain, Press Esc Key Twice To Flee ...");
		}
    }
};

int main(int argc, char *argv[])
{
try {	
	SDL::App::getInstance().setName ("RAGE::SDLut Functionnal Testing - Loading Screen");

	//Video Init
	testlog << nl << " Enabling Video... " << std::endl;
	testlog << ( (SDL::App::getInstance().initVideo(false,false,false,false))? "OK" : "FAILED" );

#ifdef HAVE_SDLTTF
	//Font Init
	testlog << nl << " Enabling Text... " << std::endl;
	testlog << ( (SDL::App::getInstance().initText())? "OK" : "FAILED" );
#endif

	std::string loading_screen = "data/LS_Initial.png";

	//Show Loading Screen
	App::getInstance().getWindow().resetDisplay(800,600);
	App::getInstance().getWindow().ShowLoadingScreen( loading_screen, "GLOBAL BLABLA", std::auto_ptr<Font>(new Font("data/ECHELON.TTF", 25)), "Setting User Input", std::auto_ptr<Font>( new Font("data/ECHELON.TTF", 12)), Rect(100, 400, 600, 25) );

	//Setting User Input
	KeyboardInput myKeyboardInput(loading_screen);
	App::getInstance().getWindow().getEventManager().setKeyboard(&myKeyboardInput);
	MouseInput *myMouseInput = new MouseInput();
	App::getInstance().getWindow().getEventManager().setMouse(myMouseInput);	

	//Setting Render Engine
	App::getInstance().getWindow().UpdateLoadingScreen(10, "Setting Render Engine");
	RenderEngine myRenderEngine(loading_screen);
	App::getInstance().getWindow().setEngine(&myRenderEngine);

	//Do something while loading screen displayed
	for (int i = 0; i < 5; i++)
	{
		App::getInstance().getWindow().UpdateLoadingScreen(20+16*(i), "Doing Iterations N°" + Int_To_String(i) );
		testlog << nl << "Test Loading Screen Iteration N°" << i << std::endl;
		Delay(300);
		
	}

	//start mainloop
	App::getInstance().getWindow().UpdateLoadingScreen(100, "Done" );
	App::getInstance().getWindow().HideLoadingScreen();
	App::getInstance().getWindow().mainLoop();

	//quit
	delete myMouseInput, myMouseInput = NULL;
	return 0;

}
catch(std::exception & e)
{
	testlog << nl << "Exception caught in main : " << e.what();
} catch (...) {
	testlog << nl << "Unhandled exception in main.";
}
}
