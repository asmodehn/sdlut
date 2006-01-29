#ifndef AML_SPRITE_HH
#define AML_SPRITE_HH

#include "Config.hh"
#include "Image.hh"
#include <string>

namespace RAGE
{
    namespace AML
    {
        class Sprite
        {
            friend class Scene;
            static const int minX = 0;
            static const int minY = 0;
            static const int maxX = 640;
            static const int maxY = 480;

        protected:

            const Image & _img;
            int posX, posY;


        public :
            Sprite(const Image &) throw (std::logic_error);
            Sprite(const Sprite &);
            virtual ~Sprite()
            {}
            Sprite& operator=(const Sprite &);


            bool operator == (const Sprite & s);
            bool operator != (const Sprite & s)
            {
                return !(operator==(s));
            }

#ifndef HAVE_OPENGL

            virtual bool render(SDL::VideoSurface * screen)const;
#else

            virtual bool render()const;
#endif

            //absolute pixel position (at the moment)
            void setPos( int x, int y)
            {
                posX=(x >minX ? x: minX)< maxX ? x : maxX;
                posY=(y > minY ? y : minY)< maxY ? y : maxY;
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

