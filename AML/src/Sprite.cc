#include "Sprite.hh"

namespace RAGE
{
    namespace AML
    {

        Sprite::Sprite(std::string filename) throw (std::logic_error)
        try
:
            _psurf(new SDL::RGBSurface(filename)),
            posX(0),
            posY(0)
        {
#ifdef DEBUG
            Log << nl << "Sprite::Sprite("<<filename <<") called ...";
#endif


#ifdef DEBUG

            Log << nl << "Sprite::Sprite("<<filename <<") done.";
#endif

        }
        catch (std::exception & e)
        {
            Log << nl << "Exception in Sprite constructor ! " << nl << e.what ();
        }

        Sprite::Sprite(const Sprite &s)
                : _psurf(new SDL::RGBSurface(*s._psurf)), posX(0), posY(0)
        {
            Log << nl << "Sprite Copy !!!";
        }

        Sprite& Sprite::operator=(const Sprite &s)
        {
            Log << nl << "Sprite Assign !!!";
            if (this != &s)
            {
                delete _psurf;
                _psurf = new SDL::RGBSurface(*s._psurf);
                posX=0;
                posY=0;
            }
            return *this;
        }

        bool Sprite::operator == (const Sprite & s)
        {
            return posX == s.posX && posY == s.posY && _psurf == s._psurf;
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

            //res =screen->blit(_surf,p);
            res =screen->blit(*_psurf,p);
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

