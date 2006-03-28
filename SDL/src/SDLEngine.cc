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

			//Enable texturing
			//glEnable(GL_TEXTURE_2D);

			//Load the texture
			//glBindTexture(GL_TEXTURE_2D, imagetexture);

			glBegin(GL_QUADS);
				//Top-left vertex (corner)
				glColor3f(0.0f,0.0f,1.0f);
				//glTexCoord2i(0,0);
				glVertex3f(1.0f, 1.0f, 1.0f);
				
				//Bottom-left vertex (corner)
				//glTexCoord2i(1,0);
				glVertex3f(2.0f, 1.0f, 1.0f);
				
				//Bottom-right vertex (corner)
				//glTexCoord2i(1,1);
				glVertex3f(2.0f, 2.0f, 0.0f);
				
				//Top-right vertex (corner)
				//glTexCoord2i(0,1);
				glVertex3f(1.0f, 2.0f, 0.0f);
			glEnd();

			//Disable texturing
			//glDisable(GL_TEXTURE_2D);

		}

			//to initialise the engine, just called once before any render
		bool DefaultGLEngine::init(int width, int height)
		{

			//loading the default RGBSurface from the Resources
			image = new RGBSurface();

			//if ( image->isGLvalid() ) 
				imagetexture=image->generateTexture();

			 //actual init code
			glShadeModel(GL_SMOOTH);       // Enable Smooth Shading
			glClearDepth(1.0f);         // Depth Buffer Setup
			glEnable(GL_DEPTH_TEST);       // Enables Depth Testing
			glDepthFunc(GL_LEQUAL);        // The Type Of Depth Testing To Do
			//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations

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
