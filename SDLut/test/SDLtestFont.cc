#include "SDL.hh"
#include "Logger.hh"
using namespace RAGE;

using namespace SDLut;
using namespace SDLut::font;
using namespace SDLut::video;

RAGE::Logger Log("Test Font");

//Engine will displayed the text with the different styles and rendermode availables in the font.

class MyEngine
{

    //typedef enum { Default, Normal, Bold, Italic, Underline} Style;
    //typedef enum { Solid, Shaded, Blended } RenderMode;

    Color m_color, m_bgcolor;

    Font m_font;

    // mutable to allow blit to change them to rendered rect instead
    mutable Rect sod,son,sob,soi,sou, shd,shn,shb,shi,shu, bld,bln,blb,bli,blu;

    Text tsod,tson,tsob,tsoi,tsou, tshd,tshn,tshb,tshi,tshu, tbld,tbln,tblb,tbli,tblu;

public:
    MyEngine(const Font & font)
            :   m_color(Color(255,255,255)),m_bgcolor(Color(64,64,64)),m_font(font)
    {
        tsod = Text("Default_Solid",m_font,m_color,m_bgcolor);
        tshd = Text("Default_Shaded",m_font,m_color,m_bgcolor);
        tbld = Text("Default_Blended",m_font,m_color,m_bgcolor);

        tson = Text("Normal_Solid",m_font,m_color,m_bgcolor);
        tshn = Text("Normal_Shaded",m_font,m_color,m_bgcolor);
        tbln = Text("Normal_Blended",m_font,m_color,m_bgcolor);

        tsob = Text("Bold_Solid",m_font,m_color,m_bgcolor);
        tshb = Text("Bold_Shaded",m_font,m_color,m_bgcolor);
        tblb = Text("Bold_Blended",m_font,m_color,m_bgcolor);

        tsoi = Text("Italic_Solid",m_font,m_color,m_bgcolor);
        tshi = Text("Italic_Shaded",m_font,m_color,m_bgcolor);
        tbli = Text("Italic_Blended",m_font,m_color,m_bgcolor);

        tsou = Text("Underl_Solid",m_font,m_color,m_bgcolor);
        tshu = Text("Underl_Shaded",m_font,m_color,m_bgcolor);
        tblu = Text("Underl_Blended",m_font,m_color,m_bgcolor);
    }

    ~MyEngine()
    {}


    bool init(int width, int height)
    {
        return resize(width,height);
    }

    bool resize(int width, int height)
    {
        int hmargin = static_cast<int>( .1 * width );
        int vmargin = static_cast<int>( .1 * height );
        int cwidth = ( width - 2* hmargin) / 3;
        int cheight = ( height - 2* vmargin) / 5;

        sod = Rect(hmargin,vmargin,cwidth,cheight);
        shd = Rect(hmargin + cwidth,vmargin,cwidth,cheight);
        bld = Rect(hmargin + 2* cwidth,vmargin,cwidth,cheight);

        son = Rect(hmargin,vmargin + cheight,cwidth,cheight);
        shn = Rect(hmargin + cwidth,vmargin+ cheight,cwidth,cheight);
        bln = Rect(hmargin + 2* cwidth,vmargin+ cheight,cwidth,cheight);

        sob = Rect(hmargin,vmargin+ cheight * 2,cwidth,cheight);
        shb = Rect(hmargin + cwidth,vmargin+ cheight * 2,cwidth,cheight);
        blb = Rect(hmargin + 2* cwidth,vmargin+ cheight * 2,cwidth,cheight);

        soi = Rect(hmargin,vmargin+ cheight * 3,cwidth,cheight);
        shi = Rect(hmargin + cwidth,vmargin+ cheight * 3,cwidth,cheight);
        bli = Rect(hmargin + 2* cwidth,vmargin+ cheight * 3,cwidth,cheight);

        sou = Rect(hmargin,vmargin+ cheight * 4,cwidth,cheight);
        shu = Rect(hmargin + cwidth,vmargin+ cheight * 4,cwidth,cheight);
        blu = Rect(hmargin + 2* cwidth,vmargin+ cheight * 4,cwidth,cheight);


        return true;
    }

    bool render( ScreenBuffer & screen) const
    {
        screen.blit(tsod,sod);
        screen.blit(tshd,shd);
        screen.blit(tbld,bld);

        return render_n(screen);
    }

    bool render_n( ScreenBuffer &screen) const
    {
        screen.blit(tson,son);
        screen.blit(tshn,shn);
        screen.blit(tbln,bln);

        return render_b(screen);
    }

    bool render_b( ScreenBuffer &screen) const
    {
        screen.blit(tsob,sob);
        screen.blit(tshb,shb);
        screen.blit(tblb,blb);

        return render_i(screen);
    }

    bool render_i( ScreenBuffer &screen) const
    {
        screen.blit(tsoi,soi);
        screen.blit(tshi,shi);
        screen.blit(tbli,bli);

        return render_u(screen);
    }

    bool render_u( ScreenBuffer &screen) const
    {
        screen.blit(tsou,sou);
        screen.blit(tshu,shu);
        screen.blit(tblu,blu);

        return true;
    }

};



//Main Program
int main(int argc, char** argv)
{
    //BUGs
    //in foreign keyb language keys are not displayed correctly (a --> q, z --> w)
    //unknown caracters shown another caracter (ç --> h; è --> g)
    //IN OpenGL mode: caracters are not displayed on the program windows

    RAGE::Logger testlog("Test Log");


#ifdef WK_OPENGL_FOUND
    bool ogl = true;
    if (argc > 1 && std::string(argv[1]) == "nogl" ) ogl = false;
#else
    bool ogl = false;
#endif

    //Setup example

    testlog << nl << " Enabling SDL Video... " << std::endl;
    App::getInstance().setName ("SDLut::SDL test - Font");
    App::getInstance().initVideo(false,false,false);
    App::getInstance().initText();

    testlog << nl << " Creating the User Interface... " << std::endl;

    Font font;

    if ((argc > 1 ) && std::string(argv[1]) != "nogl" )
    {
        //specific font
        font.setTTF(argv[1],24);
    }
    else if ( argc > 2 )
    {
        //specific font
        font.setTTF(argv[2],24);
    }

    MyEngine engine(font);

    App::getInstance().getDisplay().getScreenRequest().requestOpenGL(ogl);
	App::getInstance().getDisplay().getScreenRequest().requestSize(800,600);

    App::getInstance().getDisplay().resetInitCallback(engine,&MyEngine::init);
    App::getInstance().getDisplay().resetResizeCallback(engine,&MyEngine::resize);
    App::getInstance().getDisplay().resetRenderCallback(engine,&MyEngine::render);

	if ( App::getInstance().getDisplay().show() )
    {
        App::getInstance().getDisplay().mainLoop();
    }

    return 0;
}


