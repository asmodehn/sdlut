#include "TestCommon.hh"

using namespace SDLut::video;

Logger testlog("TestScreenClipRect");

#define IMG_TEST_SIZE 5

class AssertClip : public AssertEngine
{
protected:
    Rect imgTLPos; //top left image
    Rect imgTRPos; //top right image
    Rect imgBLPos; //bottom left image
    Rect imgBRPos; //bottom right image
    Rect imgCPos; //center image

    std::vector<Rect> pos;
    std::vector<Color> col;

    Color m_bgColor;
    Color m_imgColor;

    Rect clipRect;

public:

    AssertClip(Logger & log, const ArgParser & ap, Rect clippos, Color imgcolor, Color bgc)
            : AssertEngine(log,ap),imgTLPos(),imgTRPos(),imgBLPos(), imgBRPos(),imgCPos(), m_bgColor(bgc), m_imgColor(imgcolor)
    {

        Rect table[5] = {imgTLPos,imgTRPos,imgBLPos,imgBRPos,imgCPos};

        for (int t=0; t< 5; ++t)
        {

            for (int i= table[t].getx(); i < table[t].getx()+table[t].getw(); ++i)
                for (int j= table[t].gety(); j < table[t].gety()+table[t].geth(); ++j)
                {
                    //pos to test
                    Rect asrt_rect = Rect(i,j);
                    pos.push_back(asrt_rect);

                    //intersection with clip rect
                    Rect intersect = asrt_rect.inf(clippos);
                    //if inside clip rect, imgcolor
                    if ( intersect == asrt_rect )
                    {
                        col.push_back(m_imgColor);
                    }
                    else //otherwise background color
                    {
                        col.push_back(m_bgColor);
                    }
                }
        }

    }

    virtual ~AssertClip()
    {}

    virtual bool assertresize(int width, int height)
    {
        //TODO handle resize
        return true;
    }

    bool testClipRect(const Rect & abspos) const
    {
        return (abspos.getx() > clipRect.getx() && abspos.getx() < static_cast<int>(clipRect.getx() + clipRect.getw()) )
               && (abspos.gety() > clipRect.gety() && abspos.gety() < static_cast<int>(clipRect.gety() + clipRect.geth()) );

    }

    virtual bool assertrender(ScreenBuffer& screen)const
    {

        bool res = true;

        for (unsigned int i = 0 ; i < pos.size(); ++i)
        {
            //getting real color on screen
            Color real = screen.getColorAt(pos[i].getx(),pos[i].gety());
            if (! col.at(i).isSimilarTo(real) )
            {
                m_log << nl << "Expected = " << col.at(i);
                m_log << nl << "Pixel at X = " << pos[i].getx() << " Y = " << pos[i].gety() << " : " << nl << real;
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


};



class TestClip : public TestEngine
{

    //position of the surface to test in the screenbuffer
    Rect clipRect;

    Rect imgTLPos;
    Rect imgTRPos;
    Rect imgBRPos;
    Rect imgBLPos;
    Rect imgCPos;

    Color m_bgc;
    Image m_fgimg;

public:

    TestClip(Logger & log, AssertClip & ac, Rect cliprect, Color imgcolor, Color bgcolor)
            : TestEngine(log,ac), clipRect(cliprect), imgTLPos(), imgTRPos(), imgBRPos(), imgBLPos(), m_bgc(bgcolor), m_fgimg(IMG_TEST_SIZE,IMG_TEST_SIZE)
    {
        m_log.enableFileLog("TestScreenClipRect.log");

        //preparing image
        m_fgimg.fill(imgcolor);

        //preparing image test positions
        imgTLPos.resetx(clipRect.getx());
        imgTLPos.resety(clipRect.gety());

        imgTRPos.resetx(clipRect.getx()+clipRect.getw() - IMG_TEST_SIZE /2);
        imgTRPos.resety(clipRect.gety());

        imgBLPos.resetx(clipRect.getx());
        imgBLPos.resety(clipRect.gety()+clipRect.geth() - IMG_TEST_SIZE /2);

        imgBRPos.resetx(clipRect.getx()+clipRect.getw() - IMG_TEST_SIZE /2);
        imgBRPos.resety(clipRect.gety()+clipRect.geth() - IMG_TEST_SIZE /2);

        imgCPos.resetx(clipRect.getx()+clipRect.getw() /2);
        imgCPos.resety(clipRect.gety()+clipRect.geth() /2);


    }

    virtual ~TestClip()
    {}

    virtual bool resize(int width, int height)
    {

        //TODO : handle resize
        return true;
    }

    virtual bool render(ScreenBuffer & screen) const
    {
        screen.setBGColor(m_bgc);

        //copying rect from actual assert engine, to make sure we dont modify it
        Rect tlpos = imgTLPos;
        Rect trpos = imgTRPos;
        Rect brpos = imgBRPos;
        Rect blpos = imgBLPos;
        Rect cpos = imgCPos;


        screen.resetClipRect(clipRect);

        screen.blit(m_fgimg,tlpos);
        screen.blit(m_fgimg,trpos);
        screen.blit(m_fgimg,brpos);
        screen.blit(m_fgimg,blpos);
        screen.blit(m_fgimg,cpos);

        return true;
    }

};

int main(int argc, char** argv)
{
    ArgParser args(argc,argv);

    //Starting with usual SDL window
    App::getInstance().initVideo(false,true,false);
    App::getInstance().setName ("SDLut::video test Screen Clip Rect");

    //Setting Display size and BPP
    App::getInstance().getDisplay().setDisplay(640,480); // using autodetected bpp

    App::getInstance().getDisplay().requestOpenGL(args.isOGL());

    int exitstatus = -1;

    Color fgc(Randomizer<unsigned char>::get(),Randomizer<unsigned char>::get(),Randomizer<unsigned char>::get());
    Color bgc(Randomizer<unsigned char>::get(),Randomizer<unsigned char>::get(),Randomizer<unsigned char>::get());

    Rect clipr( Randomizer<unsigned int>::get(0,640),Randomizer<unsigned int>::get(0,480 - 64));
    clipr.resetw( Randomizer<unsigned int>::get(1,640 - clipr.getx()) );
    clipr.reseth( Randomizer<unsigned int>::get(1,480 - 64 - clipr.gety() ) );

    if ( clipr.getw() < 1 ) clipr.resetw();
    if ( clipr.geth() < 1 ) clipr.reseth();

    AssertClip teng(testlog,args,clipr,fgc,bgc);
    TestClip test(testlog,teng,clipr,fgc,bgc);
    if (App::getInstance().getDisplay().show())
    {
        exitstatus = App::getInstance().getDisplay().mainLoop();
    }

    return exitstatus;
}




