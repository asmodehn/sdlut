#include "TestCommon.hh" // for argParser only

Logger testlog("RectTest");

using namespace SDLut::video;

class RectTester
{
    Rect r1,r2;

    public:
    RectTester() : r1(-15,-4,63,37), r2(34,-12,56,87)
    {
        testlog.enableFileLog("TestRect.log");
    }

    ~RectTester()
    {
    }

    //first tests to run, they will be used later
    bool testgetx() { return r1.getx() == -15 && r2.getx() == 34; }
    bool testgety() { return r1.gety() == -4 && r2.gety()== -12; }
    bool testgetw() { return r1.getw() == 63 && r2.getw() == 56; }
    bool testgeth() { return r1.geth() == 37 && r2.geth() == 87; }

    //we use testget* to make sure the rect are returned to ther initial coordinates
    bool testsetx() { r2.resetx(r1.getx()); r1.resetx(42); bool res=(r1.getx() == 42); r1.resetx(r2.getx()); r2.resetx(34); return res && testgetx(); }
    bool testsety() { r2.resety(r1.gety()); r1.resety(42); bool res=(r1.gety() == 42); r1.resety(r2.gety()); r2.resety(-12); return res && testgety(); }
    bool testsetw() { r2.resetw(r1.getw()); r1.resetw(42); bool res=(r1.getw() == 42); r1.resetw(r2.getw()); r2.resetw(56); return res && testgetw(); }
    bool testseth() { r2.reseth(r1.geth()); r1.reseth(42); bool res=(r1.geth() == 42); r1.reseth(r2.geth()); r2.reseth(87); return res && testgeth(); }

    bool testinf() { Rect res = r1.inf(r2); return res.getx() == 34 && res.gety() == -4 && res.getw() == 14 && res.geth() == 37; }
    bool testsup() { Rect res = r1.sup(r2); return res.getx() == -15 && res.gety() ==-12 && res.getw() == 105 && res.geth()==87; }

    bool testmult() { Rect res = r1 * 3; return res.getx() == -15 && res.gety() == -4 && res.getw() == 63*3 && res.geth() == 37*3; }
    bool testdiv() { Rect res = r1 / 3; return res.getx() == -15 && res.gety() == -4 && res.getw() == 63/3 && res.geth() == 37/3; }
    bool testequal() { Rect r1eq = Rect(r1.getx(),r1.gety(),r1.getw(),r1.geth()); return r1eq == r1; }
    bool testdiff()
    {
        Rect r1d1 = Rect(r1.getx() -1,r1.gety(),r1.getw(),r1.geth() );
        Rect r1d2 = Rect(r1.getx() ,r1.gety() +3,r1.getw(),r1.geth() );
        Rect r1d3 = Rect(r1.getx() ,r1.gety(),r1.getw() -5,r1.geth() );
        Rect r1d4 = Rect(r1.getx(),r1.gety(),r1.getw(),r1.geth() +4 );
        return r1 != r1d1 && r1 != r1d2 && r1 != r1d3 && r1 != r1d4;
    }

    int testall()
    {
        int status = 0;
        if ( ! testgetx() ) { testlog << nl << "testgetx() failed "; status = -1; }
        if ( ! testgety() ) { testlog << nl << "testgety() failed "; status = -2; }
        if ( ! testgetw() ) { testlog << nl << "testgetw() failed "; status = -3; }
        if ( ! testgeth() ) { testlog << nl << "testgeth() failed "; status = -4; }

        if ( ! testsetx() ) { testlog << nl << "testsetx() failed "; status = -5; }
        if ( ! testsety() ) { testlog << nl << "testsety() failed "; status = -6; }
        if ( ! testsetw() ) { testlog << nl << "testsetw() failed "; status = -7; }
        if ( ! testseth() ) { testlog << nl << "testseth() failed "; status = -8; }

        if ( ! testsup() ) { testlog << nl << "testsup() failed "; status = -9; }
        if ( ! testinf() ) { testlog << nl << "testinf() failed "; status = -10; }
        if ( ! testmult() ) { testlog << nl << "testmult() failed "; status = -11; }
        if ( ! testdiv() ) { testlog << nl << "testdiv() failed "; status = -12; }
        if ( ! testequal() ) { testlog << nl << "testequal() failed "; status = -13; }
        if ( ! testdiff() ) { testlog << nl << "testdiff() failed "; status = -14; }

        return status;
    }

};






int main(int argc, char** argv)
{
    ArgParser args(argc,argv);

    //Starting with usual SDL window
    App::getInstance().initVideo(false,true,false);
    App::getInstance().setName ("SDLut::video test Rect");


    RectTester rt;

    int exitstatus = rt.testall();
    //Setting Display size and BPP
//    App::getInstance().getDisplay().setDisplay(640,480); // using autodetected bpp

//    App::getInstance().getDisplay().getScreenBuffer().setOpenGL(args.isOGL());

//    int exitstatus = -1;

 //       if (App::getInstance().getDisplay().show())
 //       {
 //           exitstatus = App::getInstance().getDisplay().mainLoop();
 //       }
    return exitstatus;
}


