#include "Window.hh"

namespace RAGE
{
    namespace AML
    {
        Window::Window(std::string title, std::string icon, int width, int height)
        {
            Log << nl << "Window::Window() called" ;
            SDL::App::getInstance().setName ( title );
            SDL::App::getInstance().setIcon( icon);
            if (SDL::App::getInstance().initVideo(false,false,true,false) )
            {
                _scene = new Scene();
                SDL::App::getInstance().getWindow()->setEngine(_scene);
                SDL::App::getInstance().getWindow()->reset(width,height);

            }
        }

        void Window::loop()
        {
            SDL::App::getInstance().getWindow()->mainLoop();
        }


    }
}
