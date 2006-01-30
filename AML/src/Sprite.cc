#include "Sprite.hh"

namespace RAGE
{
    namespace AML
    {
        Sprite::Sprite(const Image & img) throw (std::logic_error)
        try
:
            _img (img),
            _ori(img.getSize()),
            _pos(0,0)
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

        Sprite::Sprite(const Image & img, std::string spriteID) throw (std::logic_error)
        try
:
            _img (img),
            _pos(0,0)
        {
#ifdef DEBUG
            Log << nl << "Sprite::Sprite() called ...";
#endif

        _ori = _img.getComponent(spriteID,0,0);
        Log << nl << _ori;
#ifdef DEBUG

            Log << nl << "Sprite::Sprite() done.";
#endif

        }
        catch (std::exception & e)
        {
            Log << nl << "Exception in Sprite constructor ! " << nl << e.what ();
        }

        Sprite::Sprite(const Sprite &s)
                : _img (s._img), _ori(s._ori),_pos( s._pos)
        {
            Log << nl << "Sprite Copy !!!";
        }

        Sprite& Sprite::operator=(const Sprite &s)
        {
            Log << nl << "Sprite Assign !!!";
            if (this != &s)
            {
                _ori = s._ori;
                _pos = s._pos;
            }
            return *this;
        }

        bool Sprite::operator == (const Sprite & s)
        {
            return _pos == s._pos && _ori == s._ori;
        }

#ifndef HAVE_OPENGL
        bool Sprite::render(SDL::VideoSurface * screen) const
        {
#if (DEBUG == 2)
            Log <<  nl << "Sprite::render("<< screen<<") called ..." << std::endl;
            assert(screen);
#endif

            bool res = false;

#if (DEBUG == 2)

            Log << nl << "blitting at " << _pos;
#endif

            res =_img.display(screen, _ori, _pos);
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

