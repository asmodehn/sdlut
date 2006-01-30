#ifndef IMAGE_HH
#define IMAGE_HH

#include "Config.hh"

using namespace RAGE;
using namespace RAGE::AML;

class Image
{
    SDL::RGBSurface _surf;

    class SubImage
    {
        public:
        SDL::Rect subimg;
        std::string spriteID;
        int sequence;
        int frame;

        SubImage (SDL::Rect si, std::string sID, int s, int f) : subimg(si), spriteID(sID), sequence(s), frame(f) {}

    };

    std::vector<SubImage> component;


    public:
        Image(std::string filename);
        Image(std::string filename, SDL::Color c);

        void setColorKey(SDL::Color c);

        bool display(SDL::VideoSurface * screen,const SDL::Rect  & ori, const SDL::Point & pos) const ;

        SDL::Rect getSize()const { return _surf.getSize(); }

        void setComponent(SDL::Rect subimg, std::string spriteID, int sequence, int frame);

        const SDL::Rect & getComponent(std::string spriteID, int sequence, int frame) const;
        std::vector<const SDL::Rect *> getComponent(std::string spriteID, int sequence = 0) const;




    protected:
    private:
};

#endif // IMAGE_HH
