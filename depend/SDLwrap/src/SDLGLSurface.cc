#include "SDLGLSurface.hh"


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
        VideoSurface(width, height, bpp, _defaultflags), _glmanager(glmanager), _engine(glengine)
    {
        if (_engine != NULL)
            _engine->init(getWidth(),getHeight());
        else
            throw std::logic_error("Engine not initialized --> aborting GLWindow Constructor!");
    }
    catch (std::exception &e)
    {
        Log << nl << "Exception catched in GLWindow constructor !" << nl << e.what() << std::endl;
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

    bool GLSurface::resize (int width, int height)
    {

        assert(_engine);
        return _engine->resize(width,height);
    }


    bool GLSurface::setBGColor(const Color & color)
    {
        assert(_engine);
        return _engine->setBGColor(static_cast<float> (color.getR() ) / 255.0f, static_cast<float> (color.getG() ) / 255.0f,static_cast<float> (color.getB() ) / 255.0f);
    }


    bool GLSurface::saveContent(void)
    {
        assert(_engine);
        return _engine->saveContent();
    }

    bool GLSurface::restoreContent(void)
    {
        assert(_engine);
        return _engine->restoreContent();
    }

#endif

} //namespace SDL
