//test program
#include "AML.hh"

//tmp : logger is aimed only for internal use in AML
#include "Logger.hh"

//would be nice if we can put that in AML.hh
#ifdef __MINGW32__
#ifdef main
#undef main
#endif
#endif

using namespace std;

//TEMPORARY
void resetDisplay(int newW, int newH)
{
	SDLSurfaceFactory::getScreen()->resize(newW,newH);
	SDLSurfaceFactory::getScreen()->debug();
}

//Defining UserInput
class MyUserInput : public SDLEventHandler
{
	bool closing;
  int step;
public:
	MyUserInput() : closing(false),step(0) {}
	virtual bool handleKeyboardEvent (SDL_keysym &keysym, bool pressed)
	{
		switch( keysym.sym ) {
    		case SDLK_ESCAPE: if (pressed==false) closing=true; break;
    		case SDLK_F4: if (pressed==false) step++; break;
    		case SDLK_F5: if (pressed==true) SDLDisplaySurface::iconify(); break;
    		case SDLK_F6: if (pressed==true) SDLDisplaySurface::toggleFullScreen(); break;
	    default: break;
		}
		return true;
	}
	virtual bool handleResizeEvent(int w, int h) { resetDisplay(w,h); }
	virtual bool handleQuitEvent(void) { closing=true; return true; }
	bool closed(void) { return closing; }
  int getStep(void) { return step; }
};


int main(int argc, char* argv [] )
{
	
		Logger testlog;
		
		//mandatory call to initialize
		Config::setConfig(true,false,false,false,false);
		
   Sprite * s = new Sprite("../data/spritelib_gpl/paddle/arinoid.bmp");
		//Layer l;
		
    //l.add(s);
		
		MyUserInput ui;
		
    //creating the display //NOT RIGHT IF NO LOOP to handle the events... even a default "do nothing special" using SDLwrap is needed...
		Display screen;
		//1 ) looks like Display must be created before the sprite, otherwise there is no DisplayFormat to optimise the sprite
		//should be handled in sprite constructor... in progress...
		//2 ) error when sprite moves... ->TO INVESTIGATE
		
		testlog.add ("Display created");
		//http://geocities.com/smxrk/game-example.html
		while(ui.getStep()==0)
		{
			SDLEvent::handleEvents(ui);
			screen.update();
		}
		
		
		Camera * c=Camera::getCamera(); // has been created by Display
		
		testlog.add ("Camera created");
		
		//if not using layer, the sprite has to be attached directly to the camera
		c->add(s);
		//c.add(l);
		
		while(ui.getStep()==1)
		{
			SDLEvent::handleEvents(ui);
			screen.update();
		}
		
		
		Vector2 up(100.0,0.0);
		Vector2 down(-100.0,0.0);


		cout << "moving sprite up" << endl;
		s->move(up);

		while(ui.getStep()==2)
		{
			SDLEvent::handleEvents(ui);
			screen.update();
		}
		
	
		//cout << "moving layer down" << endl;
		//l.move(down);
		//screen.update();
		
		/*
		system("pause");
		cout << "moving sprite up" << endl;
		s->move(up);
		screen.update();
		
		system("pause");*/
		cout << "moving camera up" << endl;
		
		c->move(up);
		
		while(ui.getStep()==3)
		{
			SDLEvent::handleEvents(ui);
			screen.update();
		}
		
		return 0;
}


