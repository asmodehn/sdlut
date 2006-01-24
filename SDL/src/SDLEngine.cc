#include "SDLEngine.hh"

//#include "SDLVideoSurface.hh"


////additional includes
//#include <math.h>
////if not define by math (why ??)
//#ifndef M_PI
//#define M_PI  3.14159265358979323846
//#endif

//#include "SDLApp.hh" //to access the display only
//
//namespace RAGE
//{
//    namespace SDL
//    {
//        Engine::Engine(VideoSurface * display) throw (std::logic_error)
//        try
//        : //Carefull the display should already be initialised before constructing the Engine
//            _screen(display)
//        {
//#ifdef DEBUG
//            Log << nl << "Engine::Engine() called ...";
//#endif
//
//
//#ifdef DEBUG
//
//            Log << nl << "Engine::Engine() done.";
//#endif
//
//        }
//        catch (std::exception & e)
//        {
//            Log << nl
//            << "Engine:: Exception in Constructor !"
//            << nl << e.what() << std::endl;
//        };


//        bool Engine::init(int width, int height)
//        {
//
//#ifdef DEBUG
//            Log << nl << "Engine::init() called ...";
//#endif
//
//            _screen = App::getInstance().getWindow()->getDisplay();
//
//#ifdef DEBUG
//
//            Log << nl << "Engine::init() done.";
//#endif
//
//            return _screen != NULL ;
//        }
//
////        //to call only when needed
////        bool Engine::render(void) const
////        {
////#if (DEBUG == 2)
////            Log << nl << "Engine::render() called ...";
////#endif
////
////            if ( _screen == NULL )
////            {
////                Log << nl << "Engine not initialised, the render has been aborted." << std::endl;
////            }
////            else
////{
////                _screen->blit(_defaultlogo,Point((_screen->getWidth()-_defaultlogo.getWidth())/2,(_screen->getHeight()-_defaultlogo.getHeight())/2));
////}
////#if (DEBUG == 2)
////            Log << nl << "Engine::render() done.";
////#endif
////
////            return true;
////        }
//
//
//
//#ifdef HAVE_OPENGL
//
//        float rtri; // rotation angle
//        float rquad; // rotation angle
//
//        GLEngine::GLEngine() throw(std::logic_error)
//        try
//        :
//            Engine()
//        {
//#ifdef DEBUG
//            Log << nl << "GLEngine::GLEngine() called ...";
//#endif
//
//
//#ifdef DEBUG
//
//            Log << nl << "GLEngine::GLEngine() done.";
//#endif
//
//        }
//        catch(std::exception & e)
//        {
//            Log << nl
//            << "GLEngine:: Exception in Constructor ! "
//            << nl << e.what() << std::endl;
//        };
//
//
//
//        bool GLEngine::init(int width, int height)
//        {
//            //actual init code
//#ifdef DEBUG
//            Log << nl <<"GLEngine::init("<< width <<", " << height << ") called...";
//#endif
//            glShadeModel(GL_SMOOTH);       // Enable Smooth Shading
//            glClearDepth(1.0f);         // Depth Buffer Setup
//            glEnable(GL_DEPTH_TEST);       // Enables Depth Testing
//            glDepthFunc(GL_LEQUAL);        // The Type Of Depth Testing To Do
//            glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations
//
//#ifdef DEBUG
//    Log << nl <<"GLEngine::init("<< width <<", " << height << ") done.";
//#endif
//            return resize(width,height);
//        }
//
//        bool GLEngine::resize(int width, int height)
//        {
//#ifdef DEBUG
//            Log << nl <<"GLEngine::resize("<< width <<", " << height << ") called...";
//#endif
//            //resize code
//            glViewport(0,0,width,height);      // Reset The Current Viewport
//            //maybe in  glsurface ?
//
//            glMatrixMode(GL_PROJECTION);      // Select The Projection Matrix
//            glLoadIdentity();         // Reset The Projection Matrix
//
//            GLdouble znear = 0.1f ;
//            GLdouble zfar = 100.0f ;
//            GLdouble ymax = znear * tan(45.0f * M_PI / 360.0);
//            GLdouble ymin = -ymax;
//            GLdouble xmin = ymin * GLfloat(width) / GLfloat(height);
//            GLdouble xmax = ymax * GLfloat(width) / GLfloat(height);
//
//            glFrustum(xmin, xmax, ymin, ymax, znear, zfar);
//
//            glMatrixMode(GL_MODELVIEW);       // Select The Modelview Matrix
//            glLoadIdentity();
//
//#ifdef DEBUG
//    Log << nl <<"GLEngine::resize("<< width <<", " << height << ") done.";
//#endif
//
//            return true;
//
//        }
//
//
//        bool GLEngine::render(void) const
//        {
//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
//            glLoadIdentity();         // Reset The Current Modelview Matrix
//            glTranslatef(-1.5f,0.0f,-6.0f);      // Move Left 1.5 Units And Into The Screen 6.0
//            glRotatef(rtri,0.0f,1.0f,0.0f);      // Rotate The Triangle On The Y axis ( NEW )
//            glBegin(GL_TRIANGLES);        // Start Drawing A Triangle
//            glColor3f(1.0f,0.0f,0.0f);      // Red
//            glVertex3f( 0.0f, 1.0f, 0.0f);     // Top Of Triangle (Front)
//            glColor3f(0.0f,1.0f,0.0f);      // Green
//            glVertex3f(-1.0f,-1.0f, 1.0f);     // Left Of Triangle (Front)
//            glColor3f(0.0f,0.0f,1.0f);      // Blue
//            glVertex3f( 1.0f,-1.0f, 1.0f);     // Right Of Triangle (Front)
//            glColor3f(1.0f,0.0f,0.0f);      // Red
//            glVertex3f( 0.0f, 1.0f, 0.0f);     // Top Of Triangle (Right)
//            glColor3f(0.0f,0.0f,1.0f);      // Blue
//            glVertex3f( 1.0f,-1.0f, 1.0f);     // Left Of Triangle (Right)
//            glColor3f(0.0f,1.0f,0.0f);      // Green
//            glVertex3f( 1.0f,-1.0f, -1.0f);     // Right Of Triangle (Right)
//            glColor3f(1.0f,0.0f,0.0f);      // Red
//            glVertex3f( 0.0f, 1.0f, 0.0f);     // Top Of Triangle (Back)
//            glColor3f(0.0f,1.0f,0.0f);      // Green
//            glVertex3f( 1.0f,-1.0f, -1.0f);     // Left Of Triangle (Back)
//            glColor3f(0.0f,0.0f,1.0f);      // Blue
//            glVertex3f(-1.0f,-1.0f, -1.0f);     // Right Of Triangle (Back)
//            glColor3f(1.0f,0.0f,0.0f);      // Red
//            glVertex3f( 0.0f, 1.0f, 0.0f);     // Top Of Triangle (Left)
//            glColor3f(0.0f,0.0f,1.0f);      // Blue
//            glVertex3f(-1.0f,-1.0f,-1.0f);     // Left Of Triangle (Left)
//            glColor3f(0.0f,1.0f,0.0f);      // Green
//            glVertex3f(-1.0f,-1.0f, 1.0f);     // Right Of Triangle (Left)
//            glEnd();           // Done Drawing The Pyramid
//
//            glLoadIdentity();         // Reset The Current Modelview Matrix
//            glTranslatef(1.5f,0.0f,-7.0f);      // Move Right 1.5 Units And Into The Screen 7.0
//            glRotatef(rquad,1.0f,1.0f,1.0f);     // Rotate The Quad On The X axis ( NEW )
//            glBegin(GL_QUADS);         // Draw A Quad
//            glColor3f(0.0f,1.0f,0.0f);      // Set The Color To Green
//            glVertex3f( 1.0f, 1.0f,-1.0f);     // Top Right Of The Quad (Top)
//            glVertex3f(-1.0f, 1.0f,-1.0f);     // Top Left Of The Quad (Top)
//            glVertex3f(-1.0f, 1.0f, 1.0f);     // Bottom Left Of The Quad (Top)
//            glVertex3f( 1.0f, 1.0f, 1.0f);     // Bottom Right Of The Quad (Top)
//            glColor3f(1.0f,0.5f,0.0f);      // Set The Color To Orange
//            glVertex3f( 1.0f,-1.0f, 1.0f);     // Top Right Of The Quad (Bottom)
//            glVertex3f(-1.0f,-1.0f, 1.0f);     // Top Left Of The Quad (Bottom)
//            glVertex3f(-1.0f,-1.0f,-1.0f);     // Bottom Left Of The Quad (Bottom)
//            glVertex3f( 1.0f,-1.0f,-1.0f);     // Bottom Right Of The Quad (Bottom)
//            glColor3f(1.0f,0.0f,0.0f);      // Set The Color To Red
//            glVertex3f( 1.0f, 1.0f, 1.0f);     // Top Right Of The Quad (Front)
//            glVertex3f(-1.0f, 1.0f, 1.0f);     // Top Left Of The Quad (Front)
//            glVertex3f(-1.0f,-1.0f, 1.0f);     // Bottom Left Of The Quad (Front)
//            glVertex3f( 1.0f,-1.0f, 1.0f);     // Bottom Right Of The Quad (Front)
//            glColor3f(1.0f,1.0f,0.0f);      // Set The Color To Yellow
//            glVertex3f( 1.0f,-1.0f,-1.0f);     // Top Right Of The Quad (Back)
//            glVertex3f(-1.0f,-1.0f,-1.0f);     // Top Left Of The Quad (Back)
//            glVertex3f(-1.0f, 1.0f,-1.0f);     // Bottom Left Of The Quad (Back)
//            glVertex3f( 1.0f, 1.0f,-1.0f);     // Bottom Right Of The Quad (Back)
//            glColor3f(0.0f,0.0f,1.0f);      // Set The Color To Blue
//            glVertex3f(-1.0f, 1.0f, 1.0f);     // Top Right Of The Quad (Left)
//            glVertex3f(-1.0f, 1.0f,-1.0f);     // Top Left Of The Quad (Left)
//            glVertex3f(-1.0f,-1.0f,-1.0f);     // Bottom Left Of The Quad (Left)
//            glVertex3f(-1.0f,-1.0f, 1.0f);     // Bottom Right Of The Quad (Left)
//            glColor3f(1.0f,0.0f,1.0f);      // Set The Color To Violet
//            glVertex3f( 1.0f, 1.0f,-1.0f);     // Top Right Of The Quad (Right)
//            glVertex3f( 1.0f, 1.0f, 1.0f);     // Top Left Of The Quad (Right)
//            glVertex3f( 1.0f,-1.0f, 1.0f);     // Bottom Left Of The Quad (Right)
//            glVertex3f( 1.0f,-1.0f,-1.0f);     // Bottom Right Of The Quad (Right)
//            glEnd();           // Done Drawing The Quad
//
//            rtri+=0.2f;           // Increase The Rotation Variable For The Triangle ( NEW )
//            rquad-=0.15f;          // Decrease The Rotation Variable For The Quad ( NEW )
//            // Keep Going
//            return true;
//        }
//
//#endif
//

//}
//}
