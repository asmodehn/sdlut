#include "SDL.hh"

using namespace SDLut;
using namespace SDLut::video;

class MyEngine
{


    Image* red;
    Image* green;
    Image* blue;
    Image* alpha;

public:

    MyEngine() : red(0), green(0),blue(0),alpha(0)
    {
    }

    virtual ~MyEngine()
    {
        delete red;
        delete green;
        delete blue;
        delete alpha;
    }

    bool init(int width, int height)
    {

        return resize(width,height);
    }

    bool resize(int width, int height)
    {
        delete red;
        delete green;
        delete blue;
        delete alpha;
        red = new Image(width/4,height,32);
        red->fill(Color(255,0,0));
        green = new Image(width/4,height,32);
        green->fill(Color(0,255,0));
        blue = new Image(width/4,height,32);
        blue->fill(Color(0,0,255,128));
        alpha = new Image(width-red->getWidth()-green->getWidth()-blue->getWidth(),height,32, true);
        alpha->fill(Color(255,255,255,128));


        std::cout << "Red Pixel : " << std::hex << red->getpixel(0,0) << std::endl;
        std::cout << "Green Pixel : " << std::hex << green->getpixel(0,0)<< std::endl;
        std::cout << "Blue Pixel : " << std::hex << blue->getpixel(0,0)<< std::endl;
        std::cout << "Alpha Pixel : " << std::hex << alpha->getpixel(0,0)<< std::endl;

        return true;
    }

    bool render(ScreenBuffer & screen) const
    {
        Rect red_dst(0,0,red->getWidth(),red->getHeight());
        screen.blit(*red,red_dst);
        Rect green_dst(0 + red->getWidth(),0,green->getWidth(),green->getHeight());
        screen.blit(*green,green_dst);
        Rect blue_dst(0 + red->getWidth() + green->getWidth(), 0,blue->getWidth(),blue->getHeight());
        screen.blit(*blue,blue_dst);
        Rect alpha_dst(0 + red->getWidth() + green->getWidth() / 2, 0,alpha->getWidth(),alpha->getHeight());
        screen.blit(*alpha,alpha_dst);

        return true;
    }

};


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


