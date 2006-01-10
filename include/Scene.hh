#ifndef AML_SCENE_HH
#define AML_SCENE_HH

#include "Config.hh"
#include "Sprite.hh"

namespace AML
{
    //manages layers and the blits
    class Scene : public SDL::VideoSurface
    {
        friend class Window;

        protected:

        Sprite * _sprite;

        Scene();

        void render();

        public:

        void put( Sprite sprite, int posX, int posY);



        bool resize (int width, int height);

        //TODO : SAVE THE CURRENT SCENE STATE...
        bool saveContent(void) {return false;}
        bool restoreContent(void) {return true;}

        bool update(void);//call render


    };
}

#endif
