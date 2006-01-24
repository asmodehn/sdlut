#ifndef SDL_GLSURFACE_HH
#define SDL_GLSURFACE_HH

/**
 * \class SDLGLSurface
 *
 * \ingroup Video
 *
 * \brief This class is an OpenGL Window
 *
 * This class implement in C++ the behaviour of SDLDdisplaySurface when the content is 3D (OpenGL).
 *
 * BUG : doesnt handle the resize correctly -> 0x0 access (maybe not from the code here...)
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "SDLConfig.hh"

#include "SDLVideoSurface.hh"
#include "SDLGLManager.hh"
#include "SDLEngine.hh"

namespace RAGE
{
    namespace SDL
    {

#ifdef HAVE_OPENGL

        class GLSurface : public VideoSurface
        {
        protected :

            GLManager * const _glmanager;

        public:

            //Constructor
            GLSurface(int width, int height, int bpp,GLManager * const glmanager) throw (std::logic_error);
            //Destructor
            ~GLSurface()
            {
            }

            bool resize (int width, int height);

            bool setBGColor(const Color & color);

            bool update(void);//call scene3D->render

        };

#endif // HAVE_OPENGL

    } //namespace RAGE::SDL
}
#endif //SDLGLSURFACE_HH
