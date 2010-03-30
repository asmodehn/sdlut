#include "TestCommon.hh"

using namespace SDLut::video;

Logger testlog("TestScreenBuffer");

class Test : public AssertEngine
{
protected:
    Rect imgTLPos; //top left image
    Rect imgTRPos; //top right image
    Rect imgBLPos; //bottom left image
    Rect imgBRPos; //bottom right image
    Rect imgCPos; //center image

    //this Assert Engine check that loaded image is a proper smiley.bmp image
    std::vector<Rect> pos;
    std::vector<Color> color;

    Color m_bgColor;
    const Image * m_fgimg;

    Rect clipRect;

public:

    Test(const Image & fgimage, Color bgc, Logger & log, const ArgParser & ap)
            : AssertEngine(log,ap),imgTLPos(),imgTRPos(),imgBLPos(), imgBRPos(),imgCPos(), m_bgColor(bgc), m_fgimg(&fgimage)
    {
        //For rendering tests : pos and color needs to be filled in the constructor

        //expecting data/test/smiley.bmp

        //white corner
        pos.push_back(Rect(0,0,1,1));
        color.push_back(Color(0xff,0xff,0xff));
        pos.push_back(Rect(31,0,1,1));
        color.push_back(Color(0xff,0xff,0xff));
        pos.push_back(Rect(31,31,1,1));
        color.push_back(Color(0xff,0xff,0xff));
        pos.push_back(Rect(0,31,1,1));
        color.push_back(Color(0xff,0xff,0xff));

        //yellowhead
        pos.push_back(Rect(10,9,1,1));
        color.push_back(Color(0xff,0xff,0x00));
        pos.push_back(Rect(21,9,1,1));
        color.push_back(Color(0xff,0xff,0x00));
        pos.push_back(Rect(10,25,1,1));
        color.push_back(Color(0xff,0xff,0x00));
        pos.push_back(Rect(21,25,1,1));
        color.push_back(Color(0xff,0xff,0x00));

        //mouth
        pos.push_back(Rect(11,23,1,1));
        color.push_back(Color(0x00,0x00,0x00));
        pos.push_back(Rect(20,23,1,1));
        color.push_back(Color(0x00,0x00,0x00));

        //nose
        pos.push_back(Rect(15,18,1,1));
        color.push_back(Color(0x00,0x00,0x00));
        pos.push_back(Rect(16,19,1,1));
        color.push_back(Color(0x00,0x00,0x00));

        //eyes
        pos.push_back(Rect(11,14,1,1));
        color.push_back(Color(0x00,0x00,0x00));
        pos.push_back(Rect(12,14,1,1));
        color.push_back(Color(0xff,0xff,0xff));
        pos.push_back(Rect(19,14,1,1));
        color.push_back(Color(0x00,0x00,0x00));
        pos.push_back(Rect(20,14,1,1));
        color.push_back(Color(0xff,0xff,0xff));

    }

    virtual ~Test()
    {}

    virtual bool assertresize(int width, int height)
    {

        //setting clip rect
        clipRect.resetx(width/10);
        clipRect.resety(height/10);
        clipRect.resetw(width/2);
        clipRect.reseth(height/2);

        //setting expected positions of images
        imgTLPos.resetx(clipRect.getx() - 16);
        imgTLPos.resety(clipRect.gety() - 16);
        imgTLPos.resetw(32);
        imgTLPos.reseth(32);

        //setting expected positions of images
        imgTRPos.resetx(clipRect.getw() - 16);
        imgTRPos.resety(clipRect.gety() - 16);
        imgTRPos.resetw(32);
        imgTRPos.reseth(32);

        //setting expected positions of images
        imgBLPos.resetx(clipRect.getx() - 16);
        imgBLPos.resety(clipRect.geth() - 16);
        imgBLPos.resetw(32);
        imgBLPos.reseth(32);

        //setting expected positions of images
        imgBRPos.resetx(clipRect.getw() - 16);
        imgBRPos.resety(clipRect.geth() - 16);
        imgBRPos.resetw(32);
        imgBRPos.reseth(32);

        //center position for center display
        imgCPos.resetx( (clipRect.getw() - 32) / 2  );
        imgCPos.resety ( (clipRect.geth() - 32) /2);
        imgCPos.resetw(32);
        imgCPos.reseth(32);


        return true;
    }

    bool testClipRect(const Rect & abspos) const
    {
        return (abspos.getx() > clipRect.getx() && abspos.getx() < static_cast<int>(clipRect.getx() + clipRect.getw()) )
            && (abspos.gety() > clipRect.gety() && abspos.gety() < static_cast<int>(clipRect.gety() + clipRect.geth()) );

    }

