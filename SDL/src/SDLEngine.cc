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
#pragma message( "DefaultGLEngine not finished yet!!!")

			//this is run just before the render
		void DefaultGLEngine::prerender(void)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
		}

			//this render function should not modify the engine
		void DefaultGLEngine::render(VideoSurface& screen) const
		{

			//3D Rendering

//glEnable( GL_DEPTH_TEST ) ;
//glMatrixMode( GL_PROJECTION ) ;
//glLoadIdentity() ;
//
//			glMatrixMode(GL_PROJECTION);      // Select The Projection Matrix
//			glLoadIdentity();         // Reset The Projection Matrix
//	
//			GLdouble znear = 0.1f ;
//			GLdouble zfar = 100.0f ;
//			GLdouble ymax = znear * tan(45.0f * M_PI / 360.0);
//			GLdouble ymin = -ymax;
//			GLdouble xmin = ymin * GLfloat(width) / GLfloat(height);
//			GLdouble xmax = ymax * GLfloat(width) / GLfloat(height);
//	
//			glFrustum(xmin, xmax, ymin, ymax, znear, zfar);


			//2D Rendering

glDisable( GL_DEPTH_TEST ) ;
glMatrixMode( GL_PROJECTION ) ;
glLoadIdentity() ;
//
///*
// * Upside-down square viewport : it maps the screen as if the (arbitrary-set) resolution were
// * 1000x1000 pixels.
// *
// */
//
glOrtho( /* left */ 0, /* right */ screen.getWidth(), /* bottom */ screen.getHeight(), /* top */ 0, /* near */ 0, /* far */ 1 ) ;
//- or, preferably to keep the 4/3 ratio like 800x600, 640x480, 1024x768, etc. - 
//
//// Non-reversed 4/3 viewport :	
//glOrtho( /* left */ -320.0f, /* right */ 320.0f, /* bottom */ -240.0f, /* top */ 240.0f, 
//	/* near */ -1, /* far */ 1 ) ;
////use one or the other depending if your texture is flipped or not vertically
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			//Enable texturing
			glEnable(GL_TEXTURE_2D);

			//Load the texture
			glBindTexture(GL_TEXTURE_2D, imagetexture);

//glColor4f( 1.0, 1.0, 1.0, 1.0 ) ;
glDisable(GL_CULL_FACE);

glBegin( GL_QUADS ) ;
	glTexCoord2i( 0,0) ;
	glVertex2i( screen.getWidth() - image->getWidth() , screen.getHeight()- image->getHeight() ) ;
	
	glTexCoord2i( 0, 1) ;
	glVertex2i( screen.getWidth() - image->getWidth() , screen.getHeight()) ;
	
	glTexCoord2i( 1, 1) ;
	glVertex2i( screen.getWidth() , screen.getHeight()) ;
	
	glTexCoord2i( 1, 0) ;
	glVertex2i( screen.getWidth(), screen.getHeight() - image->getHeight() ) ;
glEnd() ;


			//Disable texturing
			glDisable(GL_TEXTURE_2D);



		}

			//to initialise the engine, just called once before any render
		bool DefaultGLEngine::init(int width, int height)
		{

			//loading the default RGBSurface from the Resources
			image = new RGBSurface();

			//if ( image->isGLvalid() ) 
			imagetexture=image->generateTexture();
			Log << nl << imagetexture;

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
	
			return true;

		}
	}
}

#endif //HAVE_OPENGL
