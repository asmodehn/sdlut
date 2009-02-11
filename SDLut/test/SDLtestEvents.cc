#include "SDL.hh"
#include "Logger.hh"
using namespace RAGE;
using namespace RAGE::SDL;

#include <sstream>

Logger Log("Test Events");

class Console
{

	friend class MyEngine;

	//if member embedded (object not reference), error when destructing Font...
	//to debug -> copy / deletion problem
	const Font _font;
	short linesize;

	Color _bgColor;

	RGBSurface * surf;

	std::string text;

public :
	Console(const Font & fnt = Font(),Color c = Color(0,0,0)) :_font(fnt),_bgColor(c),surf(NULL),text(">")
	{
		//init();
		//draw();
		linesize = _font.getHeight();
	}

	bool init(int width, int height)
	{
		surf = new RGBSurface(_bgColor,width,height,8); //8 as magic number for minimum bpp.
		if (surf == NULL) return false;
		surf->optimise(); // Doesnt matter anyway we match the display one here.
		return true;
	}

	//WARNING : BUG here if trying to set to fullscreen using F6, then error, then trying to resize -> crash
	bool resize(int width, int height,bool keepcontent = true)
	{
		bool res = surf->resize(width,height,false);
		draw();
		return res;
	}

	void print(const std::string & newtext)
	{
		text += newtext + "\n";
		draw();
	}

	void add(char newchar)
	{
		if (newchar != '\0')
			text += newchar;
		draw();
	}

	void draw()
	{
    		std::stringstream ss(text); // Insert the text into a stream
			surf->fill(_bgColor);
			int i=0;
			char line[256];
			while ( ss.getline(line,255) && ss.good() )
			{
				std::auto_ptr<RGBSurface> textsurf = _font.render(line,Color(255,255,255),Font::Solid);
				assert(textsurf.get());
				surf->blit(*textsurf,Point (0,i * linesize));
				++i;
				//ss.ignore();//ignoring end of line
			}
	}

	~Console()
	{
		if (surf != NULL)
			delete surf,surf = NULL;
	}


};

//Defining general EventHandler
class MyGeneralHandler : public GeneralHandler
{
	friend class EventManager;
        bool _quitRequested;

		Console * cons;

        public:

			MyGeneralHandler(): GeneralHandler(), cons(NULL) {};
			virtual ~MyGeneralHandler() {};

		void setConsole(Console* csl)
		{
			cons = csl;
		}

			//Callbacks on Window / Display events
            virtual bool handleActiveEvent(bool gain, bool active, bool inputfocus, bool mousefocus)
		{
			if ( cons == NULL )	return false;
			else
			{
				cons->print("Active");
			}
			return true;
		}

            virtual bool handleResizeEvent(int w, int h)
		{

				App::getInstance().getWindow().resizeDisplay(w,h);
        		
				
			if ( cons == NULL )	return false;
			else
			{
				cons->print("Resize");
			}
			

				return true;
		}
            virtual bool handleExposeEvent()
		{
			 	if ( cons == NULL )	return false;
			else
			{
				cons->print("Expose");
			}
			

				return true;
		}
            //callback on platform-dependent windows manager event
            virtual bool handleSysWMEvent(void)
    {
        			 			if ( cons == NULL )	return false;
			else
			{
				cons->print("System WM");
			}
			

				return true;
    }

            //Callback on other Events
	    virtual bool handleUserEvent(Event::Type type, int code, void* data1, void* data2)
    {
        			 			if ( cons == NULL )	return false;
			else
			{
				cons->print("User Event");
			}
			

				return true;
    }


            //Callback on Quit Event
            virtual bool handleQuitEvent(void)
		{
        
        		if ( cons == NULL )	return false;
				else
				{
					cons->print("Quit");
				}
			
				_quitRequested=true;
				return true;
		}
            //Catch-all callback
            virtual bool handleEvent(Event &event)
		{
#if (DEBUG ==2)
        //Getting the details of the Event
        Log << nl << "Last chance handler : " << cevent.getType() << std::endl;
        return true;
#else

        return false;
#endif
		}

};

class MyKeyboard: public Keyboard
{public:

	Console *cons;

	MyKeyboard() : Keyboard(), cons(NULL) {}

	void setConsole (Console * newcons)
	{
		cons = newcons;
	}

	virtual bool handleKeyEvent (const Sym &s, bool pressed)
	{
		         bool res = false;
        #ifdef DEBUG
                   Log << nl << " Key Name : " << getKeyName(s.getKey()) <<  " pressed : " << pressed << std::endl;
                   res=true;
        #endif

	//default keyboard behaviour : ESC quits
            switch( s.getKey() )
            {
                case KEscape:
                if (pressed==false)
                {
#ifdef DEBUG
                    Log << nl << "Quit requested !" << std::endl;
#endif
                    _quitRequested=true;
                    res=true;
                }
                break;
                default:
                res = false;
            }
               return res;
	}
};

class MyMouse: public Mouse
{public:

	Console *cons;

	MyMouse() : Mouse(), cons(NULL) {}

	void setConsole (Console * newcons)
	{
		cons = newcons;
	}

