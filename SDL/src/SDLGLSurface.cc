#include "SDLGLSurface.hh"


namespace RAGE
{
    namespace SDL
    {

#ifdef HAVE_OPENGL

        GLSurface::GLSurface(int width, int height, int bpp, GLManager * const glmanager) throw (std::logic_error)
        try
        :
            VideoSurface(width, height, bpp), _glmanager(glmanager)
        {
#ifdef DEBUG
            Log << nl << "GLSurface::GLSurface() called ...";
#endif

            glClearColor(static_cast<float> (_background.getR() ) / 255.0f, static_cast<float> (_background.getG() ) / 255.0f,static_cast<float> (_background.getB() ) / 255.0f, 0.0f);    // Black Background

#ifdef DEBUG

            Log << nl << "GLSurface::GLSurface() done.";
#endif

        }
        catch (std::exception &e)
        {
            Log << nl << "GLSurface:: Exception in Constructor !" << nl << e.what() << std::endl;
        };

        bool GLSurface::update(void)
        {
#if (DEBUG == 2)
            Log << nl << "GLSurface::update() called...";
#endif

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            if (_engine !=NULL)
			{
                _engine->render();
            }
            //if we got also blit //DEPRECATED
            //SDLDisplay::update();

            SDL_GL_SwapBuffers();


#if (DEBUG == 2)

            Log << nl << "GLSurface::update() done.";
#endif

            return true;
        }




        bool GLSurface::resize (int width, int height)
        {
			bool res = false;
            //some weird OpenGL stuff happen if we dont do it from here... no idea why...
            if (_engine == NULL)
			{	            glViewport(0,0,width,height);      // Reset The Current Viewport
							glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			res = true;
			}
			else
			{
				res = _engine->resize(width,height);
			}
			return res;
        }


        bool GLSurface::setBGColor(const Color & color)
        {
#ifdef DEBUG
            Log << nl << "GLSurface::setBGColor(" << color << ") called ...";
#endif

            bool res = false;

            _background=color;
            glClearColor(static_cast<float> (color.getR() ) / 255.0f, static_cast<float> (color.getG() ) / 255.0f,static_cast<float> (color.getB() ) / 255.0f,0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#ifdef DEBUG

            Log << nl << "GLSurface::setBGColor(" << color << ") done.";
#endif

            return res;

        }


#endif

    }
} //namespace RAGE::SDL
