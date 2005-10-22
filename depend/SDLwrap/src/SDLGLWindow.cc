#include "SDLGLWindow.hh"

namespace SDL {

Interface3D* GLWindow::engine = new Interface3D;

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
bool GLWindow::update(void)
{
	assert(engine);
	engine->render();
	//si on a du blit
	//SDLDisplay::update();
	
	SDL_GL_SwapBuffers();
	return true;
}

bool GLWindow::resize (int width, int height)
{
	return engine->resize(width,height);
}

} //namespace SDL
