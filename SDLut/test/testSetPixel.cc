
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

    bool newframe(unsigned long framerate, unsigned long lastframe)
    {

    }

    bool render(video::ScreenBuffer & screen) const
    {
        //No image
        if (fn == "")
        {
            switch (test_it)
            {
            case 1: //set pixel on screenbuffer
                //screen.fill(bgcolor);
                screen.setpixel(10,10, pixel);
                if (screen.getpixel(10,10) != pixel)
                    App::getInstance().requestTermination(-1); //OGL error here
                break;

            case 2: //set pixel w alpha on screenbuffer
                //screen.fill(bgcolor);

                pixel.setA(128);
                objectivePixel = screen.getpixel(10,10).blendunder(pixel);
                screen.setpixel(10,10, pixel);
                pixel.setA(255);

                if (screen.getpixel(10,10) != objectivePixel)
                    App::getInstance().requestTermination(-1);
                break;

            }
        }

        //PNG
        else

        {
            loadedimage = loader.load(fn);

            //http://www.libsdl.org/cgi/docwiki.cgi/SDL_SetAlpha

            switch (test_it)
            {
            case 0: //set pixel wo alpha on image, get on image
                pixel.setA(255);

                objectivePixel = loadedimage->getpixel(10,10).blendunder(pixel);

                loadedimage->setpixel(10,10, pixel);
                if (loadedimage->getpixel(10,10) != objectivePixel)
                    App::getInstance().requestTermination(-1);
                break;

            case 1: //set pixel w alpha on image, get on image
                pixel.setA(128);

                objectivePixel = loadedimage->getpixel(12,12).blendunder(pixel);

                loadedimage->setpixel(12,12, pixel);
                if (loadedimage->getpixel(12,12) != objectivePixel)
                    App::getInstance().requestTermination(-1);
                break;

            case 2: //no bg, set pixel wo alpha on image, blit image, get on screen
                pixel.setA(255);

                objectivePixel = loadedimage->getpixel(14,14).blendunder(pixel);
                objectivePixel.setA(255);

                loadedimage->setpixel(14,14, pixel);
                screen.blit(*loadedimage.get(), imagepos);
                if (screen.getpixel(14,14) != objectivePixel)
                    App::getInstance().requestTermination(-1);
                break;

            case 3: //no bg, set pixel w alpha on image, blit image, get on screen
                pixel.setA(128);

                objectivePixel = loadedimage->getpixel(16,16).blendunder(pixel);
                objectivePixel.setA(255);

                loadedimage->setpixel(16,16, pixel);
                screen.blit(*loadedimage.get(), imagepos);
                pixel.setA(255);
                if (screen.getpixel(16,16) != objectivePixel)
                    App::getInstance().requestTermination(-1);
                break;

            default:
                App::getInstance().requestTermination(0); //OK
                break;

            }


        } //PNG



        test_it++; //increment

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


