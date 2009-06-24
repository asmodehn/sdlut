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

	friend class FontExtend;

	///Conversion Constructor
    	explicit GLSurface(SDL_Surface * s) throw (std::logic_error); ///< This one should be called only by friends

	///Conversion Constructor with explicit ownership transfert
    	explicit GLSurface(std::auto_ptr<SDL_Surface> s) throw (std::logic_error);

	void computeGLWidthHeight();
	void convertPixels();

protected:

	//to mark the texture as modified, if texture update needed before using it
	bool modified;

	unsigned int textureHandle;
	int textureWidth;
	int textureHeight;
	unsigned int * texturePixels;

	unsigned int getTextureHandle();

public : 

	//Constructor
	//BPP should NEVER be == 0 !!!!
	GLSurface( int width, int height, int bpp,
				bool alpha = false,
				bool colorkey = false,
				bool hardware = false,
				unsigned long r_mask = r_default_mask,
				unsigned long g_mask = g_default_mask,
				unsigned long b_mask = b_default_mask,
				unsigned long a_mask = a_default_mask
				) throw (std::logic_error);

	GLSurface( void * pixeldata, int depth, int pitch, int width, int height,
				unsigned long r_mask = r_default_mask,
				unsigned long g_mask = g_default_mask,
				unsigned long b_mask = b_default_mask,
				unsigned long a_mask = a_default_mask
				) throw (std::logic_error);

	virtual ~GLSurface();

	int getTextureWidth();

	int getTextureHeight();

	bool convertToDisplayFormat();

    bool fill (const PixelColor& color, Rect dest_rect);

	bool blit (const RGBSurface& src, Rect& dest_rect, const Rect& src_rect);

    friend Logger & operator << (Logger & ostr, const RGBSurface & surf);

};
    }
} //namespace RAGE::SDL

#endif
