#include "testRendering.hh"

Logger testlog("TestImage");

class Test : public RenderingAssertEngine
{
    void regtestPixel()
    {
        //We expect data/test/colortest/Colortest.xxxx
        //Measures made by hand, with The Gimp

        //building pixel test
        //top columns
        pos.push_back(Rect(10,10,1,1));
        color.push_back(Color(0xcc,0xcc,0xcc)); // light grey
        pos.push_back(Rect(100,10,1,1));
        color.push_back(Color(0xff,0xff,0x00)); //yellow
        pos.push_back(Rect(190,10,1,1));
        color.push_back(Color(0x00,0xff,0xff)); //light blue
        pos.push_back(Rect(280,10,1,1));
        color.push_back(Color(0x00,0xff,0x00)); //green
        pos.push_back(Rect(380,10,1,1));
        color.push_back(Color(0xff,0x00,0xff)); //pink
        pos.push_back(Rect(470,10,1,1));
        color.push_back(Color(0xff,0x00,0x00)); //red
        pos.push_back(Rect(560,10,1,1));
        color.push_back(Color(0x00,0x00,0xff)); //blue
        // middle rect
        pos.push_back(Rect(10,340,1,1));
        color.push_back(Color(0x00,0x00,0xff)); //blue
        pos.push_back(Rect(100,340,1,1));
        color.push_back(Color(0x13,0x13,0x13)); // dark grey
        pos.push_back(Rect(190,340,1,1));
        color.push_back(Color(0xff,0x00,0xff)); //pink
        pos.push_back(Rect(280,340,1,1));
        color.push_back(Color(0x13,0x13,0x13)); // dark grey
        pos.push_back(Rect(380,340,1,1));
        color.push_back(Color(0x00,0xff,0xff)); //light blue
        pos.push_back(Rect(470,340,1,1));
        color.push_back(Color(0x13,0x13,0x13)); // dark grey
        pos.push_back(Rect(560,340,1,1));
        color.push_back(Color(0xcc,0xcc,0xcc)); // light grey
        // lower rect
        pos.push_back(Rect(10,380,1,1));
        color.push_back(Color(0x08,0x3e,0x59)); // marine blue
        pos.push_back(Rect(120,380,1,1));
        color.push_back(Color(0xff,0xff,0xff)); // white
        pos.push_back(Rect(240,380,1,1));
        color.push_back(Color(0x3a,0x00,0x7e)); // purple
        pos.push_back(Rect(350,380,1,1));
        color.push_back(Color(0x13,0x13,0x13)); // dark grey
        pos.push_back(Rect(470,380,1,1));
        color.push_back(Color(0x00,0x00,0x00)); // black
        pos.push_back(Rect(500,380,1,1));
        color.push_back(Color(0x13,0x13,0x13)); // dark grey
        pos.push_back(Rect(540,380,1,1));
        color.push_back(Color(0x26,0x26,0x26)); // grey
        pos.push_back(Rect(560,380,1,1));
        color.push_back(Color(0x13,0x13,0x13)); // dark grey

    }

public:

    Test(const Image & fgimage, Color bgc, Logger & log, const ArgParser & ap)
            : RenderingAssertEngine(fgimage,bgc,log,ap)
    {
        regtestPixel();
        m_log.enableFileLog("TestImage.log");
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
    App::getInstance().getDisplay().requestSize(800,600); // using autodetected bpp

    App::getInstance().getDisplay().requestOpenGL(args.isOGL());

    int exitstatus = -1;

    ImageLoader loader;
    std::string imgfile = args.get(1);
    if (imgfile != "" )
    {
        std::auto_ptr<Image> testImg = loader.load(imgfile);
        Test teng(*testImg,Color(0,0,0),testlog,args);
        RenderingTestEngine engine(testlog,teng);
        if (App::getInstance().getDisplay().show())
        {
            exitstatus = App::getInstance().getDisplay().mainLoop();
        }
    }
    else
    {
        testlog << nl << " File : " << imgfile << "not found. Exiting.";
    }
    return exitstatus;
}


