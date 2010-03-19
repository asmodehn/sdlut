#ifndef SDLUT_TEST_COMMON
#define SDLUT_TEST_COMMON


//This header is the common structure to all tests.
// A test coder can extend these classes to implement easy checks
#include "SDL.hh"

#include "Logger.hh"
using namespace RAGE;

using namespace SDLut;



//engine holding the test code to be run
class AssertEngine
{
    unsigned int m_numrender;
    unsigned int m_maxrender;

    public :
    ///max_render = 0 means it will run forever
    AssertEngine(int max_render = 0) : m_numrender(0), m_maxrender(max_render)
    {
    }

    ~AssertEngine() {}


    //init and resize code is often the same ( but not always )
	virtual bool assertinit(int width, int height)
	{
	    return assertresize(width,height);
	}

	virtual bool assertresize(int width, int height)
	{
	    return true;
	}

	bool testquit_assertnewframe(unsigned long framerate, unsigned long deltaticks)
	{
	    if (m_maxrender > 0 && m_numrender < m_maxrender )
	    {
	        //stop it !
            App::getInstance().requestTermination(false);
	    }
	    m_numrender++;
		return assertnewframe(framerate,deltaticks);
	}

	virtual bool assertnewframe(unsigned long framerate, unsigned long deltaticks)
	{
	    return true;
	}

	virtual bool assertrender(video::ScreenBuffer & screen) const
	{
	    return true;
	}

};




//Engine Holding what you want to test

class TestEngine
{

AssertEngine m_assertengine;

protected:

Logger log;

public:


	TestEngine(std::string testname  = "Test_Log", const AssertEngine & ae = AssertEngine() ) : m_assertengine(ae), log(testname)
	{

        log.enableFileLog(testname + ".log");

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






class ArgParser
{
  std::vector<std::string> args;

public:
  ArgParser(int argc, char* argv[])
  {
      for (int i = 0; i < argc; ++i )
      {
        args.push_back(std::string(argv[i]));
      }
  }

  ~ArgParser() {}

  std::string get(int index)
  {
      return args.at(index);
  }

  bool isSDL()
  {
      #ifdef WK_OPENGL_FOUND
      return args[0] == "nogl";
      #else
      return true;
      #endif
  }

  bool isOGL()
  {
      #ifdef WK_OPENGL_FOUND
      return args[0] != "nogl";
      #else
      return false;
      #endif
  }

};


#endif
