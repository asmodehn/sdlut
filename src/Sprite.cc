#include "Sprite.hh"

namespace AML {

void render()
        {
            _display->blit(_sprite,SDL::Point(posX,posY));
        }


}