#include "TestCommon.hh" //to get argparser

using namespace SDLut;

Logger testlog("ScreenBGColor");

class Assert : public AssertEngine
    {
        video::Rect pixTL, pixTR, pixBL, center;
        video::Color m_bgc;

        public:
        Assert(Logger& l, ArgParser& ap, video::Color bgc) : AssertEngine(l,ap), m_bgc(bgc)
        {
            //All Rects must already be (0,0,1,1) as per Rect default
            }

        bool assertresize(int width, int height)
        {
            pixTR.resetx( width -1 );
            pixBL.resety( height -1 );
            center.resetx( width /2 );
            center.resety( height /2);
             return true;
        }
        bool assertrender(video::ScreenBuffer& screen) const
        {
            bool res = true;
            res = res && (m_bgc == screen.getColorAt(pixTL.getx(), pixTL.gety()));
            res = res && (m_bgc == screen.getColorAt(pixTR.getx(), pixTR.gety()));
            res = res && (m_bgc == screen.getColorAt(pixBL.getx(), pixBL.gety()));
            res = res && (m_bgc == screen.getColorAt(center.getx(), center.gety()));
            return res;
        }
    };

class Test : public TestEngine
    {
        video::Color m_bgc;
        public:
        Test(Logger& l, Assert & a, video::Color bgc) : TestEngine(l,a), m_bgc(bgc)
        {

        }
        bool resize(int width, int height)
        {

            return true;
        }
        bool render(video::ScreenBuffer& screen) const
        {
             screen.setBGColor(m_bgc);
             return true;
        }
};

int main(int argc, char** argv)
{
    ArgParser args(argc,argv);

    //Starting with usual SDL window
    App::getInstance().initVideo(false,true,false);
    App::getInstance().setName ("SDLut::video Dumb test ");

    //Setting Display size and BPP
    App::getInstance().getDisplay().getScreenInfo().requestSize(300,240); // using autodetected bpp
    App::getInstance().getDisplay().getScreenInfo().requestOpenGL(args.isOGL());

    int exitstatus = -1;

    video::Color randcolor(Core::Randomizer<unsigned char>::get(), Core::Randomizer<unsigned char>::get(),Core::Randomizer<unsigned char>::get());

    Assert asrt(testlog,args, randcolor);
    Test engine(testlog,asrt, randcolor);

    if (App::getInstance().getDisplay().show())
    {
        exitstatus = App::getInstance().getDisplay().mainLoop();
    }

    return exitstatus;
}


