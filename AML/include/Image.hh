#ifndef IMAGE_HH
#define IMAGE_HH

#include "Config.hh"

using namespace RAGE;
using namespace RAGE::AML;

class Image
{
    SDL::RGBSurface _surf;
    public:
        Image(std::string filename);
        Image(std::string filename, SDL::Color c);

        void setColorKey(SDL::Color c);


        bool display(SDL::VideoSurface * screen, SDL::Point pos) const ;
    protected:
    private:
};

#endif // IMAGE_HH
