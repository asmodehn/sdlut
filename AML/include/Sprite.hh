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
            SDL::RGBSurface * _psurf;
            int posX, posY;


        public :
            Sprite(std::string filename) throw (std::logic_error);
            Sprite(const Sprite &);
            Sprite& operator=(const Sprite &);

#ifndef HAVE_OPENGL

            bool render(SDL::VideoSurface * screen)const;
#else

            bool render()const;
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

