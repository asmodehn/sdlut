#include "SDL.hh"
#include "Logger.hh"
using namespace RAGE;

using namespace SDLut;
using namespace SDLut::video;

RAGE::Logger testlog("TestVideo");

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

    App::getInstance().getDisplay().getScreenBuffer().setBGColor(Color (128,0,0));


    //setting proper opengl value ( before the engine, otherwise wrong image format )
    App::getInstance().getDisplay().getScreenBuffer().setOpenGL(ogl);

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


