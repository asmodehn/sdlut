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
#ifdef DEBUG
            Log <<  nl << "Sprite::render() called ..." << std::endl;
            assert(screen);
#endif

            bool res = false;


            res =screen->blit(_surf,SDL::Point(posX,posY));

#ifdef DEBUG

            Log <<  nl << "Sprite::render() done." << std::endl;
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

