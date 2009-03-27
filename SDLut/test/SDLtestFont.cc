#include "SDL.hh"
#include "Logger.hh"
using namespace RAGE;
using namespace RAGE::SDL;

Logger Log("Test Font");

#include <sstream>
#include <string>
#include <algorithm>

class Console
{

	friend class MyEngine;

	//if member embedded (object not reference), error when destructing Font...
	//to debug -> copy / deletion problem
	const Font _font;
	short linesize;

	RGBColor _bgColor;

	RGBSurface * surf;

	std::string text;

public :
	Console(const Font & fnt = Font(),RGBColor c = RGBColor(0,0,0)) :_font(fnt),_bgColor(c),surf(NULL),text("")
	{
		//init();
		//draw();
		linesize = _font.getHeight();
	}

	bool init(int width, int height)
	{
		surf = new RGBSurface(width,height,8); //8 as magic number for minimum bpp.
		surf->fill(_bgColor);
		if (surf == NULL) return false;
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
		int nb_line = std::count(text.begin(), text.end(), '\n');
		int current_line = 0;
		int nb_line_toshow = (int)((surf->getHeight()-linesize)/linesize);
		char line[256];

		while ( ss.good() )
		{
			ss.getline(line,255);
			++current_line;
			if (current_line > (nb_line-nb_line_toshow))
			{
				if ((std::string)line != "")
				{
					std::auto_ptr<RGBSurface> textsurf = _font.render(line,RGBColor(255,255,255),Font::Solid);
					assert(textsurf.get());
					surf->blit(*textsurf,Point (0,i * linesize));
				}
				++i;
			}
		}
	}

	~Console()
	{
		if (surf != NULL)
			delete surf,surf = NULL;
	}


};

//Defining UserInput
class MyUserInput : public TextInput //Should TextInput have a DefaultTextI nput with default behavior too ???
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
		TextInput::handleKeyEvent(s,pressed);

		if (pressed == true) cons->add(s.getChar());
        
		return true;
    }
};

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
		console->init(width,height - 2 * DefaultEngine::_logo->getHeight());
		consolePos.sety(DefaultEngine::_logo->getHeight());
		HelpMsg = console->_font.render("Plz Use Keyboard To Write Text Down", RGBColor(0xFF, 0xFF, 0xFF), Font::Shaded, RGBColor(0, 0, 0));
		return true;
	}

	bool resize(int width, int height)
	{
		DefaultEngine::resize(width,height);
		console->resize(width,height - 2 * DefaultEngine::_logo->getHeight());
		consolePos.sety(DefaultEngine::_logo->getHeight());
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
 
    App::getInstance().getWindow().setBGColor(RGBColor (64,0,0));

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


    if (! (App::getInstance().getWindow().resetDisplay(800,600)))
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


