#include "SDL.hh"
#include "Logger.hh"
using namespace RAGE;
using namespace RAGE::SDL;

Logger Log("Test Font");

class Console
{

	friend class MyEngine;

	//if member embedded (object not reference), error when destructing Font...
	//to debug -> copy / deletion problem
	const Font _font;

	Color _bgColor;

	RGBSurface * surf;

	std::string text;

public :
	Console(const Font & fnt = Font(),Color c = Color(0,0,0)) :_font(fnt),_bgColor(c),surf(NULL),text(">")
	{
		//init();
		//draw();
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
		text += newtext;
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
		RGBSurface * textsurf = _font.render(text,Color(255,255,255),Font::Solid);
		assert(textsurf);
		surf->fill(_bgColor);
		surf->blit(*textsurf);
		delete textsurf;
	}

	~Console()
	{
		if (surf != NULL)
			delete surf,surf = NULL;
	}


};

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

class MyEngine : public DefaultEngine
{

public:

	Point consolePos;
	Console * console;
	RGBSurface *HelpMsg;
		
	MyEngine() : consolePos(0,0), console (NULL)
	{ HelpMsg = NULL; }

	void setConsole( Console * cons ) { console = cons;}

    virtual ~MyEngine()
	{
		if (HelpMsg != NULL)
			delete HelpMsg, HelpMsg = NULL;
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

		if (HelpMsg != NULL) 
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
	
   //UI Creation
    MyUserInput ui;
	ui.setConsole(&cons);
    App::getInstance().getWindow().getEventManager().setKeyboard(&ui);


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


