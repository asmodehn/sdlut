// Include all necessary headers.
#include <iostream>
#include <guichan.hpp>
#include <guichan/sdlut.hpp>
#include "SDL.hh"
#include "Logger.hh"

/*#if defined (_WIN32)
	#include <windows.h>
	// Sometimes windows.h defines DELETE which causes a compilation
	// error in a Guichan header.
	#if defined (DELETE)
		#undef DELETE
	#endif
#endif

#if defined (__amigaos4__)
	#include <mgl/gl.h>
#elif defined(__APPLE__)
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif*/

namespace globals
{
    gcn::Gui* gui;
}
#include "helloworld.hpp"

using namespace RAGE;
using namespace RAGE::SDL;
using namespace globals;

//TODO : IF we dont want to use SLDut for the main window and top event handling...
// these too can be transparently called from gcn::Graphics*... thanks to inheritance
gcn::SDLutGraphics* graphics;       // Graphics driver
gcn::SDLutImageLoader* imageLoader; // For loading images

Logger logger("Example"); //prefix

//Defining UserInput
class KeyboardInput : public TextInput
{
public:

    bool handleKeyEvent (const Sym &s, bool pressed)
    {
        bool res = false;
            switch( s.getKey() )
            {
                case Key_Escape: //Quit
					if (!pressed)
					{
						logger << nl << "Quit requested !" << std::endl;

						App::getInstance().requestTermination();
						res=true;
					}
					break;

                case Key_F5: //iconify
					if (pressed)
						App::getInstance().getDisplay().getWindow().iconify();
					res = true;
					break;

				case Key_F6: //FullScreen
					if (pressed)
					{
						App::getInstance().getDisplay().setDisplay(800, 600);
						App::getInstance().getDisplay().setFullscreen(!App::getInstance().getDisplay().isFullscreen());
					}
					res = true;
					break;

				default:
					res = false;
            }

        return res;
    }
};

class RenderEngine
{

public:

	RenderEngine(){}

    virtual ~RenderEngine(){}

    bool init(int width, int height)
	{
		return true;
	}

	bool resize(int width, int height)
	{
		return true;
	}

	bool prerender(unsigned long framerate, unsigned long deltaticks)
	{
		//Check Gui Logic
		gui->logic();

		return true;
	}

	bool render(ScreenBuffer& screen) const
    {
		// Set the target for the graphics object to be the screen.
		// In other words, we will draw to the screen.
		graphics->setTarget(&screen);

		//oglgraphics->setTargetPlane(640, 480);

		//Draw The Gui
		gui->draw();

		return true;
    }
};

KeyboardInput* myKeyboardInput;
RenderEngine* myEngine;

void init(bool ogl = false)
{
	logger.enableFileLog("Example.Log");

	App::getInstance().setName("Example");

	if (! App::getInstance().initVideo(false, ogl, true, false) )
		throw std::logic_error( "Init Video Failed: " + GetError() );

	if (! App::getInstance().getDisplay().setDisplay(640, 480, 32)  )
		throw std::logic_error( "Create Surface Failed: " + GetError() );

	/*glViewport(0, 0, 640, 480);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);*/

}

void implement(bool ogl = false)
{
//GuiChan SDLuT Stuff
    imageLoader = new gcn::SDLutImageLoader();

	graphics = new gcn::SDLutGraphics();

//Gui Initialization
    gui = new gcn::Gui();
	gcn::Image::setImageLoader(imageLoader);
	gui->setGraphics(graphics); /*SDLuTGraphics*/

	helloworld::init();

//SDLuT Stuff
	myKeyboardInput = new KeyboardInput();
	App::getInstance().getDisplay().getEventManager().setKeyboard(myKeyboardInput);

	myEngine = new RenderEngine();

    App::getInstance().getDisplay().resetInitCallback(myEngine,&RenderEngine::init);
	App::getInstance().getDisplay().resetResizeCallback(myEngine,&RenderEngine::resize);
//	App::getInstance().getDisplay().resetNewFrameCallback(myEngine,&RenderEngine::prerender);
	App::getInstance().getDisplay().resetRenderCallback(myEngine,&RenderEngine::render);
}

void clean()
{
	helloworld::halt();
    delete gui, gui = NULL;

    delete graphics, graphics = NULL;

    delete imageLoader, imageLoader = NULL;


	delete myKeyboardInput, myKeyboardInput = NULL;
	delete myEngine, myEngine = NULL;
}

int main(int argc, char **argv)
{
    try
    {

		if ( argc > 1 && std::string(argv[1]) == "opengl" )
		{
			std::cout << "YEAH OpenGL" << std::endl;
			init(true);
			implement(true);
		}
		else
		{
			std::cout << "BOUH No OpenGL" << std::endl;
			init();
			implement();
		}

		if(App::getInstance().getDisplay().show())
		{
		   App::getInstance().getDisplay().mainLoop();
		}

        clean();
    }
    catch (gcn::Exception e)
    {
        logger << nl << e.getMessage() << std::endl;
		Delay(2000);
        return 1;
    }
    catch (std::exception exc)
    {
        logger << nl << exc.what() << std::endl;
		Delay(2000);
        return 1;
    }
    catch (...)
    {
        logger << nl << "Unknown exception" << std::endl;
		Delay(2000);
        return 1;
    }

    return 0;
}
