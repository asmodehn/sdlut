#include "Sprite.hh"

namespace RAGE
{
namespace AML {

#ifndef HAVE_OPENGL
bool Sprite::render(SDL::VideoSurface * screen)
{
    Log <<  nl << "Sprite::render()" << std::endl;
    assert(screen);
    return screen->blit(_surf,SDL::Point(posX,posY));
}
#else
    bool Sprite::render()
    {

    }
#endif

}
}

