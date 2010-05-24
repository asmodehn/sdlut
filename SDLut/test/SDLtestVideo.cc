#include "SDL.hh"
#include "Logger.hh"

using namespace Core;

using namespace SDLut;
using namespace SDLut::video;

Core::Logger testlog("TestVideo");

class MyEngine
{

public:

    std::auto_ptr<Image> loadedimage;
    mutable Rect imagepos;

    MyEngine( const std::string & imagefilename) : imagepos()
    {
        ImageLoader loader;
        loadedimage = loader.load(imagefilename);
    }

    virtual ~MyEngine() {}

    bool init(int width, int height)
    {
        imagepos.resetx( (width - loadedimage->getWidth()) /2);
        imagepos.resety( (height - loadedimage->getHeight()) /2);
        imagepos.resetw( loadedimage->getWidth());
        imagepos.reseth( loadedimage->getHeight());
        return true;
    }

    bool resize(int width, int height)
    {
        imagepos.resetx( (width - loadedimage->getWidth()) /2);
        imagepos.resety( (height - loadedimage->getHeight()) /2);
        imagepos.resetw( loadedimage->getWidth());
        imagepos.reseth( loadedimage->getHeight());
        return true;
    }

    bool render(ScreenBuffer & screen) const
    {

        screen.blit(*loadedimage, imagepos );

        video::Color rect_color(80,80,96,100);
        for (unsigned int i = 0; i<50; i++)
        {
            for (unsigned int j = 0; j<50; j++)
            {
                screen.setColorAt(imagepos.getx() + i, imagepos.gety() + j, rect_color);
            }
        }

        return true;
    }
};


//Main Program
int main(int argc, char** argv)
{
    std::string imgFile("");
#ifdef WK_OPENGL_FOUND
    bool ogl = true;
    if (argc > 1)
    {
        if (std::string(argv[1]) == "nogl" )
        {
            //if first option was "nogl" then adjust filename
            ogl = false;
            imgFile = argv[2];
        }
        else
        {
            imgFile = std::string(argv[1]);
        }
    }
#else
    if ( argc > 1)
    {
        imgFile = std::string(argv[1]);
    }
    bool ogl = false;
#endif

    //Setup example

    testlog << nl << " Enabling SDL Video... " << std::endl;
    App::getInstance().initVideo(false,true,false);

    App::getInstance().setName ("SDLut::SDL test - Video");

    //setting proper opengl value ( before the engine, otherwise wrong image format )
    App::getInstance().getDisplay().requestOpenGL(true);

    //if argument we load the image in the test engine
    std::auto_ptr<MyEngine> engine;
    if ( argc > 1 )
    {
        engine.reset(new MyEngine(imgFile));


        App::getInstance().getDisplay().resetInitCallback(*engine,&MyEngine::init);
        App::getInstance().getDisplay().resetResizeCallback(*engine,&MyEngine::resize);
        App::getInstance().getDisplay().resetRenderCallback(*engine,&MyEngine::render);

        //otherwise we use the default engine only.
    }

    if (! (App::getInstance().getDisplay().setDisplay(800,600,24)))
    {
        testlog << nl << "Display Creation FAILED !"<< std::endl;
    }
    else if ( App::getInstance().getDisplay().show() )
    {
        App::getInstance().getDisplay().mainLoop();
        //think about automatic exit after timeout...
    }

    return 0;
}


