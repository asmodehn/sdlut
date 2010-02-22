#include "Video/ImageLoader.hh"
#include "SDLConfig.hh"

namespace RAGE
{
namespace SDL
{

ImageLoader::ImageLoader()
try :
    surfloader()
{

}
catch (std::exception &e)
{
    Log << nl << "Exception in ImageLoader Constructor !"  << nl <<
    e.what() << nl << GetError() << std::endl;
    //TODO : much more explicit error message...
}

ImageLoader::ImageLoader( const ImageLoader& sl)
try :
    surfloader(sl.surfloader)
{

}
catch (std::exception &e)
{
    Log << nl << "Exception in ImageLoader Copy Constructor !"  << nl <<
    e.what() << nl << GetError() << std::endl;
    //TODO : much more explicit error message...
}

ImageLoader::~ImageLoader()
{
}

void ImageLoader::resetFlags(	bool SWSURFACE,
                              bool HWSURFACE,
                              bool SRCCOLORKEY,
                              bool SRCALPHA )
{
    surfloader.resetFlags( SWSURFACE, HWSURFACE, SRCCOLORKEY, SRCALPHA);
}

void ImageLoader::resetOpengl(bool ogl )
{
    surfloader.resetOpengl(ogl);
}

//creates surface from file, copying its content...
std::auto_ptr<Image> ImageLoader::load(std::string filename , bool no_failure ) throw (std::logic_error)
{
    std::auto_ptr<Image> img(new Image(surfloader.load(filename, no_failure)));
    return img;
}


std::auto_ptr<Image> ImageLoader::load(std::string filename, const Color & colorKey, bool no_failure ) throw ( std::logic_error)
{
    std::auto_ptr<Image> img(new Image(surfloader.load(filename, colorKey, no_failure)));
    return img;

}

//creates a surface from a RWOps containing a image.
std::auto_ptr<Image> ImageLoader::load(RWOps & rwops) throw(std::logic_error) //TODO : add optional format
{
    std::auto_ptr<Image> img(new Image(surfloader.load(rwops)));
    return img;
}

//convert creates a new RGBSurface
std::auto_ptr<Image> ImageLoader::copyconvert(const RGBSurface & s, const PixelFormat & pfmt, bool no_failure ) throw (std::logic_error)
{
    std::auto_ptr<Image> img ( new Image(surfloader.copyconvert(s, pfmt, no_failure)));
    return img;
}


} //SDL

} // RAGE

