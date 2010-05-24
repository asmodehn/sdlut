#ifndef TEST_RENDERING_HH
#define TEST_RENDERING_HH

#include "TestCommon.hh"

using namespace SDLut::video;

class RenderingAssertEngine : public AssertEngine
{

protected:
    Rect imgRPos;

//this Assert Engine check that loaded image is a proper ColorTest image
    std::vector<Rect> pos;
    std::vector<Color> color;

    Color m_bgColor;
    const Image * m_fgimg;
    const Image * m_bgimg;

public:

    RenderingAssertEngine(const Image & fgimage, const Image & bgimage, Logger & log, const ArgParser & ap)
            : AssertEngine(log,ap), imgRPos(), m_fgimg(&fgimage), m_bgimg(&bgimage)
    {
        //For rendering tests : pos and color needs to be filled in the constructor
        //For the foreground image only.
        //BProper blending computation with background image and background color will be taken care of, in render.
    }

    RenderingAssertEngine(const Image & fgimage, Color bgc, Logger & log, const ArgParser & ap)
            : AssertEngine(log,ap), imgRPos(), m_bgColor(bgc), m_fgimg(&fgimage), m_bgimg(0)
    {
        //For rendering tests : pos and color needs to be filled in the constructor
    }

    virtual ~RenderingAssertEngine()
    {}

    virtual bool assertresize(int width, int height)
    {
        imgRPos.resetx( (width - m_fgimg->getWidth()) / 2  );
        imgRPos.resety ( (height - m_fgimg->getHeight()) /2);
        imgRPos.resetw(m_fgimg->getWidth());
        imgRPos.reseth(m_fgimg->getHeight());
        return true;
    }

    virtual bool assertrender(ScreenBuffer & screen) const
    {
        bool res = true;
        for (unsigned int i= 0; i<pos.size() ; i++)
        {
            Color expctd;
            if ( m_fgimg )
            {
                if ( m_bgimg ) expctd = blend(blend(color[i],m_bgimg->getpixel( pos[i].getx(), pos[i].gety())),m_bgColor);
                else expctd = blend(color[i],m_bgColor);
            }
            Color real = screen.getColorAt(imgRPos.getx() + pos[i].getx(), imgRPos.gety() + pos[i].gety());
            if (!expctd.isSimilarTo(real))
            {
                m_log << nl << "Expected = " << expctd;
                m_log << nl << "Pixel at X = " << imgRPos.getx() + pos[i].getx() << " Y = " << imgRPos.gety() + pos[i].gety() << " : " << nl << real;
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


    const Image * getFGImage() const
    {
        return m_fgimg;
    }
    const Image * getBGImage() const
    {
        return m_bgimg;
    }
    const Color * getBGColor() const
    {
        return &m_bgColor;
    }
    const Rect * getImgPos() const
    {
        return &imgRPos;
    }

};

class RenderingTestEngine : public TestEngine
{

    //position of the surface to test in the screenbuffer
    const Rect * imgRPos;
    const Image * m_fgimg;
    const Image * m_bgimg;

public:

    RenderingTestEngine(Logger & log, RenderingAssertEngine & ae)
            : TestEngine(log,ae), imgRPos(ae.getImgPos()), m_fgimg(ae.getFGImage()), m_bgimg(ae.getBGImage())
    {
        //TODO Logfile should be enabled here
    }

    virtual ~RenderingTestEngine()
    {}

    virtual bool resize(int width, int height)
    {
        //putting image in screen center
        //taking care of resize for imgRPos should have been done already by AssertEngine
        return true;
    }

    virtual bool render(ScreenBuffer & screen) const
    {

        //copying rect from actual assert engine, to make sure we dont modify it
        Rect relpos = *imgRPos;

        //careful not to draw image not existing
        if ( m_bgimg) screen.blit(*m_bgimg,relpos);
        if ( m_fgimg) screen.blit(*m_fgimg,relpos);
        return true;
    }

};



#endif //TEST_RENDERING_HH
