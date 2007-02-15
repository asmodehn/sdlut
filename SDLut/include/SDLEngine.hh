#ifndef SDL_ENGINE_HH
#define SDL_ENGINE_HH

/*******************************************************************************
 * Interface with other systems
 ******************************************************************************/

#include "SDLRGBSurface.hh"
#include "SDLVideoSurface.hh"

namespace RAGE
{
    namespace SDL
    {

        // Engine interface
        class Engine
        {

		public:
			//this is run just before the render
			//deltaticks is the amount of ticks between the end of the last render and now.
			virtual void prerender(unsigned long deltaticks) {}

			//this render function should not modify the engine
            virtual void render(VideoSurface & screen) const = 0;

			//this is run just after the render, and refresh of the screen
			virtual void postrender(void) {}

			//to initialise the engine, just called once before any render
            virtual bool init(int width, int height) = 0;

			//call everytime the display is resized
            virtual bool resize(int width, int height) = 0;
        };

		// Default 2D Engine ( only used if no engine is defined )
		class DefaultEngine : public Engine
        {
			protected:
			//will be initialized in init
			//might be better in a constructor actually...
			RGBSurface * _logo;

			public:

			DefaultEngine() : _logo(NULL) {}

			//this render function should not modify the engine
            virtual void render(VideoSurface & screen) const;

			//to initialise the engine, just called once before any render
            virtual bool init(int width, int height);

			//call everytime the display is resized
            virtual bool resize(int width, int height);
		};

#ifdef HAVE_OPENGL
		// Default GL Engine ( only used if no engine is defined )
		class DefaultGLEngine : public Engine
        {
		protected:
			//will be initialized in init
			//might be better in a constructor actually...
			RGBSurface * _logo;
			unsigned int _logotexture;
			

			public:

				DefaultGLEngine();
				~DefaultGLEngine();

			//this is run just before the render
			virtual void prerender(unsigned long deltaticks);

			//this render function should not modify the engine
            virtual void render(VideoSurface & screen) const;

			//to initialise the engine, just called once before any render
            virtual bool init(int width, int height);

			//call everytime the display is resized
            virtual bool resize(int width, int height);
		};
#endif //HAVE_OPENGL


    }
}




#endif //SDL_ENGINE_HH
