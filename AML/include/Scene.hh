#ifndef AML_SCENE_HH
#define AML_SCENE_HH

#include "Config.hh"
#include "Sprite.hh"
#include <list>

namespace RAGE
{
    namespace AML
    {
        //manages layers and the blits
        class Scene : public SDL::Engine
        {
            friend class Window;

        protected:

            std::list<Sprite *> _spritelist;

            Scene();
            virtual ~Scene();


        public:

            void put( Sprite* sprite);
            void remove( Sprite* sprite);
            bool init (int width, int height);
            bool resize (int width, int height);

            bool render() const ;//call render on all the sprites

        };



    }

}

#endif
