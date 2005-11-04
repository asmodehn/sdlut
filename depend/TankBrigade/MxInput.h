# if !defined (MX_INPUT_H_)
# define MX_INPUT_H_


#include "MxSDL.h"
#include "MxScene.h"

namespace MxLib
{

    class MxInput : public SDL::EventHandler
    {

        bool closing;

    public:
        MxInput() : closing(false)
        {
          SDL::Event::enableKeyRepeat();
        }

        virtual bool handleKeyboardEvent (SDL_keysym &keysym, bool pressed)
        {
            switch( keysym.sym )
            {
                case SDLK_ESCAPE:
                if (pressed==false)
                    closing=true;
                break;
                case SDLK_F5:
                if (pressed==true)
                    MxInit::getDisplay()->iconify();
                break;
                case SDLK_F6:
                if (pressed==true)
                    MxInit::getDisplay()->toggleFullScreen();
                break;
                default:
                break;
            }
            return true;
        }

        virtual bool handleResizeEvent(int w, int h)
        {
            MxInit::getDisplay()->resize(w,h);
        }

        virtual bool handleQuitEvent(void)
        {
            closing=true;
            return true;
        }
        bool closed(void)
        {
            return closing;
        }

    };

}

#endif
