#include "SDLGLSurface.hh"


namespace SDL {

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

GLSurface::GLSurface(int width, int height, int bpp, GLManager * const glmanager) throw (std::logic_error)
try	: VideoSurface(width, height, bpp, _defaultflags), _glmanager(glmanager)
{
    assert (_glmanager);
    if (_glmanager->getEngine() != NULL)
        _glmanager->getEngine()->init(getWidth(),getHeight());
    else
        throw std::logic_error("Engine not initialized --> aborting GLWindow Constructor!");
}
catch (std::exception &e)
{
    Log << nl << "Exception catched in GLWindow constructor !" << nl << e.what() << std::endl;
};

bool GLSurface::update(void)
{
    assert(_glmanager);
	assert(_glmanager->getEngine());
	_glmanager->getEngine()->render();
	//si on a du blit //DEPRECATED
	//SDLDisplay::update();

	SDL_GL_SwapBuffers();
	return true;
}

bool GLSurface::resize (int width, int height)
{

    assert(_glmanager);
	assert(_glmanager->getEngine());
	return _glmanager->getEngine()->resize(width,height);
}


    void GLSurface::setBGColor(const Color & color)
    {
            _background = color;
             assert(_glmanager);
         	assert(_glmanager->getEngine());
         	_glmanager->getEngine()->setBGColor(static_cast<float> (color.getR() ) / 255.0f, static_cast<float> (color.getG() ) / 255.0f,static_cast<float> (color.getB() ) / 255.0f);
    }
    //might be improved and secured later...
    Color GLSurface::getBGColor ()
    {
          return _background;
    }

#endif

} //namespace SDL
