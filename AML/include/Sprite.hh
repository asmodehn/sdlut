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
            SDL::Rect _ori;
            SDL::Point _pos;


        public :
        Sprite(const Image & img) throw (std::logic_error);
            Sprite(const Image &, std::string ID ) throw (std::logic_error);
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
                _pos.setx((x >minX ? x: minX)< maxX ? x : maxX);
                _pos.sety((y > minY ? y : minY)< maxY ? y : maxY);
            }
            SDL::Point getPos()
            {
                return _pos;
            }

//            void move (int x, int y)
//            {
//
//            }

        };
    }
}

#endif

