#include "Video/SDLGLManager.hh"
#include "SDLConfig.hh"

namespace RAGE
{
namespace SDL
{

#ifdef WK_OPENGL_FOUND

//may be connected with constructor ???
bool GLManager::loadGLLibrary(const std::string & path)
{
    return SDL_GL_LoadLibrary(path.c_str()) == 0;
}

int GLManager::getRSize(void) const
{
    int res;
    SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &res);
    return res;
}

int GLManager::getGSize(void) const
{
    int res;
    SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &res);
    return res;
}

int GLManager::getBSize(void) const
{
    int res;
    SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &res);
    return res;
}

int GLManager::getASize(void) const
{
    int res;
    SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &res);
    return res;
}

int GLManager::getBufferSize(void) const
{
    int res;
    SDL_GL_GetAttribute(SDL_GL_BUFFER_SIZE, &res);
    return res;
}

int GLManager::getDepthSize(void) const
{
    int res;
    SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &res);
    return res;
}

int GLManager::getStencilSize(void) const
{
    int res;
    SDL_GL_GetAttribute(SDL_GL_STENCIL_SIZE, &res);
    return res;
}

int GLManager::getAccumRSize(void) const
{
    int res;
    SDL_GL_GetAttribute(SDL_GL_ACCUM_RED_SIZE, &res);
    return res;
}

int GLManager::getAccumGSize(void) const
{
    int res;
    SDL_GL_GetAttribute(SDL_GL_ACCUM_GREEN_SIZE, &res);
    return res;
}

int GLManager::getAccumBSize(void) const
{
    int res;
    SDL_GL_GetAttribute(SDL_GL_ACCUM_BLUE_SIZE, &res);
    return res;
}

int GLManager::getAccumASize(void) const
{
    int res;
    SDL_GL_GetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, &res);
    return res;
}

bool GLManager::setRSize(int bits)
{
    return SDL_GL_SetAttribute(SDL_GL_RED_SIZE, bits) == 0;
}

bool GLManager::setGSize(int bits)
{
    return SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, bits) == 0;
}

bool GLManager::setBSize(int bits)
{
    return SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, bits) == 0;
}

bool GLManager::setASize(int bits)
{
    return SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, bits) == 0;
}

bool GLManager::setBufferSize(int bits)
{
    return SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, bits) == 0;
}

bool GLManager::setDepthSize(int bits)
{
    return SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, bits) == 0;
}

bool GLManager::setStencilSize(int bits)
{
    return SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, bits) == 0;
}

bool GLManager::setAccumRSize(int bits)
{
    return SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, bits) == 0;
}

bool GLManager::setAccumGSize(int bits)
{
    return SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, bits) == 0;
}

bool GLManager::setAccumBSize(int bits)
{
    return SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, bits) == 0;
}

bool GLManager::setAccumASize(int bits)
{
    return SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, bits) == 0;
}

Logger & operator << (Logger & log, const GLManager & glman)
{
    log << nl << "GLManager : " << nl <<
    "GL Red Size = " << glman.getRSize() << nl <<
    "GL Green Size = " << glman.getGSize() << nl <<
    "GL Blue Size = " << glman.getBSize() << nl <<
    "GL Alpha Size = " << glman.getASize() << nl <<
    "GL Buffer Size = " << glman.getBufferSize() << nl <<
    "GL Depth Size = " << glman.getDepthSize() << nl <<
    "GL Stencil Size = " << glman.getStencilSize() << nl <<
    "GL Accum Red Size = " << glman.getAccumRSize() << nl <<
    "GL Accum Green Size = " << glman.getAccumGSize() << nl <<
    "GL Accum Blue Size = " << glman.getAccumBSize() << nl <<
    "GL Accum Alpha Size = " << glman.getAccumASize() ;
    return log;
}
#else
#pragma message if no OpenGL, methods should be implemented
#endif
}
}
