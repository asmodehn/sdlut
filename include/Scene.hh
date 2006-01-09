#ifndef AML_SCENE_HH
#define AML_SCENE_HH

#include "Config.hh"
#include "Sprite.hh"

namespace AML
{
    class Scene //manages layers and the blits
    {
        friend class Window;

        protected:

        Sprite * _sprite;

        Scene();

        public:

        void put( Sprite sprite, int posX, int posY);

        void render();

    };
}

#endif
