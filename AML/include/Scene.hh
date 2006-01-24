#ifndef AML_SCENE_HH
#define AML_SCENE_HH

#include "Config.hh"
#include "Sprite.hh"

namespace RAGE
{
    namespace AML
    {
        //manages layers and the blits
        class Scene : public SDL::Engine
        {
            friend class Window;

        protected:

            Sprite * _sprite;

            Scene();
            ~Scene();


        public:

            void put( Sprite sprite, int posX = 0, int posY = 0);        //bool init(int width, int height, SDL::VideoSurface * display) {}
            bool init (int width, int height);
            bool resize (int width, int height);

            bool render() const ;//call render on all the sprites

        };



    }

}

#endif
