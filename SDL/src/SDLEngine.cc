#include "SDLEngine.hh"

#include "SDLVideoSurface.hh"


//additional includes
#include <math.h>
//if not define by math (why ??)
#ifndef M_PI
#define M_PI  3.14159265358979323846
#endif

#include "SDLApp.hh"

namespace RAGE
{
    namespace SDL
    {


        //global variable
        std::string defaultlogoname("../data/SDL_logo.bmp");

        Engine::Engine() throw (std::logic_error)
        try : _screen(NULL), _backupscreen(NULL), _defaultlogo(defaultlogoname), _background(0,0,0)
        {
#ifdef DEBUG
            Log << nl << "Engine::Engine() called ...";
#endif


#ifdef DEBUG
            Log << nl << "Engine::Engine() done.";
#endif
        }
        catch (std::exception & e)
        {
            Log << nl
            << "Engine:: Exception in Constructor !"
            << nl << e.what() << std::endl;
        };

        Engine::~Engine()
        {
#ifdef DEBUG
            Log << nl << "Engine::~Engine() called ...";
#endif
            _screen = NULL;
            if (_backupscreen !=NULL )
                delete _backupscreen;

        #ifdef DEBUG
            Log << nl << "Engine::~Engine() done.";
#endif
        }

        bool Engine::setBGColor(const Color & color)
        {
            #ifdef DEBUG
            Log << nl << "Engine::setBGColor(" << color << ") called ...";
            #endif
            _background=color;
            if (_screen != NULL )
            {
                _screen->fill(_background);
            }
            #ifdef DEBUG
Log << nl << "Engine::setBGColor(" << color << ") done.";
#endif
            return true;
        }

        bool Engine::init(int width, int height)
        {

#ifdef DEBUG
            Log << nl << "Engine::init() called ...";
#endif
            _screen = App::getInstance().getWindow()->getDisplay();
            if ( _screen != NULL )
                _screen->fill(_background);
#ifdef DEBUG
            Log << nl << "Engine::init() done.";
#endif
            return _screen != NULL ;
        }

        bool Engine::resize(int width, int height)
        {
#ifdef DEBUG
            Log << nl << "Engine::resize(" << width << ", " << height << ") called ...";
#endif
            if ( _screen != NULL )
                _screen->fill(_background);


#ifdef DEBUG
            Log << nl << "Engine::resize(" << width << ", " << height << ") done.";
#endif
            return true;
        }

        //to call only when needed
        bool Engine::render(void) const
        {
#if DEBUG == 2
            Log << nl << "Engine::render() called ...";
#endif
            if ( _screen == NULL )
                Log << nl << "Engine not initialised, the render has been aborted." << std::endl;
            _screen->fill(_background);
            _screen->blit(_defaultlogo,Point((_screen->getWidth()-_defaultlogo.getWidth())/2,(_screen->getHeight()-_defaultlogo.getHeight())/2));
#if DEBUG == 2
            Log << nl << "Engine::render() done.";
#endif
        return true;
        }

        bool Engine::saveContent(void)
        {
            if (_backupscreen != NULL )
                delete _backupscreen;

            Log << nl << "Engine::saveContent()" << std::endl;
            // we create a new RGB surface to clone the display...
            assert(_screen);
            _backupscreen= new RGBSurface(*_screen);
            return _backupscreen!=NULL;
        }

        bool Engine::restoreContent(void)
        {
            assert(_screen);
            if (_backupscreen == NULL)
                return false;
            Log << nl << "Engine::restoreContent()" << std::endl;

            //to restore the content in the middle of the window
            Point newpos;
            newpos.setx( (_screen->getWidth()-_backupscreen->getWidth()) / 2 );
            newpos.sety( (_screen->getHeight()-_backupscreen->getHeight()) / 2 );

            Log << nl << "Blitting backupscreen at " << newpos << std::endl;
            return _screen->blit(*_backupscreen, newpos);
        }

#ifdef HAVE_OPENGL

        float rtri; // rotation angle
        float rquad; // rotation angle

        GLEngine::GLEngine() throw(std::logic_error)
        try : Engine()
        {
#ifdef DEBUG
            Log << nl << "GLEngine::GLEngine() called ...";
#endif


#ifdef DEBUG
            Log << nl << "GLEngine::GLEngine() done.";
#endif
        }
        catch(std::exception & e)
        {
            Log << nl
            << "GLEngine:: Exception in Constructor ! "
            << nl << e.what() << std::endl;
        };

        bool GLEngine::setBGColor(const Color & color)
        {
#ifdef DEBUG
            Log << nl << "GLEngine::setBGColor(" << color << ") called ..." << std::endl;
#endif
            _background=color;
            glClearColor(static_cast<float> (color.getR() ) / 255.0f, static_cast<float> (color.getG() ) / 255.0f,static_cast<float> (color.getB() ) / 255.0f,0.0f);

#ifdef DEBUG
            Log << nl << "GLEngine::setBGColor(" << color << ") done." << std::endl;
#endif
            return true;
        }

        bool GLEngine::init(int width, int height)
        {
            //actual init code
            std::cout << " 3D Engine's init" << std::endl;
            glShadeModel(GL_SMOOTH);       // Enable Smooth Shading
            glClearColor(static_cast<float> (_background.getR() ) / 255.0f, static_cast<float> (_background.getG() ) / 255.0f,static_cast<float> (_background.getB() ) / 255.0f, 0.0f);    // Black Background
            glClearDepth(1.0f);         // Depth Buffer Setup
            glEnable(GL_DEPTH_TEST);       // Enables Depth Testing
            glDepthFunc(GL_LEQUAL);        // The Type Of Depth Testing To Do
            glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations

            return resize(width,height);
        }

        bool GLEngine::resize(int width, int height)
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


        bool GLEngine::render(void) const
        {
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

#endif

    }
}

