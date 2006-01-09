#ifndef AML_SPRITE_HH
#define AML_SPRITE_HH

#include "Config.hh"
#include <string>

namespace AML
{
    class Sprite
    {
        friend class Scene;

        static SDL::VideoSurface * _display;

        SDL::RGBSurface _surf;
        int posX, posY;


        public :
        Sprite(std::string filename) : _surf(filename),posX(0),posY(0)
        {}

        void render();



        void setPos( int x, int y) {posX=x;posY=y;}
        int getPosX() { return posX;}
        int getPosY() { return posY;}

    };
}

#endif

