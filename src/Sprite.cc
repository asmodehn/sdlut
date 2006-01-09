#include "Sprite.hh"

namespace AML {

SDL::VideoSurface * Sprite::_display = NULL ;

void Sprite::render()
{
    assert(_display);
    _display->blit(_surf,SDL::Point(posX,posY));
}


}
