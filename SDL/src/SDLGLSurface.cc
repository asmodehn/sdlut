#include "SDLGLSurface.hh"


namespace RAGE
{
    namespace SDL
    {

#ifdef HAVE_OPENGL

        /*
        void GLSurface::enableBlit(void)
        {
         _flags=_flags | SDL_OPENGLBLIT;
         if (initialized) setup();
        }

        void GLSurface::disableBlit(void)
        {
         _flags=_flags & !SDL_OPENGLBLIT;
         if (initialized) setup();
        }

        //Only valid with HWSurface
        void GLSurface::enableDoubleBuf(void)
        {
         _newFlags=_newFlags | SDL_DOUBLEBUF;
        }
        void GLSurface::disableDoubleBuf(void)
        {
         _newFlags=_newFlags & !SDL_DOUBLEBUF;
        }

        */

        GLSurface::GLSurface(int width, int height, int bpp, GLManager * const glmanager, GLEngine * glengine ) throw (std::logic_error)
        try
:
            VideoSurface(width, height, bpp,glengine), _glmanager(glmanager)//, _engine(glengine)
        {
#ifdef DEBUG
            Log << nl << "GLSurface::GLSurface() called ...";
#endif

            if (_engine != NULL)
                _engine->init(getWidth(),getHeight());
            else
                throw std::logic_error("GLSurface:: Engine pointer missing properly --> aborting GLWindow Constructor!");

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
            assert(_engine);
            _engine->render();
            //if we got also blit //DEPRECATED
            //SDLDisplay::update();

            SDL_GL_SwapBuffers();
            return true;
        }

//        bool GLSurface::resize (int width, int height)
//        {
//            //some weird OpenGL stuff happen if we dont do it from here... no idea why...
//            assert(_engine);
//            return _engine->resize(width,height);
//        }

        //
        //    bool GLSurface::setBGColor(const Color & color)
        //    {
        //        assert(_engine);
        //        return _engine->setBGColor(color);
        //    }
        //
        //
        //    bool GLSurface::saveContent(void)
        //    {
        //        assert(_engine);
        //        return _engine->saveContent();
        //    }
        //
        //    bool GLSurface::restoreContent(void)
        //    {
        //        assert(_engine);
        //        return _engine->restoreContent();
        //    }

#endif

    }
} //namespace RAGE::SDL
