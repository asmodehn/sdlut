#include "Sprite.hh"

namespace RAGE
{
    namespace AML
    {

        Sprite::Sprite(std::string filename)
        try : _surf(filename),posX(0),posY(0)
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


#ifndef HAVE_OPENGL
        bool Sprite::render(SDL::VideoSurface * screen)
        {
#if (DEBUG == 2)
            Log <<  nl << "Sprite::render("<< screen<<") called ..." << std::endl;
            assert(screen);
#endif

            bool res = false;

#if (DEBUG == 2)
            Log << nl << "blitting at " << SDL::Point(posX,posY);
#endif
            res =screen->blit(_surf,SDL::Point(posX,posY));

#if (DEBUG == 2)

            Log <<  nl << "Sprite::render("<< screen<<") done." << std::endl;
            assert(screen);
#endif

            return res;
        }
#else
        bool Sprite::render()
        {}
#endif

    }
}

