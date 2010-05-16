#include "TestCommon.hh" //to get argparser

using namespace SDLut;

Logger testlog("ScreenAccess");

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
        int x =assertedrect.getx(), y =assertedrect.gety();
        while ( y < (int)assertedrect.geth())
        {
            while ( x < (int)assertedrect.getw() )
            {
                res = res && (sb.getColorAt(x,y) == color);
            }
        }

        return res ;
    }
};

class Test : public TestEngine
{
    video::Rect testedrect;
    video::Color color;
public:

    Test(Logger& l, Assert & a, video::Rect testrect, video::Color c) : TestEngine(l,a), testedrect(testrect),color(c) {}
    bool resize(int width, int height)
    {
        //check rect size
        if (testedrect.getx() < 0) testedrect.resetx(0);
        if (testedrect.gety() < 0) testedrect.resety(0);
        if ( (int)(testedrect.getx() + testedrect.getw()) > width ) testedrect.resetw( width - testedrect.getx() );
        if ( (int)(testedrect.gety() + testedrect.geth()) > height ) testedrect.reseth( height - testedrect.gety() );

        return true;
    }
    bool render(video::ScreenBuffer& sb) const
    {
        if ( (1 == testedrect.geth() ) && ( testedrect.getw() == 1 ) )
        {
            sb.setColorAt( testedrect.getx(),testedrect.gety(),color );
        }
        else
        {
            //working around constness
            video::Rect dstrect = testedrect;
            sb.setColorAt( dstrect,color);
        }

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
    App::getInstance().getDisplay().requestSize(300,240); // using autodetected bpp
    App::getInstance().getDisplay().requestOpenGL(args.isOGL());

    int exitstatus = -1;

    ///testing pixel set
    video::Color color(Randomizer<unsigned char>::get(),Randomizer<unsigned char>::get(),Randomizer<unsigned char>::get());
    video::Rect pix(Randomizer<unsigned int>::get(0,300),Randomizer<unsigned int>::get(0,240 - 64 )); //keeping some space for logos...

    Assert asrt(testlog,args,pix,color);
    Test engine(testlog,asrt,pix,color);

    if (App::getInstance().getDisplay().show())
    {
        exitstatus = App::getInstance().getDisplay().mainLoop();
    }

    video::Rect scarea(Randomizer<unsigned int>::get(0,300),Randomizer<unsigned int>::get(0,240 - 64 )); //keeping some space for logos...
    scarea.resetw(Randomizer<unsigned int>::get(1,300 - scarea.getx()));
    scarea.reseth(Randomizer<unsigned int>::get(1,240-64 - scarea.gety()));

    //quick check
    if (scarea.getw() < 1)
    {
        scarea.resetw();
    }
    if (scarea.geth() < 1)
    {
        scarea.reseth();
    }

    ///testing rect fill

    //Declaring these here will construct them and reset the SDLut Callbacks as per parents classes in TestCommon.hh.
    Assert asrtbis(testlog,args,scarea,color);
    Test enginebis(testlog,asrtbis,scarea,color);

    //BUG
    //This should not be needed !!!
    //TODO : FIX IT
    App::getInstance().getDisplay().requestOpenGL(args.isOGL());
    if (App::getInstance().getDisplay().show())
    {
        exitstatus = (exitstatus == 0) && App::getInstance().getDisplay().mainLoop();
    }

    return exitstatus;
}

