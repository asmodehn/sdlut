#include "TestCommon.hh" //to get argparser

using namespace SDLut;

Logger testlog("ScreenBlit");

class Assert : public AssertEngine
{
    video::Rect assertedrect;
    video::Color color;
public:
    Assert(Logger& l, ArgParser& ap,video::Rect assertrect, video::Color c)
            : AssertEngine(l,ap), assertedrect(assertrect), color(c)
    {
        if ( ! testlog.isFileLogEnabled() ) testlog.enableFileLog("TestScreenAccess.log");
    }

    bool assertresize(int width, int height)
    {
        if (assertedrect.getx() < 0) assertedrect.resetx(0);
        if (assertedrect.gety() < 0) assertedrect.resety(0);
        if ( (int)(assertedrect.getx() + assertedrect.getw() ) > width ) assertedrect.resetw( width - assertedrect.getx() );
        if ( (int)(assertedrect.gety() + assertedrect.geth() ) > height ) assertedrect.reseth( height - assertedrect.gety() );

        return true;
    }
    bool assertrender(video::ScreenBuffer& sb) const
    {
        bool res = true;

        for ( unsigned int y = 0; y < assertedrect.geth(); y++)
        {
            for ( unsigned int x = 0; x < assertedrect.getw(); x ++)
            {
                video::Color gotclr = sb.getColorAt(x + assertedrect.getx(),y + assertedrect.gety());
                res = res && ( gotclr== color);
            }
        }

        if ( ! res ) logError("Error : Wrong color detected");
        return res ;
    }
};

class Test : public TestEngine
{
    video::Rect testedrect;
    video::Color color;
    video::Image img;
public:

    Test(Logger& l, Assert & a, video::Rect testrect, video::Color c)
            : TestEngine(l,a), testedrect(testrect),color(c)
    {
    }

    bool resize(int width, int height)
    {
        //check rect size
        if (testedrect.getx() < 0) testedrect.resetx(0);
        if (testedrect.gety() < 0) testedrect.resety(0);
        if ( (int)(testedrect.getx() + testedrect.getw()) > width ) testedrect.resetw( width - testedrect.getx() );
        if ( (int)(testedrect.gety() + testedrect.geth()) > height ) testedrect.reseth( height - testedrect.gety() );

        bool res = img.resize(testedrect.getw(),testedrect.geth());
        res = res && img.fill(color);

        //img.saveBMP("beforetest.bmp");
        return res;
    }

    bool newframe(unsigned long framerate, unsigned long deltaticks) // not mandatory
    {
        //static int cnt=0;
        //std::stringstream fname;
        //fname << "render_" << cnt++ << ".bmp";
        //testlog << nl << "DEBUG : " << fname.str() << " created";
        //img.saveBMP(fname.str());
        return true;
    }

    bool render(video::ScreenBuffer& sb) const
    {
        //work around for constness of render
        video::Rect dst = testedrect;

        //BUG WORKAROUND !!!
        //refresh doesnt seem to work properly here...
        // TOFIX !!!
        //sb.requestFullRefresh();

        return sb.blit( img, dst );


        //TODO : test blitting with different sized rect ( bigger smaller than image... )
        // need to choose policy !!!

    }
};

int main(int argc, char** argv)
{
    ArgParser args(argc,argv);

    //Starting with usual SDL window
    App::getInstance().initVideo(false,true,false);
    App::getInstance().setName ("SDLut::video Screen Blitting test ");

    //Setting Display size and BPP
    App::getInstance().getDisplay().requestSize(300,240); // using autodetected bpp
    App::getInstance().getDisplay().requestOpenGL(args.isOGL());

    int exitstatus = -1;

    ///testing pixel set
    video::Color color(Randomizer<unsigned char>::get(),Randomizer<unsigned char>::get(),Randomizer<unsigned char>::get());
    video::Rect rct(Randomizer<unsigned int>::get(0,300),Randomizer<unsigned int>::get(0,240 - 64 )); //keeping some space for logos...
    rct.resetw(Randomizer<unsigned int>::get(1,300 - rct.getx()));
    rct.reseth(Randomizer<unsigned int>::get(1,240-64 - rct.gety()));
    //quick check
    if (rct.getw() < 1) rct.resetw();
    if (rct.geth() < 1) rct.reseth();

    Assert asrt(testlog,args,rct,color);
    Test engine(testlog,asrt,rct,color);

    if (App::getInstance().getDisplay().show())
    {
        exitstatus = App::getInstance().getDisplay().mainLoop();
    }

    return exitstatus;
}


