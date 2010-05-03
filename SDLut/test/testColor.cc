#include "TestCommon.hh"

Logger testlog("testColor");

using namespace SDLut::video;

class ColorTester
{
    Color c1,c2,c3;

public:
    ColorTester()
            : c1(), //testing default Color
            c2(56,23,45), // default alpha
            c3(123,36,154,57)
    {
        testlog.enableFileLog("testColor.log");
    }

    ~ColorTester()
    {
    }

    //first tests to run, they will be used later
    bool testgetR()
    {
        return c1.getR() == 0 && c2.getR() == 56 && c3.getR() == 123;
    }
    bool testgetG()
    {
        return c1.getG() == 0 && c2.getG()== 23 && c3.getG() == 36;
    }
    bool testgetB()
    {
        return c1.getB() == 0 && c2.getB() == 45 && c3.getB() == 154;
    }
    bool testgetA()
    {
        return c1.getA() == 255 && c2.getA() == 255 && c3.getA() == 57;
    }

    //we use testget* to make sure the color are returned to ther initial values
    bool testsetR()
    {
        c1.resetR(c2.getR());
        c2.resetR(42);
        bool res=(c2.getR() == 42);
        c2.resetR(c1.getR());
        c1.resetR(); //testing default
        return res && testgetR();
    }
    bool testsetG()
    {
        c1.resetG(c2.getG());
        c2.resetG(42);
        bool res=(c2.getG() == 42);
        c2.resetG(c1.getG());
        c1.resetG(); //testing default
        return res && testgetG();
    }
    bool testsetB()
    {
        c1.resetB(c2.getB());
        c2.resetB(42);
        bool res=(c2.getB() == 42);
        c2.resetB(c1.getB());
        c1.resetB(); //testing default
        return res && testgetB();
    }
    bool testsetA()
    {
        c1.resetA(c2.getA());
        c2.resetA(42);
        bool res=(c2.getA() == 42);
        c2.resetA(c1.getA());
        c1.resetA(); // testing default
        return res && testgetA();
    }

//TODO
    /*
        bool testblend()
        {

        }
        bool testequal()
        {
            Rect r1eq = Rect(r1.getx(),r1.gety(),r1.getw(),r1.geth());
            return r1eq == r1;
        }
        bool testdiff()
        {

            r1.reseth(37);
            r1.resetw(63);
            Rect r1d1 = Rect(r1.getx() -1,r1.gety(),r1.getw(),r1.geth() );
            Rect r1d2 = Rect(r1.getx() ,r1.gety() +3,r1.getw(),r1.geth() );
            Rect r1d3 = Rect(r1.getx() ,r1.gety(),r1.getw() -5,r1.geth() );
            Rect r1d4 = Rect(r1.getx(),r1.gety(),r1.getw(),r1.geth() +4 );
            return r1 != r1d1 && r1 != r1d2 && r1 != r1d3 && r1 != r1d4;
        }
    */
    int testall()
    {
        int status = 0;
        if ( ! testgetR() )
        {
            testlog << nl << "testgetR() failed ";
            status = -1;
        }
        if ( ! testgetG() )
        {
            testlog << nl << "testgetG() failed ";
            status = -2;
        }
        if ( ! testgetB() )
        {
            testlog << nl << "testgetB() failed ";
            status = -3;
        }
        if ( ! testgetA() )
        {
            testlog << nl << "testgetA() failed ";
            status = -4;
        }

        if ( ! testsetR() )
        {
            testlog << nl << "testsetR() failed ";
            status = -5;
        }
        if ( ! testsetG() )
        {
            testlog << nl << "testsetG() failed ";
            status = -6;
        }
        if ( ! testsetB() )
        {
            testlog << nl << "testsetB() failed ";
            status = -7;
        }
        if ( ! testsetA() )
        {
            testlog << nl << "testsetA() failed ";
            status = -8;
        }

//TODO
        /*
                if ( ! testblend() )
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
        */
        return status;
    }

};


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
    ArgParser args(argc,argv);

    //Starting with usual SDL window
    App::getInstance().initVideo(false,true,false);
    App::getInstance().setName ("SDLut::video test Rect");


    ColorTester ct;

    int exitstatus = ct.testall();

    return exitstatus;

}


