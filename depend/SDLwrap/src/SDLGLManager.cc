#include "SDLGLManager.hh"

SDLGLManager* SDLGLManager::_uniqueInstance = NULL;

int SDLGLManager::getRSize(void) const
{
	int res;
	SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &res);
	return res;
}

int SDLGLManager::getGSize(void) const
{
	int res;
	SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &res);
	return res;
}

int SDLGLManager::getBSize(void) const
{
	int res;
	SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &res);
	return res;
}

int SDLGLManager::getASize(void) const
{
	int res;
	SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &res);
	return res;
}

int SDLGLManager::getBufferSize(void) const
{
	int res;
	SDL_GL_GetAttribute(SDL_GL_BUFFER_SIZE, &res);
	return res;
}

int SDLGLManager::getDepthSize(void) const
{
	int res;
	SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &res);
	return res;
}

int SDLGLManager::getStencilSize(void) const
{
	int res;
	SDL_GL_GetAttribute(SDL_GL_STENCIL_SIZE, &res);
	return res;
}

int SDLGLManager::getAccumRSize(void) const
{
	int res;
	SDL_GL_GetAttribute(SDL_GL_ACCUM_RED_SIZE, &res);
	return res;
}

int SDLGLManager::getAccumGSize(void) const
{
	int res;
	SDL_GL_GetAttribute(SDL_GL_ACCUM_GREEN_SIZE, &res);
	return res;
}

int SDLGLManager::getAccumBSize(void) const
{
	int res;
	SDL_GL_GetAttribute(SDL_GL_ACCUM_BLUE_SIZE, &res);
	return res;
}

int SDLGLManager::getAccumASize(void) const
{
	int res;
	SDL_GL_GetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, &res);
	return res;
}
	
bool SDLGLManager::setRSize(int bits)
{
	return SDL_GL_SetAttribute(SDL_GL_RED_SIZE, bits) == 0;
}	

bool SDLGLManager::setGSize(int bits)
{
	return SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, bits) == 0;
}	

bool SDLGLManager::setBSize(int bits)
{
	return SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, bits) == 0;
}

bool SDLGLManager::setASize(int bits)
{
	return SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, bits) == 0;
}

bool SDLGLManager::setBufferSize(int bits)
{
	return SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, bits) == 0;
}

bool SDLGLManager::setDepthSize(int bits)
{
	return SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, bits) == 0;
}

bool SDLGLManager::setStencilSize(int bits)
{
	return SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, bits) == 0;
}

bool SDLGLManager::setAccumRSize(int bits)
{
	return SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, bits) == 0;
}

bool SDLGLManager::setAccumGSize(int bits)
{
	return SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, bits) == 0;
}

bool SDLGLManager::setAccumBSize(int bits)
{
	return SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, bits) == 0;
}

bool SDLGLManager::setAccumASize(int bits)
{
	return SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, bits) == 0;
}
	
void SDLGLManager::debug(void) const
{
	std::cout << "SDLGLManager - debug() : \n" <<
    	"GL Red Size = " << getRSize() << "\n" <<
		"GL Green Size = " << getGSize() << "\n" <<
		"GL Blue Size = " << getBSize() << "\n" <<
		"GL Alpha Size = " << getASize() << "\n" <<
		"GL Buffer Size = " << getBufferSize() << "\n" <<
		"GL Depth Size = " << getDepthSize() << "\n" <<
		"GL Stencil Size = " << getStencilSize() << "\n" <<
		"GL Accum Red Size = " << getAccumRSize() << "\n" <<
		"GL Accum Green Size = " << getAccumGSize() << "\n" <<
		"GL Accum Blue Size = " << getAccumBSize() << "\n" <<
		"GL Accum Alpha Size = " << getAccumASize() <<
	std::endl;
}
