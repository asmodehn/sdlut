#include "SDL.hh"
using namespace RAGE;
using namespace RAGE::SDL;


//Defining UserInput
class MyUserInput : public Keyboard
{
public:

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
                    App::getInstance().getWindow()->iconify();
                res = true;
                break;
				case KF6:
                if (pressed==true)
                    App::getInstance().getWindow()->setFullscreen(!App::getInstance().getWindow()->isFullscreen());
                res = true;
                break;
                default:
                res = false;
            }
        return res;
    }
};

class Console
{

	friend class MyEngine;

	//if member embedded (object not reference), error when destructing Font...
	//to debug -> copy / deletion problem
	const Font & _font;

	Color _bgColor;

	RGBSurface * surf;

public :
	Console(const Font & fnt = Font(),Color c = Color(0,0,0)) :_font(fnt),_bgColor(c),surf(NULL)
	{
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
		surf->fill(_bgColor);
		return res;
	}

	~Console()
	{
		if (surf != NULL)
			delete surf,surf = NULL;
	}


};

class MyEngine : public DefaultEngine
{

public:

	Point consolePos;
	Console * console;

	MyEngine() : consolePos(0,0), console (NULL)
	{}

	void setConsole( Console * cons ) { console = cons;}

    virtual ~MyEngine(){}

	bool init(int width, int height)
	{
		DefaultEngine::init(width,height);
		console->init(width,height - 2 * DefaultEngine::image->getHeight());
		consolePos.sety(DefaultEngine::image->getHeight());
		return true;
	}

	bool resize(int width, int height)
	{
		DefaultEngine::resize(width,height);
		console->resize(width,height - 2 * DefaultEngine::image->getHeight());
		consolePos.sety(DefaultEngine::image->getHeight());
		return true;
	}

	void prerender()
	{
		//nothing for now
	}

	void render(VideoSurface & screen) const
    {
		DefaultEngine::render(screen);
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
    App::getInstance().initVideo(false,false,true,false);
	App::getInstance().initText();

    testlog << nl << " Creating the User Interface... " << std::endl;
    //UI Creation
    MyUserInput ui;
    App::getInstance().getWindow()->getEventManager()->setKeyboard(&ui);

    App::getInstance().getWindow()->setBGColor(Color (64,0,0));

	Font font("data/echelon.ttf");
	Console cons(font);
	MyEngine engine;
	engine.setConsole(&cons);
	
	//without this line the default engine is used
    App::getInstance().getWindow()->setEngine(&engine);


    if (! (App::getInstance().getWindow()->resetDisplay()))
    {
        testlog << nl << "Display Creation FAILED !"<< std::endl;
        exit(0);
    }
    else
    {

        App::getInstance().getWindow()->mainLoop();

    }
    return 0;
}


