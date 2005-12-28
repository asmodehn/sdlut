#ifndef AML_SCENE_HH
#define AML_SCENE_HH


#include "Sprite.hh"

namespace AML
{
    class Scene //manages layers and the blits
    {
        friend class Window;

        protected:

        Sprite * _sprite;

        Scene()
        {
           Sprite::_display=App::getInstance().getAppWindow()->getDisplay();
        }

        public:

        put(const Sprite & sprite, int posX, int posY) { _sprite = *sprite; _sprite->setPos(posX,posY);}

        render() { _sprite->render();}

    };
}

#endif
