
/* Test program to try Application management...
*/

#include "SDL.hh"
using namespace RAGE;
using namespace RAGE::SDL;

class KeyboardInput : public Keyboard
{
	bool handleKeyEvent (const Sym &s, bool pressed)
	{
		if (pressed)
			if ( s.getKey() == KEscape )
				_quitRequested=true;

		return true;
	}
};

class RenderEngine : public DefaultEngine
{

public:

	RenderEngine()
	{}

    ~RenderEngine(){}
			
    bool init(int width, int height)
	{
		return true;
	}

	bool resize(int width, int height)
	{
		return true;
	}

	void prerender(VideoSurface & screen) const
    {
    }

	void render(VideoSurface & screen) const
    {
    }

	void postrender(VideoSurface & screen) const
    {
    }
};


int main(int argc, char *argv[])
{
	Logger testlog("testApp");

	SDL::App::getInstance().setName ("RAGE::SDL Functionnal testing - App");

	//Minimum Init
	testlog << nl << " Minimum init... " << std::endl;
	testlog << ( (SDL::App::getInstance().init())? "OK" : "FAILED" );
	testlog << nl << " Retrieving Manager... " << std::endl;
	testlog << ( (SDL::App::getInstance().getManager() != NULL)? "OK" : "FAILED" );
	
	//Video Init
	testlog << nl << " Enabling Video... " << std::endl;
	testlog << ( (SDL::App::getInstance().initVideo(false,false,false,false))? "OK" : "FAILED" );
	testlog << nl << " Retrieving Window... " << std::endl;
	testlog << ( (SDL::App::getInstance().getWindow() != NULL)? "OK" : "FAILED" );
	
	//Audio Init
	/*testlog << nl << " Enabling Audio... " << std::endl;
	testlog << ( (SDL::App::getInstance().initAudio())? "OK" : "FAILED" );
	testlog << nl << " Retrieving Mixer... " << std::endl;
	testlog << ( (SDL::App::getInstance().getMixer() != NULL)? "OK" : "FAILED" );

	//Timer Init
	testlog << nl << " Enabling Timer... " << std::endl;
	testlog << ( (SDL::App::getInstance().initTimer())? "OK" : "FAILED" );

#ifdef HAVE_SDLTTF
	//Font Init
	testlog << nl << " Enabling Text... " << std::endl;
	testlog << ( (SDL::App::getInstance().initText())? "OK" : "FAILED" );
#endif
*/
	App::getInstance().getWindow()->resetDisplay();
	KeyboardInput* myKeyboardInput = new KeyboardInput();
	App::getInstance().getWindow()->getEventManager()->setKeyboard(myKeyboardInput);
	RenderEngine* myEngine = new RenderEngine();
	App::getInstance().getWindow()->setEngine(myEngine);
	App::getInstance().getWindow()->mainLoop();

	//delete myKeyboardInput, myKeyboardInput = NULL;
	delete myEngine, myEngine = NULL;

	return 0;
}

