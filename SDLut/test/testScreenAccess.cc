#include "TestCommon.hh" //to get argparser

using namespace SDLut;

Logger testlog("testScreenAccess");

class MyEngine
{

public:
    std::string fn;
    video::Rect imagepos;
    ArgParser arg;
    unsigned int test_it;
    video::Color bgcolor, pixel, objectivePixel;

    MyEngine( ArgParser ap) : arg(ap), test_it(0), bgcolor(240,128,128,255), pixel(50, 220, 80, 255)
    {
        fn = arg.get(1);
    }

    virtual ~MyEngine() {}

    bool init(int width, int height)
    {
        if (fn != "")
        {
            loadedimage = loader.load(fn);

            imagepos.resetx(0);
            imagepos.resety(0);
            imagepos.resetw( loadedimage->getWidth());
            imagepos.reseth( loadedimage->getHeight());
        }
        return true;
    }

    bool render(video::ScreenBuffer & screen) const
    {
        //No image
        if (fn == "")
        {
            //screen.fill(bgcolor);
            if (screen.getpixel(10,10) != bgcolor)
                App::getInstance().requestTermination(-1);
            break;

        }

        //PNG
        else

        {
            loadedimage = loader.load(fn);

            //http://www.libsdl.org/cgi/docwiki.cgi/SDL_SetAlpha

            pixel.setA(255);

            objectivePixel = loadedimage->getpixel(10,10).blendunder(pixel);

            loadedimage->setpixel(10,10, pixel);
            if (loadedimage->getpixel(10,10) != objectivePixel)
                App::getInstance().requestTermination(-1);
            break;



        } //PNG

        return true;
    }
};


//Main Program
int main(int argc, char** argv)
{
    ArgParser args(argc,argv);

    App::getInstance().initVideo(false,false,false);
    App::getInstance().setName ("SDLut test - Screen Access");

    testlog.enableFileLog("TestScreenAccess.log");

    App::getInstance().getDisplay().getScreenRequest().requestSize(300,240); // size is big enough for test. Using autodetected bpp
    App::getInstance().getDisplay().getScreenRequest().requestOpenGL(args.isOGL());

    int exitstatus = -1;

    std::auto_ptr<MyEngine> engine;
    engine.reset(new MyEngine(args));

    App::getInstance().getDisplay().resetInitCallback(*engine,&MyEngine::init);
    App::getInstance().getDisplay().resetNewFrameCallback(*engine,&MyEngine::newframe);
    App::getInstance().getDisplay().resetRenderCallback(*engine,&MyEngine::render);

    if (App::getInstance().getDisplay().show())
    {
        exitstatus = App::getInstance().getDisplay().mainLoop();
    }

    return exitstatus;
}




int main(int argc, char** argv)
{

#ifdef WK_OPENGL_FOUND
    bool ogl = true;
    if (argc > 1 && std::string(argv[1]) == "nogl" ) ogl = false;
#else
    bool ogl = false;
#endif

    //Starting with usual SDL window
    App::getInstance().initVideo(false,true,false);
    App::getInstance().setName ("SDLut::SDL test Color : Displayed Color order \"Red - Green - Blue - Purple if alpha is working otherwise White\"");

    //Setting Display size and BPP
    App::getInstance().getDisplay().setDisplay(800,600); // using autodetected bpp

    App::getInstance().getDisplay().getScreenRequest().requestOpenGL(ogl);

    //yellow background color (useful to test alpha / color key)
    App::getInstance().getDisplay().getScreenBuffer().setBGColor(Color (255,255,0));

    std::auto_ptr<MyEngine> engine(new MyEngine());

    App::getInstance().getDisplay().resetInitCallback(*engine,&MyEngine::init);
    App::getInstance().getDisplay().resetResizeCallback(*engine,&MyEngine::resize);
    App::getInstance().getDisplay().resetRenderCallback(*engine,&MyEngine::render);

    if (App::getInstance().getDisplay().show())
    {
        App::getInstance().getDisplay().mainLoop();
    }

    return 0;
}


