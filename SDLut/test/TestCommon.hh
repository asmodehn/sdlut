#ifndef SDLUT_TEST_COMMON
#define SDLUT_TEST_COMMON


//This header is the common structure to all tests.
// A test coder can extend these classes to implement easy checks
#include "SDL.hh"

#include "Logger.hh"
using namespace Core;

using namespace SDLut;

#include <string>

class ArgParser
{
    std::vector<std::string> args;
    bool m_nogl;
    bool m_auto;

public:
    ArgParser(int argc, char* argv[]) : m_nogl(false), m_auto(false)
    {
        for (int i = 0; i < argc; ++i )
        {
            std::string argstr(argv[i]);
            if (argstr == "nogl" )
            {
                m_nogl = true;
                continue;
            }
            if (argstr == "auto" )
            {
                m_auto = true;
                continue;
            }
            //we dont store nogl and auto arguments in the vector
            args.push_back(argstr);
        }

        std::cout << " Arguments parsing : " << std::endl;
        std::cout << " OpenGL : " << m_nogl << std::endl;
        std::cout << " Auto : " << m_auto << std::endl;
        for ( unsigned int j =0 ; j < args.size(); ++j) std::cout << "args.get(" << j << ") = " << args.at(j) << std::endl;
        std::cout << std::endl;
    }

    ~ArgParser() {}

    std::string get(unsigned int index) const
    {
        std::string result("");

        if ( args.size()>index)
        {
            result = args.at(index);
        }

        return result;
    }



    bool isSDL() const
    {
        return m_nogl;
    }

    bool isOGL() const
    {
        return !m_nogl;
    }

    bool isAuto() const
    {
        return m_auto;
    }

    std::string getcmd()
    {
        return args[0];
    }

};






//engine holding the test code to be run
//TODO : Maybe we can simplify with only one engine, to assert render only ???
class AssertEngine
{

    unsigned int m_numrender;
    unsigned int m_maxrender;

protected :

    //to be able to write in log, even while rendering
    mutable    Logger & m_log;

public :
    ///max_render = 0 means it will run forever
    AssertEngine( Logger & log, const ArgParser & ap ) : m_numrender(0), m_maxrender(0),m_log(log)
    {
        if ( ap.isAuto() ) m_maxrender = 1;
    }

    ~AssertEngine() {}

    //Will log an Error string and exit
    void logError(std::string err) const
    {
        m_log << nl<< "ERROR : " << err << nl ;
    }

    //init and resize code is often the same ( but not always )
    virtual bool assertinit(int width, int height)
    {
        return assertresize(width,height);
    }

    virtual bool assertresize(int width, int height) = 0;

    bool testquit_assertnewframe(unsigned long framerate, unsigned long deltaticks)
    {
        if (m_maxrender > 0 && m_numrender < m_maxrender )
        {
            //stop it !
            App::getInstance().requestTermination();
        }
        m_numrender++;
        return assertnewframe(framerate,deltaticks);
    }

    virtual bool assertnewframe(unsigned long framerate, unsigned long deltaticks)
    {
        return true;
    }

    virtual bool assertrender(video::ScreenBuffer & screen) const = 0;

};




//Engine Holding what you want to test

class TestEngine
{

protected:

    AssertEngine & m_assertengine;

    //to be able to write in log, even while rendering
    mutable Logger & m_log;

public:

    TestEngine(Logger & log, AssertEngine & ae ) : m_assertengine(ae),m_log(log)
    {

        App::getInstance().getDisplay().resetInitCallback(*this,&TestEngine::testinit);
        App::getInstance().getDisplay().resetResizeCallback(*this,&TestEngine::testresize);
        App::getInstance().getDisplay().resetNewFrameCallback(*this,&TestEngine::testnewframe);
        App::getInstance().getDisplay().resetRenderCallback(*this,&TestEngine::testrender);

    }

    virtual ~TestEngine()
    {

        App::getInstance().getDisplay().resetInitCallback();
        App::getInstance().getDisplay().resetResizeCallback();
        App::getInstance().getDisplay().resetNewFrameCallback();
        App::getInstance().getDisplay().resetRenderCallback();


    }


    bool testinit(int width, int height)
    {
        bool res = init(width, height);
        return res && m_assertengine.assertinit(width,height);
    }
    virtual bool init(int width, int height)
    {//init and resize code is often the same ( but not always )
        return resize(width,height);
    }

    bool testresize(int width, int height)
    {
        bool res = resize(width,height);
        return res && m_assertengine.assertresize(width,height);
    }
    virtual bool resize(int width, int height) = 0;

    bool testnewframe(unsigned long framerate, unsigned long deltaticks)
    {
        bool res = newframe();
        return res && m_assertengine.testquit_assertnewframe(framerate,deltaticks);
    }
    virtual bool newframe() // not mandatory
    {
        return true;
    }

    bool testrender(video::ScreenBuffer & screen) const
    {
        bool res = render(screen);
        return res && m_assertengine.assertrender(screen);
    }
    virtual bool render(video::ScreenBuffer & screen) const = 0;

};


/* EXAMPLE : Dumb sample test

#include "TestCommon.hh" //to get argparser

using namespace SDLut;

Logger testlog("MyTestName");

class Assert : public AssertEngine
    {
        public:
        Assert(Logger& l, ArgParser& ap) : AssertEngine(l,ap) {}
        bool assertresize(int, int) { return true;}
        bool assertrender(video::ScreenBuffer&) const { return true;}
        };

class Test : public TestEngine
    {
        public:
        Test(Logger& l, Assert & a) : TestEngine(l,a) {}
        bool resize(int, int) { return true; }
        bool render(video::ScreenBuffer&) const { return true;}
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

    Assert asrt(testlog,args);
    Test engine(testlog,asrt);

    if (App::getInstance().getDisplay().show())
    {
        exitstatus = App::getInstance().getDisplay().mainLoop();
    }

    return exitstatus;
}




*/


#endif
