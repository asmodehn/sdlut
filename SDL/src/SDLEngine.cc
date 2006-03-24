#include "SDLEngine.hh"

namespace RAGE
{
    namespace SDL
    {

		//this render function should not modify the engine
		void DefaultEngine::render(VideoSurface & screen) const
		{
			screen.blit(*image,Point( screen.getWidth() - image->getWidth(), screen.getHeight() - image->getHeight()));
		}

			//to initialise the engine, just called once before any render
		bool DefaultEngine::init(int width, int height)
		{
			//loading the default RGBSurface from the Resources
			image = new RGBSurface();
			return image != NULL;
		}

		//get called everytime the display is resized
		bool DefaultEngine::resize(int width, int height)
		{
			return true;
		}
	}
}

#ifdef HAVE_OPENGL

		
#include <math.h>
//if not define by math (why ??)
#ifndef M_PI
#define M_PI  3.14159265358979323846
#endif

namespace RAGE
{
    namespace SDL
    {


			//this is run just before the render
		void DefaultGLEngine::prerender(void)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
		}

			//this render function should not modify the engine
		void DefaultGLEngine::render(VideoSurface& screen) const
		{
			//This default rendering should be something with OpenGL logo...
			//TODO

			        static float rtri; // rotation angle
			static float rquad; // rotation angle
	
			
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
		}

			//to initialise the engine, just called once before any render
		bool DefaultGLEngine::init(int width, int height)
		{
			 //actual init code
			glShadeModel(GL_SMOOTH);       // Enable Smooth Shading
			glClearDepth(1.0f);         // Depth Buffer Setup
			glEnable(GL_DEPTH_TEST);       // Enables Depth Testing
			glDepthFunc(GL_LEQUAL);        // The Type Of Depth Testing To Do
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations

	        return resize(width,height);
		}

			//get called everytime the display is resized
		bool DefaultGLEngine::resize(int width, int height)
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
	}
}

#endif //HAVE_OPENGL
