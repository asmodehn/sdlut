#include "SDL.hh"
using namespace RAGE;
using namespace RAGE::SDL;


//Defining UserInput
class MyUserInput : public Keyboard
{
public:

    virtual bool handleKeyEvent (const Sym &s, bool pressed)
    {
        bool res = false;
            switch( s.getKey() )
            {
                case KEscape:
                if (pressed==false)
                {
#ifdef DEBUG
                    Log << nl << "Quit requested !" << std::endl;
#endif

                    _quitRequested=true;
                    res=true;
                }
                break;
                case KF5:
                if (pressed==true)
                    App::getInstance().getWindow()->iconify();
                res = true;
                break;
                case KF6:
                if (pressed==true)
                    App::getInstance().getWindow()->toggleFullScreen();
                res = true;
                break;
                default:
                res = false;
            }
        return res;
    }
};

class MyEngine : public Engine
{

    RGBSurface _defaultlogocopy;
	Font _font;
	RGBSurface _text;

public:
    MyEngine()
		: _font("data/ECHELON.ttf",16),_text(_font,"Blahblahblah",Color(0,0,255),RGBColor(0,0xFF,0))
    {
        RGBSurface _defaultlogo("data/SDL_logo.bmp",Color(0xFF,0xFF,0xff));
        Log << nl << "Assignment ... TEST";
        _defaultlogocopy = _defaultlogo;
        Log << nl << "Assignment... END";
    }

    virtual ~MyEngine(){}

    bool init(int width, int height)
    {
            Log << nl << _defaultlogocopy;
            return true;
    }

    bool resize(int width, int height)
    {return true;}

    bool render(void) const
    {
        bool res = false;
        if ( _screen != NULL )
        {
            Log << nl<< "Copie TEST";
            RGBSurface _defaultlogocopy2(_defaultlogocopy);
            Log << nl << "Copie END";
            res= _screen->blit(_defaultlogocopy2,Point((_screen->getWidth()-_defaultlogocopy2.getWidth())/2,(_screen->getHeight()-_defaultlogocopy2.getHeight())/2));

			res= _screen->blit(_text,Point(20,20));
        }

        return res;
    }
};

#include <math.h>
//if not define by math (why ??)
#ifndef M_PI
#define M_PI  3.14159265358979323846
#endif

class MyGLEngine : public Engine
{
    public:
    bool init(int width, int height)
    {
        //actual init code
        glShadeModel(GL_SMOOTH);       // Enable Smooth Shading
        glClearDepth(1.0f);         // Depth Buffer Setup
        glEnable(GL_DEPTH_TEST);       // Enables Depth Testing
        glDepthFunc(GL_LEQUAL);        // The Type Of Depth Testing To Do
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations

        return resize(width,height);
    }

    bool resize(int width, int height)
    {
        //resize code
        glViewport(0,0,width,height);      // Reset The Current Viewport

        glMatrixMode(GL_PROJECTION);      // Select The Projection Matrix
        glLoadIdentity();         // Reset The Projection Matrix

        GLdouble znear = 0.1f ;
        GLdouble zfar = 100.0f ;
        GLdouble ymax = znear * tan(45.0f * M_PI / 360.0);
        GLdouble ymin = -ymax;
        GLdouble xmin = ymin * GLfloat(width) / GLfloat(height);
        GLdouble xmax = ymax * GLfloat(width) / GLfloat(height);

        glFrustum(xmin, xmax, ymin, ymax, znear, zfar);

        glMatrixMode(GL_MODELVIEW);       // Select The Modelview Matrix
        glLoadIdentity();

        return true;

    }


