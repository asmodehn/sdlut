#ifndef SDL_GLMANAGER_HH
#define SDL_GLMANAGER_HH

/**
 * \class SDLGLManager
 *
 * \ingroup Video
 *
 * \brief This class is an SDL - OpenGL Manager
 *
 * This class implements all the opengl related functions that SDL provides
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "Logger.hh"
#include <string>

namespace RAGE
{
namespace SDL
{


/*******************************************************************************
 * Manager of the GL state machine
 ******************************************************************************/

//Howto use glSDL( planned in SDL from SDL 1.3) : http://icps.u-strasbg.fr/~marchesin/sdl/glsdl.html
//GOOD STUFF TO ADD AT http://steinsoft.net


/***************************************************************
 * OpenGL / vs / SDL  => a strategy                            *
 *                                                             *
 * Compiled w/o OpenGL : only SDL classes compiled.            *
 * -> No OpenGL option available at all                        *
 *                                                             *
 * Compiled w/ OpenGL : SDL + GL classes compiled.             *
 * -> GL classes used. Can revert back to original SDL         *
 * behavior as GLclass derivate from SDLclass                  *
 * if opengl not chosen -> revert back to original SDL         *
 *                                                             *
 * dynload : if opengl not available ( no dll, etc. )          *
 * -> revert back                                              *
 *                                                             *
 * Pb : One central option manager, accessible by all to       *
 * say which renderer is used. => Manager -> TODO...           *
 ***************************************************************
 */





//This may be useless in Windows....
//TEst to do on linux, to choose a class behaviour
class GLManager
{
    int dummy; // just to remove empty class warning

    friend class ScreenBuffer;

    GLManager() {}

public :

    ~GLManager() {}

    //may be connected with constructor ???
    bool loadGLLibrary(const std::string & path);

    //TODO : I don't know how to manage this....
    //getProcAddress



    //Accessor to GLAttributes
    //Note : DoubleBuf is managed by GLWindow, like 2D doublebuf
    //TODO -> error managed by exceptions ???
    //TODO -> different behavior depending if GLWindow is already set or not ? ( refer SDLManager... )

    // Q? : if GLWindow not set, can we access the GL data ??
    // ANSWER : on windows (wingdi driver) everything is == 0 when GLWindow not set
    // On Windows , after setvideo, the values are : { 8,8,8,8,32,24,8,0,0,0,0 } should be set by default...
    // or maybe 0 before means default after set video...
    int getRSize(void) const ;
    int getGSize(void) const ;
    int getBSize(void) const ;
    int getASize(void) const ;
    int getBufferSize(void) const ;
    int getDepthSize(void) const ;
    int getStencilSize(void) const ;
    int getAccumRSize(void) const ;
    int getAccumGSize(void) const ;
    int getAccumBSize(void) const ;
    int getAccumASize(void) const ;

    //TODO : if the video is already set, a change here should result in VIDEO RE-SET, via SDLSurfaceFactory
    //beware of the Surface Factory behavior about this for other things like doublebuf, we have to do it the same way...
    //On windows ( wingdi) all set functions returns true, but it seems they have no effects on the result after setVideoMode...
    //Tests to do on linux...
    bool setRSize(int bits);
    bool setGSize(int bits);
    bool setBSize(int bits);
    bool setASize(int bits);
    bool setBufferSize(int bits);
    bool setDepthSize(int bits);
    bool setStencilSize(int bits);
    bool setAccumRSize(int bits);
    bool setAccumGSize(int bits);
    bool setAccumBSize(int bits);
    bool setAccumASize(int bits);

    friend Logger & operator << (Logger & ostr, const GLManager & glman);
};

}
} // namespace RAGE::SDL

#endif
