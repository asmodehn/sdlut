#include "TestCommon.hh" //to get argparser

using namespace SDLut;
using namespace std;

RAGE::Logger testlog("testPixel");

class MyEngine
{

public:
    std::auto_ptr<video::Image> loadedimage;
    std::string fn;
    video::Rect imagepos;
    ArgParser arg;
    unsigned int test_it;
    video::Color bgcolor, pixel, objectivePixel;
    video::ImageLoader loader;

    MyEngine( ArgParser _arg) : imagepos(), arg(_arg), test_it(0), bgcolor(240,128,128,255), pixel(50, 220, 80, 255)
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
    App::getInstance().setName ("SDLut test - Pixel");

    testlog.enableFileLog("TestPixel.log");

    App::getInstance().getDisplay().getScreenRequest().requestSize(300,240); // using autodetected bpp

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