    bool render(void) const
    {
        static float rtri; // rotation angle
        static float rquad; // rotation angle

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
        glLoadIdentity();         // Reset The Current Modelview Matrix
        glTranslatef(-1.5f,0.0f,-6.0f);      // Move Left 1.5 Units And Into The Screen 6.0
        glRotatef(rtri,0.0f,1.0f,0.0f);      // Rotate The Triangle On The Y axis ( NEW )
        glBegin(GL_TRIANGLES);        // Start Drawing A Triangle
        glColor3f(1.0f,0.0f,0.0f);      // Red
        glVertex3f( 0.0f, 1.0f, 0.0f);     // Top Of Triangle (Front)
        glColor3f(0.0f,1.0f,0.0f);      // Green
        glVertex3f(-1.0f,-1.0f, 1.0f);     // Left Of Triangle (Front)
        glColor3f(0.0f,0.0f,1.0f);      // Blue
        glVertex3f( 1.0f,-1.0f, 1.0f);     // Right Of Triangle (Front)
        glColor3f(1.0f,0.0f,0.0f);      // Red
        glVertex3f( 0.0f, 1.0f, 0.0f);     // Top Of Triangle (Right)
        glColor3f(0.0f,0.0f,1.0f);      // Blue
        glVertex3f( 1.0f,-1.0f, 1.0f);     // Left Of Triangle (Right)
        glColor3f(0.0f,1.0f,0.0f);      // Green
        glVertex3f( 1.0f,-1.0f, -1.0f);     // Right Of Triangle (Right)
        glColor3f(1.0f,0.0f,0.0f);      // Red
        glVertex3f( 0.0f, 1.0f, 0.0f);     // Top Of Triangle (Back)
        glColor3f(0.0f,1.0f,0.0f);      // Green
        glVertex3f( 1.0f,-1.0f, -1.0f);     // Left Of Triangle (Back)
        glColor3f(0.0f,0.0f,1.0f);      // Blue
        glVertex3f(-1.0f,-1.0f, -1.0f);     // Right Of Triangle (Back)
        glColor3f(1.0f,0.0f,0.0f);      // Red
        glVertex3f( 0.0f, 1.0f, 0.0f);     // Top Of Triangle (Left)
        glColor3f(0.0f,0.0f,1.0f);      // Blue
        glVertex3f(-1.0f,-1.0f,-1.0f);     // Left Of Triangle (Left)
        glColor3f(0.0f,1.0f,0.0f);      // Green
        glVertex3f(-1.0f,-1.0f, 1.0f);     // Right Of Triangle (Left)
        glEnd();           // Done Drawing The Pyramid

        glLoadIdentity();         // Reset The Current Modelview Matrix
        glTranslatef(1.5f,0.0f,-7.0f);      // Move Right 1.5 Units And Into The Screen 7.0
        glRotatef(rquad,1.0f,1.0f,1.0f);     // Rotate The Quad On The X axis ( NEW )
        glBegin(GL_QUADS);         // Draw A Quad
        glColor3f(0.0f,1.0f,0.0f);      // Set The Color To Green
        glVertex3f( 1.0f, 1.0f,-1.0f);     // Top Right Of The Quad (Top)
        glVertex3f(-1.0f, 1.0f,-1.0f);     // Top Left Of The Quad (Top)
        glVertex3f(-1.0f, 1.0f, 1.0f);     // Bottom Left Of The Quad (Top)
        glVertex3f( 1.0f, 1.0f, 1.0f);     // Bottom Right Of The Quad (Top)
        glColor3f(1.0f,0.5f,0.0f);      // Set The Color To Orange
        glVertex3f( 1.0f,-1.0f, 1.0f);     // Top Right Of The Quad (Bottom)
        glVertex3f(-1.0f,-1.0f, 1.0f);     // Top Left Of The Quad (Bottom)
        glVertex3f(-1.0f,-1.0f,-1.0f);     // Bottom Left Of The Quad (Bottom)
        glVertex3f( 1.0f,-1.0f,-1.0f);     // Bottom Right Of The Quad (Bottom)
        glColor3f(1.0f,0.0f,0.0f);      // Set The Color To Red
        glVertex3f( 1.0f, 1.0f, 1.0f);     // Top Right Of The Quad (Front)
        glVertex3f(-1.0f, 1.0f, 1.0f);     // Top Left Of The Quad (Front)
        glVertex3f(-1.0f,-1.0f, 1.0f);     // Bottom Left Of The Quad (Front)
        glVertex3f( 1.0f,-1.0f, 1.0f);     // Bottom Right Of The Quad (Front)
        glColor3f(1.0f,1.0f,0.0f);      // Set The Color To Yellow
        glVertex3f( 1.0f,-1.0f,-1.0f);     // Top Right Of The Quad (Back)
        glVertex3f(-1.0f,-1.0f,-1.0f);     // Top Left Of The Quad (Back)
        glVertex3f(-1.0f, 1.0f,-1.0f);     // Bottom Left Of The Quad (Back)
        glVertex3f( 1.0f, 1.0f,-1.0f);     // Bottom Right Of The Quad (Back)
        glColor3f(0.0f,0.0f,1.0f);      // Set The Color To Blue
        glVertex3f(-1.0f, 1.0f, 1.0f);     // Top Right Of The Quad (Left)
        glVertex3f(-1.0f, 1.0f,-1.0f);     // Top Left Of The Quad (Left)
        glVertex3f(-1.0f,-1.0f,-1.0f);     // Bottom Left Of The Quad (Left)
        glVertex3f(-1.0f,-1.0f, 1.0f);     // Bottom Right Of The Quad (Left)
        glColor3f(1.0f,0.0f,1.0f);      // Set The Color To Violet
        glVertex3f( 1.0f, 1.0f,-1.0f);     // Top Right Of The Quad (Right)
        glVertex3f( 1.0f, 1.0f, 1.0f);     // Top Left Of The Quad (Right)
        glVertex3f( 1.0f,-1.0f, 1.0f);     // Bottom Left Of The Quad (Right)
        glVertex3f( 1.0f,-1.0f,-1.0f);     // Bottom Right Of The Quad (Right)
        glEnd();           // Done Drawing The Quad

        rtri+=0.2f;           // Increase The Rotation Variable For The Triangle ( NEW )
        rquad-=0.15f;          // Decrease The Rotation Variable For The Quad ( NEW )
        // Keep Going
        return true;
    }
};

