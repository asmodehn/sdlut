#include "TestCommon.hh" // for argParser only

#include <sstream>

Logger testlog("testScreenBufferInit");

using namespace SDLut::video;

///should be constructed only after call to initVideo
class SBTester
{
    Display & m_disp;
    ///we are using ArgParser here
    /// Except "auto" or "nogl",
    /// Arg1 is the requested width
    /// Arg2 is the requested height
    /// Arg3 is the requested bpp
    const ArgParser & m_ap;

public:
    SBTester( Display & disp, const ArgParser & ap ) : m_disp(disp), m_ap(ap)
    {
        testlog.enableFileLog("TestScreenBufferInit.log");
    }

    ~SBTester()
    {
    }

    ///For each test
    /// 1- Try to setup as required by parameters
    /// 2- Assess if supported of not.
    /// 3- Compare requested configuration with obtained configuration
    /// Test succeed if requested configuration ( obtained after parameters setup ) is the same as obtained configuration
    /// which means this test cannot be used to automatically detect if a configuration si supported.
    /// this must be done in manual.
    int testit(unsigned int width, unsigned int height, unsigned short bpp)
    {
        m_disp.getScreenRequest().requestSize(width, height);
        m_disp.getScreenRequest().requestBPP(bpp);
        return testit();
    }
    int testit()
    {
        m_disp.getScreenRequest().requestOpenGL(m_ap.isOGL());

        ScreenInfo * reqVI = &m_disp.getScreenRequest();
        testlog << nl << *reqVI;
        const ScreenInfo * gotVI;

        bool res = false;

        if (App::getInstance().getDisplay().show())
        {
            gotVI = &m_disp.getScreenBuffer().getScreenInfo();
            testlog << nl << *gotVI;
            res = true;
        }

        res = res && reqVI->getRequestedWidth() == m_disp.getScreenBuffer().getWidth();
        res = res && reqVI->getRequestedHeight() == m_disp.getScreenBuffer().getHeight();
        res = res && reqVI->getRequestedBPP() == m_disp.getScreenBuffer().getBPP();

        res = res && reqVI->isOpenGL() == gotVI->isOpenGL();
        res = res && reqVI->isResizable() == gotVI->isResizable();
        res = res && reqVI->isNoFrame() == gotVI->isNoFrame();
        res = res && reqVI->isFullscreen() == gotVI->isFullscreen();


        return res;
    }

    int testNoFrame(unsigned int width, unsigned int height, unsigned short bpp )
    {
        testNoFrame(false);
        return testit(width, height, bpp);
    }
    int testNoFrame(bool runtest = true)
    {
        int res = 0;
        //No Frame => Not Resizable
        testlog << nl << "NoFrame config : ";
        m_disp.getScreenRequest().requestNoFrame(true);
        if (runtest) res = testit();
        return res;
    }

    int testFullscreen(unsigned int width, unsigned int height, unsigned short bpp )
    {
        testFullscreen(false);
        return testit(width, height, bpp);
    }
    int testFullscreen(bool runtest = true)
    {
        int res = 0;
        //Fullscreen => noframe + Not Resizable
        testlog << nl << "Fullscreen config : ";
        m_disp.getScreenRequest().requestFullscreen(true);
        if (runtest) res = testit();
        return res;
    }

    int testResizable(unsigned int width, unsigned int height, unsigned short bpp )
    {
        testResizable(false);
        return testit(width, height, bpp);
    }
    int testResizable(bool runtest = true)
    {
        int res = 0;
        //Resizable => Frame + No Fullscreen
        testlog << nl << "Resizable config : ";
        m_disp.getScreenRequest().requestResizable(true);
        if (runtest) res = testit();
        return res;
    }

    int testDefault(unsigned int width, unsigned int height, unsigned short bpp)
    {
        testDefault(false);
        return testit(width,height,bpp);
    }
    int testDefault(bool runtest = true)
    {
        int res = 0;
        testlog << nl << "Default config : Window, Frame, Not Resizable, ";
        if (runtest) res = testit();
        return res;
    }


    int testall()
    {
        int status = 0;
        bool parameters = false;

        unsigned int width = 0;
        std::istringstream strwidth;
        strwidth.str(m_ap.get(1));
        if ( strwidth.str() != "" )
        {
            strwidth >> width;
        }

        unsigned int height = 0;
        std::istringstream strheight;
        strheight.str(m_ap.get(2));
        if ( strheight.str() != "" )
        {
            strheight >> height;
        }

        unsigned short bpp = 0;
        std::istringstream strbpp;
        strbpp.str(m_ap.get(3));
        if ( strbpp.str() != "" )
        {
            strbpp >> bpp;
            parameters  = true; // we have proper 3 parameters
        }

        if ( parameters )
        {
        testlog << nl << "Testing " << width << " x "  << height << " @ " << bpp;

        if ( ! testDefault(width, height, bpp) )
        {
            testlog << nl << "test Default failed";
            status |= 0x1;
        }
        if ( ! testResizable(width,height,bpp))
        {
            testlog << nl << "test Resizable failed";
            status |= 0x2;
        }
        if ( ! testFullscreen(width,height,bpp))
        {
            testlog << nl << " test Fullscreen failed";
            status |= 0x4;
        }
        if ( ! testNoFrame(width,height,bpp))
        {
            testlog << nl << " test NoFrame failed";
            status |= 0x8;
        }
        }
        else
        {
            testlog << nl << "Testing Default Desktop format.";

        if ( ! testDefault() )
        {
            testlog << nl << "test Default failed";
            status |= 0x1;
        }
        if ( ! testResizable())
        {
            testlog << nl << "test Resizable failed";
            status |= 0x2;
        }
        if ( ! testFullscreen())
        {
            testlog << nl << " test Fullscreen failed";
            status |= 0x4;
        }
        if ( ! testNoFrame())
        {
            testlog << nl << " test NoFrame failed";
            status |= 0x8;
        }
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

    //Setting Display size and BPP
    SBTester tester(App::getInstance().getDisplay(),args);

    return tester.testall();


}