    virtual bool assertSmiley(ScreenBuffer & screen, Rect imgpos) const
    {
        bool res = true;
        for (unsigned int i= 0; i<pos.size() ; i++)
        {
            Color expctd;
            if ( m_fgimg )
            {
                //we expect image color if inside clip rect. otherwise it will be backgraound color
                expctd = testClipRect(pos[i]) ? color[i] : m_bgColor;

            }
            //getting real color on screen
            Color real = screen.getpixel(imgpos.getx() + pos[i].getx(), imgpos.gety() + pos[i].gety());
            if (!expctd.isSimilarTo(real))
            {
                m_log << nl << "Expected = " << expctd;
                m_log << nl << "Pixel at X = " << imgpos.getx() + pos[i].getx() << " Y = " << imgpos.gety() + pos[i].gety() << " : " << nl << real;
                std::string scsht("Screenshot_Rendering_Test_Error.bmp");
                if (screen.captureBMP(scsht))
                {
                    m_log << nl << "Screenshot saved at " << scsht;
                }
                setError(-1,"Wrong color detected.");
                res = false;
            }

        }
        return res;
    }

    virtual bool assertrender(ScreenBuffer& screen)const
    {
        bool res = assertSmiley(screen,imgCPos);
        res = res && assertSmiley(screen,imgTLPos);
        res = res && assertSmiley(screen,imgTRPos);
        res = res && assertSmiley(screen,imgBLPos);
        res = res && assertSmiley(screen,imgBRPos);
        return res;
    }



    const Image * getFGImage() const
    {
        return m_fgimg;
    }
    const Color * getBGColor() const
    {
        return &m_bgColor;
    }
    const Rect * getClipRect() const
    {
        return &clipRect;
    }
    const Rect * getTLPos() const { return &imgTLPos; }
    const Rect * getTRPos() const { return &imgTRPos; }
    const Rect * getBRPos() const { return &imgBRPos; }
    const Rect * getBLPos() const { return &imgBLPos; }
    const Rect * getCPos() const { return &imgCPos; }


};



class RenderingTestEngine : public TestEngine
{

    //position of the surface to test in the screenbuffer
    const Rect * clipRect;

    const Rect * imgTLPos;
    const Rect * imgTRPos;
    const Rect * imgBRPos;
    const Rect * imgBLPos;
    const Rect * imgCPos;

    const Color * m_bgc;
    const Image * m_fgimg;

public:

    RenderingTestEngine(Logger & log, Test & ae)
            : TestEngine(log,ae), clipRect(ae.getClipRect()), imgTLPos(ae.getTLPos()), imgTRPos(ae.getTRPos()),
              imgBRPos(ae.getBRPos()), imgBLPos(ae.getBLPos()), m_bgc(ae.getBGColor()), m_fgimg(ae.getFGImage())
    {
     m_log.enableFileLog("TestScreenBuffer.log");
    }

    virtual ~RenderingTestEngine()
    {}

    virtual bool resize(int width, int height)
    {
        //putting image in screen center
        //taking care of resize for imgRPos should have been done already by AssertEngine
        Test & mytest = dynamic_cast<Test&>(m_assertengine);

        //WHY is that needed here ???
        imgTLPos = mytest.getTLPos();
        imgTRPos = mytest.getTRPos();
        imgBRPos = mytest.getBRPos();
        imgBLPos = mytest.getBLPos();
        imgCPos = mytest.getCPos();



        return true;
    }

    virtual bool render(ScreenBuffer & screen) const
    {
        screen.setBGColor(*m_bgc);

        //copying rect from actual assert engine, to make sure we dont modify it
        Rect tlpos = *imgTLPos;
        Rect trpos = *imgTRPos;
        Rect brpos = *imgBRPos;
        Rect blpos = *imgBLPos;
        Rect cpos = *imgCPos;


        //careful not to draw image not existing
        if ( m_fgimg)
        {
            screen.resetClipRect(*clipRect);
            screen.blit(*m_fgimg,tlpos);
            screen.blit(*m_fgimg,trpos);
            screen.blit(*m_fgimg,brpos);
            screen.blit(*m_fgimg,blpos);
            screen.blit(*m_fgimg,cpos);
        }
        return true;
    }

};

int main(int argc, char** argv)
{
    ArgParser args(argc,argv);

    //Starting with usual SDL window
    App::getInstance().initVideo(false,true,false);
    App::getInstance().setName ("SDLut::video test Image");

    //Setting Display size and BPP
    App::getInstance().getDisplay().setDisplay(640,480); // using autodetected bpp

    App::getInstance().getDisplay().getScreenBuffer().setOpenGL(args.isOGL());

    int exitstatus = -1;

    ImageLoader loader;
    std::string imgfile = args.get(1);
    if (imgfile != "" )
    {
        std::auto_ptr<Image> testImg = loader.load(imgfile);
        Test teng(*testImg,Color(0,0,0),testlog,args);
        RenderingTestEngine engine(testlog,teng);
        if (App::getInstance().getDisplay().show())
        {
            exitstatus = App::getInstance().getDisplay().mainLoop();
        }
    }
    else
    {
        testlog << nl << " File : " << imgfile << "not found. Exiting.";
    }
    return exitstatus;
}