//Main Program
int main(int argc, char** argv)
{

    Logger testlog("Test Log");

    //Setup example

    testlog << nl << " Enabling SDL Video... " << std::endl;
    App::getInstance().setName ("SDLtest");
    App::getInstance().initVideo(false,false,true,false);

    //Getting video informations
    testlog << nl << *App::getInstance().getWindow()->getVideoInfo() << std::endl;

    testlog << nl << " Creating the User Interface... " << std::endl;
    //UI Creation
    MyUserInput ui;
    App::getInstance().getWindow()->getEventManager()->setKeyboard(&ui);

    testlog << nl << " Creating the SDL Cursor... " << std::endl;
    Cursor cursor(blackArrow);
    cursor.show();
    Cursor::setCurrent(cursor);

    // RGBSurface bitmap (bitmapname);
    //
    // int newW=bitmap.getWidth()+60;
    // int newH=bitmap.getHeight()+60;

	App::getInstance().initText(); //to do before using the Engine

    App::getInstance().getWindow()->setBGColor(Color (128,0,0));
    App::getInstance().getWindow()->setEngine(new MyEngine());


    if (! (App::getInstance().getWindow()->resetDisplay()))
    {
        testlog << nl << "Display Creation FAILED !"<< std::endl;
        exit(0);
    }
    else
    {
        VideoSurface* display=App::getInstance().getWindow()->getDisplay();
        testlog << nl << *display << std::endl;

        //  display->blit(bitmap,Point(30,30));
        //
        //  RGBSurface smiley("icon.bmp",Color(255,255,255));
        //        smiley.optimise(true);
        //
        //  testlog << nl << std::boolalpha << display->blit(smiley,Point(50,50)) << std::endl;

        Cursor::warpCurrent(Point(50,50));

        App::getInstance().getWindow()->mainLoop();

    }

    //First test ended : go on to test OPENGL

    testlog << nl << " OPENGL activation... " << std::endl;

    MyUserInput ui2; // another ui, since the first is closed ( but not deleted )
    App::getInstance().getWindow()->getEventManager()->setKeyboard(&ui2);
    testlog << nl <<"display reset" << std::endl;

    App::getInstance().getWindow()->setGLEngine(new MyGLEngine());
    //GLManager test
    GLManager * glman=App::getInstance().getWindow()->getGLManager();
    testlog << nl<<std::boolalpha <<
    "setRsize(5) " << glman->setRSize(5) << nl <<
    "setGSize(5) " << glman->setGSize(5) << nl <<
    "setBSize(5) " << glman->setBSize(5) << nl <<
    "setASize(5) " << glman->setASize(5) << nl <<
    "setBufferSize(5) " << glman->setBufferSize(12) << nl <<
    std::endl;

    App::getInstance().getWindow()->setOpenGL(true);

    if(App::getInstance().getWindow()->resetDisplay())
    {


        //GLManager test
        testlog << nl << *glman << std::endl;

        VideoSurface* display=App::getInstance().getWindow()->getDisplay();
        testlog << nl << "calling display->debug() " << std::endl;
        testlog << nl << *display <<std::endl;

        testlog << nl << std::boolalpha << " setDepthSize(16) " << glman->setDepthSize(16) << std::endl;

        testlog << nl << *glman << std::endl;

        testlog << nl << "loop... " << std::endl;
        App::getInstance().getWindow()->mainLoop();
    }

    return 0;
}


