#ifndef SDL_SURFACELOADER_HH
#define SDL_SURFACELOADER_HH

/*******************************************************************************
 * Handle a Image File Loader to a Surface
 ******************************************************************************/

#include "Video/SDLRGBSurface.hh"
#include "Video/SDLGLSurface.hh"

namespace RAGE
{
namespace SDL
{

class SurfaceLoader
{

    bool opengl;

    unsigned long RGBFlags;
    // resource used in case of error during loading...
    // because we know it works...
    RWOps errorContent;
    int offset;//usefull to debug RWOps

public:
    void resetFlags(bool SWSURFACE = true, bool HWSURFACE = false, bool SRCCOLORKEY = false, bool SRCALPHA = false);
    void resetOpengl(bool ogl = false );//TODO : handle case without opengl...

    SurfaceLoader();
    SurfaceLoader( const SurfaceLoader& );
    ~SurfaceLoader();

    //creates surface from file, copying its content...
    //if an error happens, an exception is thrown.
    //However if silent_fail == true, then a error surface is loaded instead.
    //Therefore the auto_ptr<RGBSurface> is assumed to be properly set if no exception is thrown.
    std::auto_ptr<RGBSurface> load(std::string filename, bool no_failure = false ) throw (std::logic_error);
    std::auto_ptr<RGBSurface> load(std::string filename, const RGBAColor & colorKey, bool no_failure = false ) throw (std::logic_error);

    //creates a surface from a RWOps containing a image.
    std::auto_ptr<RGBSurface> load(RWOps & rwops) throw (std::logic_error); //TODO : add optional format

    //To create new surface, using standard RGBFlags and masks...
    std::auto_ptr<RGBSurface> create( void * pixeldata, int depth, int pitch, int width, int height, bool no_failure = false )throw (std::logic_error);
    std::auto_ptr<RGBSurface> create( const RGBAColor & color, int width , int height, int bpp, bool no_failure = false )throw (std::logic_error);
    std::auto_ptr<RGBSurface> create(int width, int height, int bpp, bool no_failure = false )throw (std::logic_error);

    //convert creates a new RGBSurface
    std::auto_ptr<RGBSurface> copyconvert(const RGBSurface &, const PixelFormat & pfmt, bool no_failure = false )throw (std::logic_error);


};

} //SDL

} // RAGE

#endif
