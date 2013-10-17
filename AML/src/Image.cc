#include "Image.hh"

Image::Image(std::string filename)
        : _surf(filename)
{
    //_surf.optimise(); //FAIL for some reason in SDL...

}

Image::Image(std::string filename, SDL::Color c)
        : _surf(filename,c)
{
    //_surf.optimise(); //FAIL for some reason in SDL...
}

void Image::setColorKey(SDL::Color c)
{
    _surf.setColorKey(c);
}

bool Image::display(SDL::VideoSurface * screen,const SDL::Rect  & ori, const SDL::Point & pos) const
{
    return screen->blit(_surf,pos,ori);
}

void Image::setComponent(SDL::Rect subimg, std::string spriteID, int sequence, int frame)
{
    component.push_back(SubImage(subimg,spriteID, sequence, frame));
    //sort by name for faster access
}

const SDL::Rect & Image::getComponent(std::string spriteID, int sequence, int frame) const
{
    unsigned int i;
    for ( i=0; i< component.size();i++)
    {
        if ( component[i].spriteID ==spriteID  && component[i].sequence == sequence && component[i].frame == frame)
            break;
    }
    Log << nl << component[i].subimg;
    return component[i].subimg;
}

std::vector<const SDL::Rect *> Image::getComponent(std::string spriteID, int sequence) const
{
    std::vector<const SDL::Rect * > res;
    for ( unsigned int i=0; i< component.size();i++)
    {
        if ( component[i].spriteID ==spriteID  && component[i].sequence == sequence)
            res.push_back(&(component[i].subimg));
    }
    return res;
}

