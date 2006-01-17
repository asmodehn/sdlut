#ifndef AML_SPRITE_HH
#define AML_SPRITE_HH

#include "Config.hh"
#include <string>

namespace RAGE
{
    namespace AML
    {
        class Sprite
        {
            friend class Scene;

            SDL::RGBSurface _surf;
            int posX, posY;


        public :
            Sprite(std::string filename);

#ifndef HAVE_OPENGL

            bool render(SDL::VideoSurface * screen);
#else

            bool render();
#endif

            void setPos( int x, int y)
            {
                posX=x;
                posY=y;
            }
            int getPosX()
            {
                return posX;
            }
            int getPosY()
            {
                return posY;
            }

        };
    }
}

#endif

