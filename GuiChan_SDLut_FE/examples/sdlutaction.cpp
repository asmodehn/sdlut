// Include all necessary headers.
#include <iostream>
#include <sstream>         // Used for int to string conversion
#include <guichan.hpp>
#include <guichan/sdlut.hpp>
#include "SDL.hh"

namespace globals
{
    gcn::Gui* gui;
}
#include "action.hpp"

using namespace RAGE;
using namespace RAGE::SDL;
using namespace globals;


gcn::SDLutInput* input;             // Input driver
gcn::SDLutGraphics* graphics;       // Graphics driver
gcn::SDLutOGLGraphics* oglgraphics;       // OGL Graphics driver
gcn::SDLutImageLoader* imageLoader; // For loading images
gcn::SDLutOGLImageLoader* oglimageLoader; // For loading images

Logger logger("Example"); //prefix

//Defining UserInput
class KeyboardInput : public Keyboard
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
						App::getInstance().getWindow().iconify();
					res = true;
					break;

				case Key_F6: //FullScreen
					if (pressed)
					{
						App::getInstance().getWindow().resizeDisplay(640, 480);
						App::getInstance().getWindow().setFullscreen(!App::getInstance().getWindow().isFullscreen());
					}
					res = true;
					break;
                
				default:
					res = false;
            }
		
		/*
         * Now that we are done polling and using SDLut events we pass
         * the leftovers to the SDLutInput object to later be handled by
         * the Gui. (This example doesn't require us to do this coz there
		 * is nothing to handle key input but will do it anyway to show
		 * how to set up an SDLut application with Guichan.)
        */
		if (!res)
		{
			input->pushInput(s, pressed);
			res = true;
		}
	
        return res;
    }
};

//Defining Mouse Input
class MouseInput : public Mouse
{
public:

	bool handleMouseButtonEvent (Button button, unsigned int x, unsigned int y, bool pressed)
	{
		bool res = false;

		if (!res)
		{
			input->pushInput(button, x, y, pressed);
			res = true;
		}

		return res;
	}

	bool handleMouseMotionEvent (bool button_pressed, unsigned int x, unsigned int y, signed int xrel, signed int yrel)
	{
		bool res = false;

		if (!res)
		{
			input->pushInput(x, y, xrel, yrel, button_pressed);
			res = true;
		}

		return res;
	}

};

class RenderEngine : public Engine
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

	void prerender(unsigned long deltaticks)
	{
		//Check Gui Logic
		gui->logic();        
	}

	void render(VideoSurface& screen) const
    {
		// Set the target for the graphics object to be the screen.
		// In other words, we will draw to the screen.
		graphics->setTarget(&screen);

		//Draw The Gui
		gui->draw();
    }
};

KeyboardInput* myKeyboardInput = NULL;
MouseInput* myMouseInput = NULL;
RenderEngine* myEngine = NULL;

void init(bool ogl = false)
{
	logger.enableFileLog("Example.Log");

	App::getInstance().setName("Example");

	if (! App::getInstance().initVideo(false, ogl, true, false) )
		throw std::logic_error( "Init Video Failed: " + GetError() );

	if (! App::getInstance().getWindow().resetDisplay(640, 480, 32)  )
		throw std::logic_error( "Create Surface Failed: " + GetError() );

}

void implement(bool ogl = false)
{
//GuiChan SDLuT Stuff
    imageLoader = new gcn::SDLutImageLoader();
    oglimageLoader = new gcn::SDLutOGLImageLoader();

	oglgraphics = new gcn::SDLutOGLGraphics(640, 480);
	graphics = new gcn::SDLutGraphics();
    
//Gui Initialization
    gui = new gcn::Gui();
	if (ogl)
	{
	    gcn::Image::setImageLoader(oglimageLoader);
		gui->setGraphics(oglgraphics); /*SDLuTOGLgraphics*/
	}
else
	{
		gcn::Image::setImageLoader(imageLoader);
		gui->setGraphics(graphics); /*SDLuTGraphics*/
	}

	input = new gcn::SDLutInput();
    gui->setInput(input);
    
	action::init();
	
//SDLuT Stuff
	myKeyboardInput = new KeyboardInput();
	App::getInstance().getWindow().getEventManager().setKeyboard(myKeyboardInput);

	myMouseInput = new MouseInput();
	App::getInstance().getWindow().getEventManager().setMouse(myMouseInput);

	myEngine = new RenderEngine();
	App::getInstance().getWindow().setEngine(myEngine);
}

void clean()
{
	action::halt();
	delete gui, gui = NULL;

    delete input, input = NULL;
    delete graphics, graphics = NULL;
	delete oglgraphics, oglgraphics = NULL;
    delete imageLoader, imageLoader = NULL;
	delete oglimageLoader, oglimageLoader = NULL;

	delete myKeyboardInput, myKeyboardInput = NULL;
	delete myMouseInput, myMouseInput = NULL;
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

		App::getInstance().getWindow().mainLoop();

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
