#include "TestCommon.hh" // for argParser only

Logger testlog("testRect");

using namespace SDLut::video;

class RectTester
{
    Rect r1,r2,r3;

public:
    RectTester()
            : r1(), //testing default position is top left (0,0)
            r2(-15,-4), //testing default size is pixel size (1,1)
            r3(34,-12,56,87)
    {
        testlog.enableFileLog("TestRect.log");
    }

    ~RectTester()
    {
    }

    //first tests to run, they will be used later
    bool testgetx()
    {
        return r1.getx() == 0 && r2.getx() == -15 && r3.getx() == 34;
    }
    bool testgety()
    {
        return r1.gety() == 0 && r2.gety() == -4 && r3.gety()== -12;
    }
    bool testgetw()
    {
        return r1.getw() == 1 && r2.getw() == 1 && r3.getw() == 56;
    }
    bool testgeth()
    {
        return r1.geth() == 1 && r2.geth() == 1 && r3.geth() == 87;
    }

    //we use testget* to make sure the rect are returned to ther initial coordinates
    bool testsetx()
    {
        r1.resetx(r2.getx());
        r2.resetx(42);
        bool res=(r2.getx() == 42);
        r2.resetx(r1.getx());
        r1.resetx(); //testing default
        return res && testgetx();
    }
    bool testsety()
    {
        r1.resety(r2.gety());
        r2.resety(42);
        bool res=(r2.gety() == 42);
        r2.resety(r1.gety());
        r1.resety(); // testing default
        return res && testgety();
    }
    bool testsetw()
    {
        r1.resetw(r2.getw());
        r2.resetw(42);
        bool res=(r2.getw() == 42);
        r2.resetw(r1.getw());
        r1.resetw(); // testing default
        return res && testgetw();
    }
    bool testseth()
    {
        r1.reseth(r2.geth());
        r2.reseth(42);
        bool res=(r2.geth() == 42);
        r2.reseth(r1.geth());
        r1.reseth(); // testing default
        return res && testgeth();
    }

    bool testinf()
    {
        r2.reseth(37);
        r2.resetw(63);
        Rect res = r2.inf(r3);
        return res.getx() == 34 && res.gety() == -4 && res.getw() == 14 && res.geth() == 37;
    }
    bool testsup()
    {

        r2.reseth(37);
        r2.resetw(63);
        Rect res = r2.sup(r3);
        return res.getx() == -15 && res.gety() ==-12 && res.getw() == 105 && res.geth()==87;
    }

    bool testmult()
    {

        r2.reseth(37);
        r2.resetw(63);
        Rect res = r2 * 3;
        return res.getx() == -15 && res.gety() == -4 && res.getw() == 63*3 && res.geth() == 37*3;
    }
    bool testdiv()
    {

        r2.reseth(37);
        r2.resetw(63);
        Rect res = r2 / 3;
        return res.getx() == -15 && res.gety() == -4 && res.getw() == 63/3 && res.geth() == 37/3;
    }
    bool testequal()
    {

        r2.reseth(37);
        r2.resetw(63);
        Rect r2eq = Rect(r2.getx(),r2.gety(),r2.getw(),r2.geth());
        return r2eq == r2;
    }
    bool testdiff()
    {

        r2.reseth(37);
        r2.resetw(63);
        Rect r2d1 = Rect(r2.getx() -1,r2.gety(),r2.getw(),r2.geth() );
        Rect r2d2 = Rect(r2.getx() ,r2.gety() +3,r2.getw(),r2.geth() );
        Rect r2d3 = Rect(r2.getx() ,r2.gety(),r2.getw() -5,r2.geth() );
        Rect r2d4 = Rect(r2.getx(),r2.gety(),r2.getw(),r2.geth() +4 );
        return r2 != r2d1 && r2 != r2d2 && r2 != r2d3 && r2 != r2d4;
    }

    int testall()
    {
        int status = 0;
        if ( ! testgetx() )
        {
            testlog << nl << "testgetx() failed ";
            status = -1;
        }
        if ( ! testgety() )
        {
            testlog << nl << "testgety() failed ";
            status = -2;
        }
        if ( ! testgetw() )
        {
            testlog << nl << "testgetw() failed ";
            status = -3;
        }
        if ( ! testgeth() )
        {
            testlog << nl << "testgeth() failed ";
            status = -4;
        }

        if ( ! testsetx() )
        {
            testlog << nl << "testsetx() failed ";
            status = -5;
        }
        if ( ! testsety() )
        {
            testlog << nl << "testsety() failed ";
            status = -6;
        }
        if ( ! testsetw() )
        {
            testlog << nl << "testsetw() failed ";
            status = -7;
        }
        if ( ! testseth() )
        {
            testlog << nl << "testseth() failed ";
            status = -8;
        }

        if ( ! testsup() )
        {
            testlog << nl << "testsup() failed ";
            status = -9;
        }
        if ( ! testinf() )
        {
            testlog << nl << "testinf() failed ";
            status = -10;
        }
        if ( ! testmult() )
        {
            testlog << nl << "testmult() failed ";
            status = -11;
        }
        if ( ! testdiv() )
        {
            testlog << nl << "testdiv() failed ";
            status = -12;
        }
        if ( ! testequal() )
        {
            testlog << nl << "testequal() failed ";
            status = -13;
        }
        if ( ! testdiff() )
        {
            testlog << nl << "testdiff() failed ";
            status = -14;
        }

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

    return exitstatus;
}


