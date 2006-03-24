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

class MyEngine : public DefaultEngine
{

public:

	Point imagePos;
	Rect screenSize;
	
	MyEngine() : imagePos(0,0)
	{}

    virtual ~MyEngine(){}

	bool init(int width, int height)
	{
		DefaultEngine::init(width,height);
		imagePos = Point( (width - image->getWidth()) /2, (height - image->getHeight()) /2);
		screenSize = Rect(width,height);
		return true;
	}

	bool resize(int width, int height)
	{
		screenSize = Rect(width,height);
		return true;
	}

	void prerender()
	{
		//to be sure we dont go out of the screen surface...
		if ( imagePos.getx() > (int)(screenSize.getw() - image->getWidth()) )
			imagePos.setx(screenSize.getw() - image->getWidth());
		if ( imagePos.gety() > (int)(screenSize.geth() - image->getHeight()) )
			imagePos.sety(screenSize.geth() - image->getHeight());
		if (imagePos.getx() < 0) imagePos.setx(0);
		if (imagePos.gety() < 0) imagePos.sety(0);
	}

	void render(VideoSurface & screen) const
    {
		screen.blit(*image,imagePos);
    }

	void postrender()
	{
		imagePos += Point (1,1);
	}
};


//Main Program
int main(int argc, char** argv)
{

    Logger testlog("Test Log");

    //Setup example

    testlog << nl << " Enabling SDL Video... " << std::endl;
	App::getInstance().setName ("RAGE::SDL test - Video");
    App::getInstance().initVideo(false,false,true,false);

    testlog << nl << " Creating the User Interface... " << std::endl;
    //UI Creation
    MyUserInput ui;
    App::getInstance().getWindow()->getEventManager()->setKeyboard(&ui);

    App::getInstance().getWindow()->setBGColor(Color (64,0,0));
	
	//without this line the default engine is used
    //App::getInstance().getWindow()->setEngine(new MyEngine());


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


