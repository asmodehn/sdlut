#include "SDLEngine.hh"
#include "SDLConfig.hh"


namespace RAGE
{
    namespace SDL
    {

		//loading the default RGBSurface from the Resources as logo
	    DefaultEngine::DefaultEngine()
	    {
	    }
	    
		//this render function should not modify the engine
		void DefaultEngine::render(VideoSurface & screen) const
		{
			screen.blit(_logo,Point( screen.getWidth() - _logo.getWidth(), screen.getHeight() - _logo.getHeight()));
		}

			//to initialise the engine, just called once before any render
		bool DefaultEngine::init(int width, int height)
		{
			return true;
		}

		//get called everytime the display is resized
		bool DefaultEngine::resize(int width, int height)
		{
			return true;
		}
		
		DefaultEngine::~DefaultEngine()
		{
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

		DefaultGLEngine::DefaultGLEngine() : _logotexture(0)
		{
		}

	    DefaultGLEngine::~DefaultGLEngine()
	    {
		    if (_logotexture!=0) glDeleteTextures(1, &_logotexture);
	    }

	    
		//this is run just before the render
		void DefaultGLEngine::prerender(unsigned long deltaticks)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
		}

			//this render function should not modify the engine
		void DefaultGLEngine::render(VideoSurface& screen) const
		{

			//2D Rendering

			glDisable( GL_DEPTH_TEST ) ;
			glMatrixMode( GL_PROJECTION ) ;
			glLoadIdentity() ;

			glOrtho( 0, screen.getWidth(), screen.getHeight(), 0, 0, 1 ) ;
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			//Enable texturing
			glEnable(GL_TEXTURE_2D);

			//Load the texture
			glBindTexture(GL_TEXTURE_2D, _logotexture);

			glBegin( GL_QUADS ) ;
				glTexCoord2i( 0,0) ;
				glVertex2i( screen.getWidth() - _logo.getWidth() , screen.getHeight()- _logo.getHeight() ) ;
	
				glTexCoord2i( 0, 1) ;
				glVertex2i( screen.getWidth() - _logo.getWidth() , screen.getHeight()) ;
	
				glTexCoord2i( 1, 1) ;
				glVertex2i( screen.getWidth() , screen.getHeight()) ;
				
				glTexCoord2i( 1, 0) ;
				glVertex2i( screen.getWidth(), screen.getHeight() - _logo.getHeight() ) ;
			glEnd() ;


			//Disable texturing
			glDisable(GL_TEXTURE_2D);
		}

			//to initialise the engine, just called once before any render
		bool DefaultGLEngine::init(int width, int height)
		{
			//texture generation
			_logotexture=_logo.generateTexture();
			if (glIsTexture(_logotexture) !=GL_TRUE)
			{
				Log << nl << "Unable to generate logo texture" ;
			}

			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering
			
			//actual init code
			glShadeModel(GL_SMOOTH);       // Enable Smooth Shading
			glClearDepth(1.0f);         // Depth Buffer Setup
			glEnable(GL_DEPTH_TEST);       // Enables Depth Testing
			glDepthFunc(GL_LEQUAL);        // The Type Of Depth Testing To Do
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations

			glViewport(0,0,width,height);      // Reset The Current Viewport
	
			glMatrixMode(GL_PROJECTION);      // Select The Projection Matrix
			glLoadIdentity();         // Reset The Projection Matrix
			return true;
		}

			//get called everytime the display is resized
		bool DefaultGLEngine::resize(int width, int height)
		{
			//SDL is losing OpenGL context when recreating the window, which we do for the resize.
			//so we basically need to re init it completely
			init(width, height);

			//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
			//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering
			//
			////actual init code
			//glShadeModel(GL_SMOOTH);       // Enable Smooth Shading
			//glClearDepth(1.0f);         // Depth Buffer Setup
			//glEnable(GL_DEPTH_TEST);       // Enables Depth Testing
			//glDepthFunc(GL_LEQUAL);        // The Type Of Depth Testing To Do
			//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations

			////resize code
		 //   glViewport(0,0,width,height);      // Reset The Current Viewport
	
			//glMatrixMode(GL_PROJECTION);      // Select The Projection Matrix
			//glLoadIdentity();         // Reset The Projection Matrix
	
			return true;

		}
	}
}

#endif //HAVE_OPENGL
