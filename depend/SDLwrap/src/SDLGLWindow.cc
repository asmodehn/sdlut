#include "SDLGLWindow.hh"

Interface3D* SDLGLWindow::engine = new Interface3D;

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
bool SDLGLWindow::update(void)
{
	assert(engine);
	engine->render();
	//si on a du blit
	//SDLDisplay::update();
	
	SDL_GL_SwapBuffers();
	return true;
}

bool SDLGLWindow::resize (int width, int height)
{
	return engine->resize(width,height);
}
