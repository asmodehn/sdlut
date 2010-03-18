#ifndef ImageLoader_HH
#define ImageLoader_HH

/*******************************************************************************
 * Loads an Image from a file
 * GLSurface are created if compilation found OpenGL
 * otherwise RGBSurface are created.
 ******************************************************************************/

#include "Video/Image.hh"
//#include "Video/SDLSurfaceLoader.hh"

namespace SDLut
{
namespace video
{

class ImageLoader
{

    unsigned long pvm_RGBFlags;
    // resource used in case of error during loading...
    // because we know it works...
    system::RWOps pvm_errorContent;
    int pvm_offset;//usefull to debug RWOps


public:

    ImageLoader();
    ImageLoader( const ImageLoader & il );
    ~ImageLoader();

    void resetFlags(bool SWSURFACE = true, bool HWSURFACE = false, bool SRCCOLORKEY = false, bool SRCALPHA = false);

    //creates surface from file, copying its content...
    //if an error happens, an exception is thrown.
    //However if silent_fail == true, then a error surface is loaded instead.
    //Therefore the auto_ptr<Image> is assumed to be properly set if no exception is thrown.
    std::auto_ptr<Image> load(std::string filename, bool no_failure = false ) throw (std::logic_error);
    std::auto_ptr<Image> load(std::string filename, const Color & colorKey, bool no_failure = false ) throw (std::logic_error);

    //TODO : Implement those
    //To create new surface, using standard RGBFlags and masks...
    std::auto_ptr<Image> create( void * pixeldata, int depth, int pitch, int width, int height, bool no_failure = false )throw (std::logic_error);
    std::auto_ptr<Image> create( const Color & color, int width , int height, int bpp, bool no_failure = false )throw (std::logic_error);
    std::auto_ptr<Image> create(int width, int height, int bpp, bool no_failure = false )throw (std::logic_error);

    //convert creates a new RGBSurface
    std::auto_ptr<Image> copyconvert(const Image &, const internal::PixelFormat & pfmt, bool no_failure = false )throw (std::logic_error);

};

} //SDL

}// SDLut

#endif //ImageLoader_HH
