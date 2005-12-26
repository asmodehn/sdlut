#include "SDLGLWindow.hh"


namespace SDL {

#ifdef HAVE_OPENGL

/*
void SDLGLWindow::enableBlit(void)
{
	_flags=_flags | SDL_OPENGLBLIT;
	if (initialized) setup();
}

void SDLGLWindow::disableBlit(void)
{
	_flags=_flags & !SDL_OPENGLBLIT;
	if (initialized) setup();
}

//Only valid with HWSurface
void SDLWindow::enableDoubleBuf(void)
{
	_newFlags=_newFlags | SDL_DOUBLEBUF;
}
void SDLWindow::disableDoubleBuf(void)
{
	_newFlags=_newFlags & !SDL_DOUBLEBUF;
}

*/

GLWindow::GLWindow(int width, int height, int bpp, GLManager * const glmanager) throw (std::logic_error)
try	: DisplaySurface(width, height, bpp, flags), _glmanager(glmanager)
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
}

bool GLWindow::update(void)
{
    assert(_glmanager);
	assert(_glmanager->getEngine());
	_glmanager->getEngine()->render();
	//si on a du blit //DEPRECATED
	//SDLDisplay::update();

	SDL_GL_SwapBuffers();
	return true;
}

bool GLWindow::resize (int width, int height)
{

    assert(_glmanager);
	assert(_glmanager->getEngine());
	return _glmanager->getEngine()->resize(width,height);
}


    void GLWindow::setBGColor(const Color & color)
    {
            background = color;
             assert(_glmanager);
         	assert(_glmanager->getEngine());
         	_glmanager->getEngine()->setBGColor(static_cast<float> (color.getR() ) / 255.0f, static_cast<float> (color.getG() ) / 255.0f,static_cast<float> (color.getB() ) / 255.0f);
    }
    //might be improved and secured later...
    Color GLWindow::getBGColor ()
    {
          return background;
    }

#endif

} //namespace SDL
