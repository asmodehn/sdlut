#include "Image.hh"

Image::Image(std::string filename)
: _surf(filename)
{
    //ctor
}

Image::Image(std::string filename, SDL::Color c)
: _surf(filename,c)
{
    //ctor
}

void Image::setColorKey(SDL::Color c)
{
    _surf.setColorKey(c);
}

bool Image::display(SDL::VideoSurface * screen, SDL::Point pos) const
{
    return screen->blit(_surf,pos);
}


