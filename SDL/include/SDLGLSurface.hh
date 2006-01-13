#ifndef SDL_GLSURFACE_HH
#define SDL_GLSURFACE_HH

/**
 * \class SDLGLSurface
 *
 * \ingroup Video
 *
 * \brief This class is an OpenGL Window
 *
 * This class implement in C++ the behaviour of SDLDdisplaySurface when the content is 3D (OpenGL).
 *
 * BUG : doesnt handle the resize correctly -> 0x0 access (maybe not from the code here...)
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "SDLConfig.hh"

#include "SDLVideoSurface.hh"
#include "SDLGLManager.hh"
#include "SDLEngine.hh"

namespace RAGE
{
    namespace SDL {

#ifdef HAVE_OPENGL

class GLSurface : public VideoSurface
{
protected :

    GLManager * const _glmanager;
    GLEngine* _engine;

public:

	//Constructor
	GLSurface(int width, int height, int bpp,GLManager * const glmanager, GLEngine * glengine = new GLEngine() ) throw (std::logic_error);
	//Destructor
	~GLSurface()  {if (_engine !=NULL ) delete _engine;}

    void setEngine(GLEngine * engine = new GLEngine()) {_engine = engine;}
    GLEngine * getEngine() { return _engine;}

//	inline bool isOpenGLset(void) const {return ((SDL_OPENGL & _surf->flags) != 0);}

  bool resize (int width, int height);


    bool setBGColor(const Color & color);

  //TODO : Save Screen -> backup the screen content in a new RGBSurface AND SAVE THE CURRENT SCENE STATE...
//Save Screen -> backup the screen content in a new RGBSurface...
	bool saveContent(void);
	//restore Screen -> blit the saved surface to the center of the display surface
	bool restoreContent(void);

	bool update(void);//call scene3D->render

	//TODO : overload Basesurface functions that cannot be used here, because there is NO OPENGL Blit
	//or overload using opengl textures ...


/*******************************************************************************
 * This is not recommended
 * Use it only for backward compatibility purpose
 //void enableBlit(void);
 //void disableBlit(void);
 //inline bool isBlitset(void) {return SDL_OPENGLBLIT & _flags;}
 //Usefull only if Blit is set
 //static void enableDoubleBuf(void);
 //static void disableDoubleBuf(void);
 //inline bool isDoubleBufset(void) const
 //{return SDL_DOUBLEBUF & screen()->getSurface()->flags;}
 ******************************************************************************/
};

#endif // HAVE_OPENGL

} //namespace RAGE::SDL
}
#endif //SDLGLSURFACE_HH
