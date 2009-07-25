#include "SDL.hh"
#include "Logger.hh"

#include <cstdlib>

using namespace RAGE;
using namespace RAGE::SDL;

Logger Log("Test Scene");

std::vector<Sprite*> logos;

class MyEngine
{
    int m_width;
    int m_height;

public:

	MyEngine()
	{
	}

    virtual ~MyEngine(){}

	bool init(int width, int height)
	{
	    /* initialize random seed: */
        srand ( time(NULL) );


	    m_width = width;
	    m_height = height;

        for ( int i=0; i<logos.size(); i++ )
        {
            int newx = rand() % m_width;
            int newy = rand() % m_height;
            logos[i]->moveto( newx, newy );
        }

		return true;
	}

	bool resize(int width, int height)
	{
	    m_width = width;
	    m_height = height;

		return true;
	}

    bool newframe(unsigned long framerate, unsigned long elapsedticks )
    {

        for ( int i=0; i<logos.size(); i++ )
        {
            int newx = rand() % m_width;
            int newy = rand() % m_height;
            logos[i]->moveto( newx, newy );
        }

        return true;
    }

	bool render(ScreenBuffer & screen) const
    {

		return true;
    }

};


int main(int argc, char** argv)
{
    Logger testlog("Test Log");

	bool ogl = false;
	if (argc > 1 && std::string(argv[1]) == "opengl" ) ogl = true;

    //Starting with usual SDL window
    App::getInstance().initVideo(false,ogl,true,false);
	App::getInstance().setName ("RAGE::SDL test Scene and refresh strategy");

    //Setting Display size and BPP
    App::getInstance().getDisplay().setDisplay(800,600); // using autodetected bpp

	std::auto_ptr<MyEngine> engine(new MyEngine());

	App::getInstance().getDisplay().resetInitCallback(&*engine,&MyEngine::init);
	App::getInstance().getDisplay().resetResizeCallback(&*engine,&MyEngine::resize);
	App::getInstance().getDisplay().resetNewFrameCallback(&*engine,&MyEngine::newframe);
	App::getInstance().getDisplay().resetRenderCallback(&*engine,&MyEngine::render);

    //TODO : improve this section by improving ImageLoader...
    SurfaceLoader loader;
    Image loadedimage( loader.load("data/smiley.bmp") );

    Sprite sp1, sp2;
    sp1.setImage(&loadedimage);
    sp2.setImage(&loadedimage);

    logos.push_back(&sp1);
    logos.push_back(&sp2);


    for ( int i=0; i< logos.size(); i++)
    {
        App::getInstance().getDisplay().getScene().add(logos[i]);
    }

    if(App::getInstance().getDisplay().show())
    {
       App::getInstance().getDisplay().mainLoop();
    }

    return 0;
}



