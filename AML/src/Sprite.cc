#include "Sprite.hh"

namespace RAGE
{
    namespace AML
    {

        Sprite::Sprite(const Image & img) throw (std::logic_error)
        try
:
            _img (img),
            posX(0),
            posY(0)
        {
#ifdef DEBUG
            Log << nl << "Sprite::Sprite() called ...";
#endif


#ifdef DEBUG

            Log << nl << "Sprite::Sprite() done.";
#endif

        }
        catch (std::exception & e)
        {
            Log << nl << "Exception in Sprite constructor ! " << nl << e.what ();
        }

        Sprite::Sprite(const Sprite &s)
                : _img (s._img), posX( s.posX), posY(s.posY)
        {
            Log << nl << "Sprite Copy !!!";
        }

        Sprite& Sprite::operator=(const Sprite &s)
        {
            Log << nl << "Sprite Assign !!!";
            if (this != &s)
            {
//               _img = s._img;
                posX= s.posX;
                posY= s.posY;
            }
            return *this;
        }

        bool Sprite::operator == (const Sprite & s)
        {
            return posX == s.posX && posY == s.posY ;//&& _img == s._img;
        }

#ifndef HAVE_OPENGL
        bool Sprite::render(SDL::VideoSurface * screen) const
        {
#if (DEBUG == 2)
            Log <<  nl << "Sprite::render("<< screen<<") called ..." << std::endl;
            assert(screen);
#endif

            bool res = false;

            SDL::Point p(posX,posY);
#if (DEBUG == 2)

            Log << nl << "blitting at " << p;
#endif

            res =_img.display(screen, p);
#if (DEBUG == 2)

            Log <<  nl << "Sprite::render("<< screen<<") done." << std::endl;
            assert(screen);
#endif

            return res;
        }
#else
        bool Sprite::render() const
            {}
#endif

    }
}

