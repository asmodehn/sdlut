#ifndef SDL_ENGINE_HH
#define SDL_ENGINE_HH

/*******************************************************************************
 * Interface with other systems
 ******************************************************************************/

#include "SDLConfig.hh"
#include "SDLColor.hh"
#include "SDLRGBSurface.hh"

namespace RAGE
{
    namespace SDL
    {



        class VideoSurface; //further reference to access the display surface to be able to blit on it

        //2D Engine interface
        class Engine
        {
                friend class Window;
        protected:
            VideoSurface * _screen; // to access the display for blit purpose

		public:
            virtual bool render(void) const = 0;
            virtual bool init(int width, int height) = 0;
            virtual bool resize(int width, int height) = 0;
        };

    }
}

#endif //SDL_ENGINE_HH
