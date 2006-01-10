#ifndef AML_SCENE_HH
#define AML_SCENE_HH

#include "Config.hh"
#include "Sprite.hh"

namespace AML
{
    //manages layers and the blits
    class Scene : public SDL::Engine
    {
        friend class Window;

        protected:

        Sprite * _sprite;

        //inirialise the videosurface pointer in sprite for them to render themselves at their position
        Scene();

        public:

        void put( Sprite sprite, int posX = 0, int posY = 0);

        bool resize (int width, int height);

        //TODO : SAVE THE CURRENT SCENE STATE...
        bool saveContent(void) {return false;}
        bool restoreContent(void) {return false;}

        bool render();//call render on all the sprites


    };
}

#endif
