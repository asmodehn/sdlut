#ifndef SDL_ENGINE_HH
#define SDL_ENGINE_HH

/*******************************************************************************
 * Interface with other systems
 ******************************************************************************/

#include "SDLConfig.hh"
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
			virtual bool prerender(void) = 0;

			//this render function should not modify the engine
            virtual bool render(VideoSurface* screen) const = 0;

			//this is run just after the render, and refresh of the screen
			virtual bool postrender(void) = 0;

			//to initialise the engine, just called once before any render
            virtual bool init(int width, int height) = 0;

			//call everytime the display is resized
            virtual bool resize(int width, int height) = 0;
        };

		// Default 2D Engine ( only used if no engine is defined )
		class DefaultEngine : public Engine
        {
			public:
			//this is run just before the render
			virtual bool prerender(void);

			//this render function should not modify the engine
            virtual bool render(VideoSurface* screen) const;

			//this is run just after the render, and refresh of the screen
			virtual bool postrender(void);

			//to initialise the engine, just called once before any render
            virtual bool init(int width, int height);

			//call everytime the display is resized
            virtual bool resize(int width, int height);
		};

#ifdef HAVE_OPENGL
		// Default GL Engine ( only used if no engine is defined )
		class DefaultGLEngine : public Engine
        {
			public:
			//this is run just before the render
			virtual bool prerender(void);

			//this render function should not modify the engine
            virtual bool render(VideoSurface* screen) const;

			//this is run just after the render, and refresh of the screen
			virtual bool postrender(void);

			//to initialise the engine, just called once before any render
            virtual bool init(int width, int height);

			//call everytime the display is resized
            virtual bool resize(int width, int height);
		};
#endif //HAVE_OPENGL


    }
}




#endif //SDL_ENGINE_HH
