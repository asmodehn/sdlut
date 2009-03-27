#ifndef SDL_GLSURFACE_HH
#define SDL_GLSURFACE_HH

/*******************************************************************************
 * Handle a Graphical GL Surface
 ******************************************************************************/

#include "Video/SDLRGBSurface.hh"

namespace RAGE
{
    namespace SDL {

class GLSurface : public RGBSurface
{

	friend class VideoGLSurface;

	friend class SurfaceLoader;

	///Conversion Constructor
    	explicit GLSurface(SDL_Surface * s); ///< This one should be called only by friends

	///Conversion Constructor with explicit ownership transfert
    	explicit GLSurface(std::auto_ptr<SDL_Surface> s);

	void computeGLWidthHeight();
	void convertPixels();

protected:

	unsigned int textureHandle;
	int textureWidth;
	int textureHeight;
	unsigned int * texturePixels;

	unsigned int getTextureHandle();

public : 

	virtual ~GLSurface();

	int getTextureWidth();

	int getTextureHeight();

	bool convertToDisplayFormat();

    friend Logger & operator << (Logger & ostr, const RGBSurface & surf);

};
    }
} //namespace RAGE::SDL

#endif
