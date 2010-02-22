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

	Color _bgColor;

	Image * surf;

	std::string text;

public :
	Console(const Font & fnt = Font(),Color c = Color(0,0,0)) :_font(fnt),_bgColor(c),surf(NULL),text("")
	{
		//init();
		//draw();
		linesize = _font.getHeight();
	}

	bool init(int width, int height)
	{
		surf = new Image(width,height,8); //8 as magic number for minimum bpp.
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
		{
			text += newchar;
		}
		draw();
	}

    void add(std::string newstr)
    {
        text += newstr + '\n' ;
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
					std::auto_ptr<Image> textsurf = _font.render(line,Color(255,255,255),Font::Solid);
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

class MyEngine
{

public:

	Point consolePos;
	Console * console;

	MyEngine() : consolePos(0,0), console (NULL)
	{}

	void setConsole( Console * cons ) { console = cons;}

    virtual ~MyEngine()
	{
	}

	bool init(int width, int height)
	{
		console->init(width,height);
		console->add("Plz Use Keyboard To Write Text Down");
		return true;
	}

	bool resize(int width, int height)
	{
		console->resize(width,height);
		return true;
	}

	bool render(ScreenBuffer & screen) const
    {
		if (console !=NULL)
            console->surf->saveBMP("testingrender.bmp");
			screen.blit(*(console->surf),consolePos);
        return true;
    }

};


//Main Program
int main(int argc, char** argv)
{
	//BUGs
	//in foreign keyb language keys are not displayed correctly (a --> q, z --> w)
	//unknown caracters shown another caracter (ç --> h; è --> g)
	//IN OpenGL mode: caracters are not displayed on the program windows

    Logger testlog("Test Log");

	bool ogl = false;
	if ((argc > 1) && ( std::string(argv[1]) == "opengl" ) )
    {
        ogl = true;
    }

    //Setup example

    testlog << nl << " Enabling SDL Video... " << std::endl;
	App::getInstance().setName ("RAGE::SDL test - Font");
    App::getInstance().initVideo(false,ogl,false,false);
	App::getInstance().initText();

    testlog << nl << " Creating the User Interface... " << std::endl;

    Font font;

    if ((argc > 1 ) && !ogl)
    {
        //specific font
        font.setTTF(argv[1],24);
    }
    else if ( ogl && argc > 2 )
    {
        //specific font
        font.setTTF(argv[2],24);
    }

	Console cons(font);
	std::auto_ptr<MyEngine> engine(new MyEngine());
	engine->setConsole(&cons);

   //UI Creation
    MyUserInput ui;
	ui.setConsole(&cons);
    App::getInstance().getDisplay().getEventManager().setKeyboard(&ui);


	App::getInstance().getDisplay().resetInitCallback(*engine,&MyEngine::init);
	App::getInstance().getDisplay().resetResizeCallback(*engine,&MyEngine::resize);
	App::getInstance().getDisplay().resetRenderCallback(*engine,&MyEngine::render);


    if (! (App::getInstance().getDisplay().setDisplay(800,600)))
    {
        testlog << nl << "Display Creation FAILED !"<< std::endl;
        exit(0);
    }
    else if ( App::getInstance().getDisplay().show() )
    {
        App::getInstance().getDisplay().mainLoop();
    }

    return 0;
}


