#ifndef ImageLoader_HH
#define ImageLoader_HH

/*******************************************************************************
 * Loads an Image from a file
 ******************************************************************************/

#include "Video/Image.hh"

#include "Video/Loader.hh"

namespace RAGE
{
namespace SDL
{

class ImageLoader
{

    SurfaceLoader surfloader;

public:

    ImageLoader();
    ImageLoader( const ImageLoader & il )
    ~ImageLoader();


    void resetFlags(bool SWSURFACE = true, bool HWSURFACE = false, bool SRCCOLORKEY = false, bool SRCALPHA = false);
    void resetOpengl(bool ogl = false );//TODO : handle case without opengl...

    //creates surface from file, copying its content...
    //if an error happens, an exception is thrown.
    //However if silent_fail == true, then a error surface is loaded instead.
    //Therefore the auto_ptr<Image> is assumed to be properly set if no exception is thrown.
    std::auto_ptr<Image> load(std::string filename, bool no_failure = false ) throw (std::logic_error);
    std::auto_ptr<Image> load(std::string filename, const RGBAColor & colorKey, bool no_failure = false ) throw (std::logic_error);

    //creates a surface from a RWOps containing a image.
    std::auto_ptr<Image> load(RWOps & rwops) throw (std::logic_error); //TODO : add optional format

    //To create new surface, using standard RGBFlags and masks...
    std::auto_ptr<Image> create( void * pixeldata, int depth, int pitch, int width, int height, bool no_failure = false )throw (std::logic_error);
    std::auto_ptr<Image> create( const RGBAColor & color, int width , int height, int bpp, bool no_failure = false )throw (std::logic_error);
    std::auto_ptr<Image> create(int width, int height, int bpp, bool no_failure = false )throw (std::logic_error);

    //convert creates a new RGBSurface
    std::auto_ptr<Ìmage> copyconvert(const RGBSurface &, const PixelFormat & pfmt, bool no_failure = false )throw (std::logic_error);



};

} //SDL

}// RAGE

#endif //ImageLoader_HH
