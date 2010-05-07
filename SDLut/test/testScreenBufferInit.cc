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
    bool testit(unsigned int width, unsigned int height, unsigned short bpp, bool resizable = false,  bool fullscreen = false, bool noframe = false)
    {
		m_disp.requestOpenGL(m_ap.isOGL());
        m_disp.requestNoFrame(noframe);
        m_disp.requestFullscreen(fullscreen);
        m_disp.requestResizable(resizable);

		m_disp.requestSize(width, height);
        bool request = ( m_disp.requestBPP(bpp) != 0 );

        const ScreenInfo * gotVI;
        bool res = false;

        if (App::getInstance().getDisplay().show())
        {
            gotVI = &m_disp.getScreenBuffer().getScreenInfo();
            //testlog << nl << *gotVI;
            res = true;
        }

    	bool gotres = res;
        //if size we got is different, it should have been signaled before with a false return
        //otherwise both should be true
        res = res && (request == ( m_disp.getScreenBuffer().getWidth() == width ) );
        res = res && (request ==  ( m_disp.getScreenBuffer().getHeight() == height ) ) ;
        //if bpp we got is different, it should have been signaled before with a false return.
        //otherwise both should be true
        res = res && (request == ( m_disp.getScreenBuffer().getBPP() == bpp ) );

		if ( ! res )
		{	
			
			if ( gotres )// we had error here :
			{
				testlog << nl << " ERROR ! ";
				testlog << nl << " Screen requested : " << m_disp.getRequestedWidth() << " x " << m_disp.getRequestedHeight() << " @ " << m_disp.getRequestedBPP() ;
				testlog << nl << " Screem obtained : " << m_disp.getScreenBuffer().getWidth() << " x " << m_disp.getScreenBuffer().getHeight() << " @ " <<m_disp.getScreenBuffer().getBPP();
			}
			else //screen creation failed
			{
				testlog << nl << " ERROR ! ";
				testlog << nl << " Screen Creation failed at : " << m_disp.getRequestedWidth() << " x " << m_disp.getRequestedHeight() << " @ " << m_disp.getRequestedBPP();
			}

			testlog << nl << " Requested OpenGL " << std::boolalpha << m_ap.isOGL() << " and got => " << gotVI->isOpenGL();
			testlog << nl << " Requested Resizable " << std::boolalpha << resizable << " and got => " << gotVI->isResizable();
			testlog << nl << " Requested Fullscreen " << std::boolalpha << fullscreen << " and got => " << gotVI->isFullscreen();
			testlog << nl << " Requested NoFrame " << std::boolalpha << noframe << " and got => " << gotVI->isNoFrame();
		}
        App::getInstance().getDisplay().hide();

        return res;
    }
	bool testit( bool resizable = false,  bool fullscreen = false, bool noframe = false)
	{
		m_disp.requestOpenGL(m_ap.isOGL());
        m_disp.requestNoFrame(noframe);
        m_disp.requestFullscreen(fullscreen);
        bool request = m_disp.requestResizable(resizable);

		const ScreenInfo * gotVI;
        bool res = false;

        if (App::getInstance().getDisplay().show())
        {
            gotVI = &m_disp.getScreenBuffer().getScreenInfo();
            //testlog << nl << *gotVI;
            res = true;
        }

		if ( ! res )
		{	
				testlog << nl << " ERROR ! ";
				testlog << nl << " Screen Creation failed at : " << m_disp.getRequestedWidth() << " x " << m_disp.getRequestedHeight() << " @ " << m_disp.getRequestedBPP();

			testlog << nl << " Requested OpenGL " << std::boolalpha << m_ap.isOGL() << " and got => " << gotVI->isOpenGL();
			testlog << nl << " Requested Resizable " << std::boolalpha << resizable << " and got => " << gotVI->isResizable();
			testlog << nl << " Requested Fullscreen " << std::boolalpha << fullscreen << " and got => " << gotVI->isFullscreen();
			testlog << nl << " Requested NoFrame " << std::boolalpha << noframe << " and got => " << gotVI->isNoFrame();
		}
        App::getInstance().getDisplay().hide();

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

            if ( !  testit(width, height, bpp)) 
            {
                testlog << nl << "test Default failed";
                status |= 0x01;
            }
            if ( ! testit(width,height,bpp,true, false, false)) 
            {
                testlog << nl << "test Resizable failed";
                status |= 0x02;
            }
            if ( ! testit(width,height,bpp, false, true, false))
            {
                testlog << nl << " test Fullscreen failed";
                status |= 0x04;
            }
            if ( ! testit(width,height,bpp, false, false, true))
            {
                testlog << nl << " test NoFrame failed";
                status |= 0x08;
            }

            ///Warning : some of these requested mode might not be possible.
            ///However setting both should have been prevented by SDLut, and the test should therefore succeed.
            if ( ! testit(width,height,bpp, true, false, true))
            {
                testlog << nl << " test Resizable + NoFrame failed";
                status |= 0x10;
            }

            if ( ! testit(width,height,bpp, false, true, true))
            {
                testlog << nl << " test Fullscreen + NoFrame failed";
                status |= 0x20;
            }

            if ( ! testit(width,height,bpp, true, true, false))
            {
                testlog << nl << " test Resizable + Fullscreen failed";
                status |= 0x40;
            }

            if ( ! testit(width,height,bpp, true, true, true))
            {
                testlog << nl << " test Resizable + Fullscreen + NoFrame failed";
                status |= 0x80;
            }
        }
        else
        {
            testlog << nl << "Testing Default Desktop format.";

            if ( ! testit() )
            {
                testlog << nl << "test Default failed";
                status |= 0x01;
            }
            if ( ! testit(true, false, false))
            {
                testlog << nl << "test Resizable failed";
                status |= 0x02;
            }
            if ( ! testit( false, true, false))
            {
                testlog << nl << " test Fullscreen failed";
                status |= 0x04;
            }
            if ( ! testit( false, false, true))
            {
                testlog << nl << " test NoFrame failed";
                status |= 0x08;
            }

            ///Warning : some of these requested mode might not be possible.
            ///However setting both should have been prevented by SDLut, and the test should therefore succeed.
            if ( ! testit( true, false, true))
            {
                testlog << nl << " test Resizable + NoFrame failed";
                status |= 0x10;
            }

            if ( ! testit( false, true, true))
            {
                testlog << nl << " test Fullscreen + NoFrame failed";
                status |= 0x20;
            }

            if ( ! testit( true, true, false))
            {
                testlog << nl << " test Resizable + Fullscreen failed";
                status |= 0x40;
            }

            if ( ! testit( true, true, true))
            {
                testlog << nl << " test Resizable + Fullscreen + NoFrame failed";
                status |= 0x80;
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


