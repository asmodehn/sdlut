#include "TestCommon.hh"

using namespace SDLut::video;

Logger testlog("TestScreenClipRect");

#define RECT_TEST_SIZE 2

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

    //Rect clipRect;

public:

    AssertClip(Logger & log, const ArgParser & ap, Rect clippos, Color imgcolor, Color bgc)
            : AssertEngine(log,ap),imgTLPos(),imgTRPos(),imgBLPos(), imgBRPos(),imgCPos(), m_bgColor(bgc), m_imgColor(imgcolor)
    {

        //preparing image test positions
        imgTLPos.resetx(clippos.getx() -1);
        imgTLPos.resety(clippos.gety() -1);
        imgTLPos.resetw(RECT_TEST_SIZE);
        imgTLPos.reseth(RECT_TEST_SIZE);

        imgTRPos.resetx(clippos.getx()+clippos.getw() - RECT_TEST_SIZE /2);
        imgTRPos.resety(clippos.gety() -1 );
        imgTRPos.resetw(RECT_TEST_SIZE);
        imgTRPos.reseth(RECT_TEST_SIZE);

        imgBLPos.resetx(clippos.getx() -1 );
        imgBLPos.resety(clippos.gety()+clippos.geth() - RECT_TEST_SIZE /2);
        imgBLPos.resetw(RECT_TEST_SIZE);
        imgBLPos.reseth(RECT_TEST_SIZE);

        imgBRPos.resetx(clippos.getx()+clippos.getw() - RECT_TEST_SIZE /2);
        imgBRPos.resety(clippos.gety()+clippos.geth() - RECT_TEST_SIZE /2);
        imgBRPos.resetw(RECT_TEST_SIZE);
        imgBRPos.reseth(RECT_TEST_SIZE);

        imgCPos.resetx(clippos.getx()+clippos.getw() /2);
        imgCPos.resety(clippos.gety()+clippos.geth() /2);
        imgCPos.resetw(RECT_TEST_SIZE);
        imgCPos.reseth(RECT_TEST_SIZE);


        Rect table[5] = {imgTLPos,imgTRPos,imgBLPos,imgBRPos,imgCPos};

        for (int t=0; t< 5; ++t)
        {

            for (int i= table[t].getx(); i < table[t].getx()+(int)table[t].getw(); ++i)
                for (int j= table[t].gety(); j < table[t].gety()+(int)table[t].geth(); ++j)
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
                    else //otherwise black color
                        //TODO change later to background color if needed
                        //TO THINK ABOUT how to manage background color + clip rect
                    {
                        col.push_back(Color());
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
                logError("Wrong color detected.");
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
    Color m_fgc;

public:

    TestClip(Logger & log, AssertClip & ac, Rect cliprect, Color fgcolor, Color bgcolor)
            : TestEngine(log,ac), clipRect(cliprect), imgTLPos(), imgTRPos(), imgBRPos(), imgBLPos(), m_bgc(bgcolor), m_fgc(fgcolor)
    {
        m_log.enableFileLog("TestScreenClipRect.log");

        //preparing image test positions
        imgTLPos.resetx(clipRect.getx() -1);
        imgTLPos.resety(clipRect.gety() -1);
        imgTLPos.resetw(RECT_TEST_SIZE);
        imgTLPos.reseth(RECT_TEST_SIZE);


        imgTRPos.resetx(clipRect.getx()+clipRect.getw() - RECT_TEST_SIZE /2);
        imgTRPos.resety(clipRect.gety() -1);
        imgTRPos.resetw(RECT_TEST_SIZE);
        imgTRPos.reseth(RECT_TEST_SIZE);

        imgBLPos.resetx(clipRect.getx() -1);
        imgBLPos.resety(clipRect.gety()+clipRect.geth() - RECT_TEST_SIZE /2);
        imgBLPos.resetw(RECT_TEST_SIZE);
        imgBLPos.reseth(RECT_TEST_SIZE);

        imgBRPos.resetx(clipRect.getx()+clipRect.getw() - RECT_TEST_SIZE /2);
        imgBRPos.resety(clipRect.gety()+clipRect.geth() - RECT_TEST_SIZE /2);
        imgBRPos.resetw(RECT_TEST_SIZE);
        imgBRPos.reseth(RECT_TEST_SIZE);

        imgCPos.resetx(clipRect.getx()+clipRect.getw() /2);
        imgCPos.resety(clipRect.gety()+clipRect.geth() /2);
        imgCPos.resetw(RECT_TEST_SIZE);
        imgCPos.reseth(RECT_TEST_SIZE);

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
        screen.resetClipRect(clipRect);

        Rect table[5] = {imgTLPos,imgTRPos,imgBLPos,imgBRPos,imgCPos};

        for (int t=0; t< 5; ++t)
        {
            screen.setColorAt(table[t],m_fgc);
        }

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