	//Callbacks on Mouse Events
        virtual bool handleMouseMotionEvent (bool button_pressed, unsigned int x, unsigned int y,
                                             signed int xrel, signed int yrel)
		{
			if ( cons != NULL )
			{
				std::stringstream str;
				if ( button_pressed ) str<<"Mouse Drag : X=" << x << " Y=" << y << " Xrel=" << xrel << " Yrel=" << yrel ;
				else str<<"Mouse Moved : X=" << x << " Y=" << y << " Xrel=" << xrel << " Yrel=" << yrel ;
				cons->print( str.str() );
			}
			
			return true;
		}

        virtual bool handleMouseButtonEvent (Button button, unsigned int x, unsigned int y,
                                             bool pressed)
		{
			if ( cons != NULL )
			{
				std::string but=" Button";
				switch (button)
				{
				case Left: but="Left Button";
				case Middle: but="Middle Button";
				case Right: but="Right Button";
				case WheelUp: but="WheelUp Button";
				case WheelDown: but="WheelDown Button";
				default: but="Unknown Button";
				}

				std::stringstream str;
				str<< but << " X=" << x << "Y=" << y << " pressed? " << pressed;

				cons->print( str.str() );
			}
			return true;
		}

};


/*
//Defining UserInput
class MyUserInput : public TextInput
{
public:

	Console *cons;

	MyUserInput() : TextInput(), cons(NULL) {}

	void setConsole (Console * newcons)
	{
		cons = newcons;
	}

    virtual bool handleKeyEvent (const Sym &s, bool pressed)
    {
        bool res = false;
            switch( s.getKey() )
            {
                case KEscape:
                if (pressed==false)
                {
#ifdef DEBUG
                    Log << nl << "Quit requested !" << std::endl;
#endif

                    _quitRequested=true;
                    res=true;
                }
                break;
                case KF5:
                if (pressed==true)
                    App::getInstance().getWindow().iconify();
                res = true;
                break;
				case KF6:
                if (pressed==true)
                    App::getInstance().getWindow().setFullscreen(!App::getInstance().getWindow().isFullscreen());
                res = true;
                break;
				default: if (pressed == true) cons->add(s.getChar());
                res = true;
            }
        return res;
    }
};
*/
class MyEngine : public DefaultEngine
{

public:

	Point consolePos;
	Console * console;
	std::auto_ptr<RGBSurface> HelpMsg;
		
	MyEngine() : consolePos(0,0), console (NULL), HelpMsg(0)
	{}

	void setConsole( Console * cons ) { console = cons;}

    virtual ~MyEngine()
	{
	}

	bool init(int width, int height)
	{
		DefaultEngine::init(width,height);
		console->init(width,height - 2 * DefaultEngine::_logo.getHeight());
		consolePos.sety(DefaultEngine::_logo.getHeight());
		HelpMsg = console->_font.render("Plz Use Keyboard To Write Text Down", Color(0xFF, 0xFF, 0xFF), Font::Shaded, Color(0, 0, 0));
		return true;
	}

	bool resize(int width, int height)
	{
		DefaultEngine::resize(width,height);
		console->resize(width,height - 2 * DefaultEngine::_logo.getHeight());
		consolePos.sety(DefaultEngine::_logo.getHeight());
		return true;
	}

	void prerender()
	{
		//nothing for now
	}

	void render(VideoSurface & screen) const
    {
		DefaultEngine::render(screen);

		if (HelpMsg.get()) 
			screen.blit( *HelpMsg, Point::Point(5, 5) );

		if (console !=NULL)
			screen.blit(*(console->surf),consolePos);
    }

	void postrender()
	{
		//nothing for now
	}
};


//Main Program
int main(int argc, char** argv)
{

    Logger testlog("Test Log");

    //Setup example

    testlog << nl << " Enabling SDL Video... " << std::endl;
	App::getInstance().setName ("RAGE::SDL test - Font");
    App::getInstance().initVideo(false,false,false,false);
	App::getInstance().initText();

    testlog << nl << " Creating the User Interface... " << std::endl;
 
    App::getInstance().getWindow().setBGColor(Color (64,0,0));

    Font font;
    
    if (argc > 1)
    {
	//specific font
	font.setTTF(argv[1],24);
    }

	Console cons(font);
	MyEngine engine;
	engine.setConsole(&cons);
	
    MyGeneralHandler gh;
		gh.setConsole(&cons);
	MyKeyboard kb;
		kb.setConsole(&cons);
	MyMouse mouse;
		mouse.setConsole(&cons);
    App::getInstance().getWindow().getEventManager().setKeyboard(&kb);
	App::getInstance().getWindow().getEventManager().setMouse(&mouse);
   App::getInstance().getWindow().getEventManager().setGeneralHandler(&gh);


	//without this line the default engine is used
    App::getInstance().getWindow().setEngine(&engine);


    if (! (App::getInstance().getWindow().resetDisplay()))
    {
        testlog << nl << "Display Creation FAILED !"<< std::endl;
        exit(0);
    }
    else
    {
        App::getInstance().getWindow().mainLoop();
    }
    
    return 0;
}


