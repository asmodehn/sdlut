#include "testRendering.hh"

Logger testlog("TestTransparency");


class Test : public RenderingAssertEngine
{
    void regtestPixel()
    {
        //We expect data/test/transparency/png/* over data/test/transparency/png/stripe.gif
        //Measures made by hand, with The Gimp

        //building pixel test
        // rect of 1 pixel dark red around ( or grey in palettized )
        Color darkred(0x80,0x00,0x00);

        pos.push_back(Rect(0,0,1,1));
        color.push_back(darkred);
        pos.push_back(Rect(m_fgimg->getWidth()-1,0,1,1));
        color.push_back(darkred);
        pos.push_back(Rect(m_fgimg->getWidth()-1,m_fgimg->getHeight()-1,1,1));
        color.push_back(darkred);
        pos.push_back(Rect(0,m_fgimg->getHeight()-1,1,1));
        color.push_back(darkred);


        Color white(0xff,0xff,0xff);
        Color blue(0x40,0x80,0x80);
        Color black(0x00,0x00,0x00);

        // 5 sample pixel test to make sure transparency is progressive
        //measure made on gray16a.png with The GIMP.
        unsigned int xtst[5] = {1,21,42,62,83};
        unsigned int alphaval[5] ={255,212,128,48,0};

        //black stripe
        pos.push_back( Rect( xtst[0],10,1,1));
        black.resetA(alphaval[0]);
        color.push_back(black); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[1],10,1,1));
        black.resetA(alphaval[1]);
        color.push_back(black); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[2],10,1,1));
        black.resetA(alphaval[2]);
        color.push_back(black); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[3],10,1,1));
        black.resetA(alphaval[3]);
        color.push_back(black); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[4],10,1,1));
        black.resetA(alphaval[4]);
        color.push_back(black); //copy of color made. we can reuse it

        //blue stripe

        pos.push_back( Rect( xtst[0],30,1,1));
        blue.resetA(alphaval[0]);
        color.push_back(blue); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[1],30,1,1));
        blue.resetA(alphaval[1]);
        color.push_back(blue); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[2],30,1,1));
        blue.resetA(alphaval[2]);
        color.push_back(blue); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[3],30,1,1));
        blue.resetA(alphaval[3]);
        color.push_back(blue); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[4],30,1,1));
        blue.resetA(alphaval[4]);
        color.push_back(blue); //copy of color made. we can reuse it

        //white stripe

        pos.push_back( Rect( xtst[0],50,1,1));
        white.resetA(alphaval[0]);
        color.push_back(white); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[1],50,1,1));
        white.resetA(alphaval[1]);
        color.push_back(white); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[2],50,1,1));
        white.resetA(alphaval[2]);
        color.push_back(white); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[3],50,1,1));
        white.resetA(alphaval[3]);
        color.push_back(white); //copy of color made. we can reuse it
        pos.push_back( Rect( xtst[4],50,1,1));
        white.resetA(alphaval[4]);
        color.push_back(white); //copy of color made. we can reuse it

    }

public:

    Test(const Image & fgimage, const Image & bgimage, Logger & log, const ArgParser & ap)
            : RenderingAssertEngine(fgimage,bgimage,log,ap)
    {
        regtestPixel();
        m_log.enableFileLog("TestTransparency.log");
    }


    virtual ~Test()
    {
    }
};

int main(int argc, char** argv)
{
    ArgParser args(argc,argv);

    //Starting with usual SDL window
    App::getInstance().initVideo(false,true,false);
    App::getInstance().setName ("SDLut::video test Image");

    //Setting Display size and BPP
    App::getInstance().getDisplay().requestSize(300,240); // using autodetected bpp

    App::getInstance().getDisplay().requestOpenGL(args.isOGL());

    int exitstatus = -1;

    ImageLoader loader;
    std::string imgfile = args.get(1);
    std::string bgfile = args.get(2);
    if (imgfile != "" && bgfile != "" )
    {
        testlog << nl << "Image file : " << imgfile;
        std::auto_ptr<Image> testImg = loader.load(imgfile);
        testlog << nl << "Background Image file : " << bgfile;
        std::auto_ptr<Image> bgtestImg = loader.load(bgfile);
        Test teng(*testImg,*bgtestImg,testlog,args);
        RenderingTestEngine engine(testlog,teng);


        if (App::getInstance().getDisplay().show())
        {
            exitstatus = App::getInstance().getDisplay().mainLoop();
        }

    }
    else
    {
        testlog << nl << "Usage : " << args.getcmd() << " <Transparent_image> <background_image>";

    }
    return exitstatus;
}



