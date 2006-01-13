#include "Window.hh"

namespace RAGE
{
namespace AML
{
    Window::Window(std::string title, std::string icon, int width, int height)
    {
        SDL::App::getInstance().setName ( title );
        SDL::App::getInstance().setIcon( icon);
        if (SDL::App::getInstance().initVideo(false,false,true,false) )
        {    SDL::App::getInstance().getWindow()->reset(width,height);
        _scene = new Scene();
        SDL::App::getInstance().getWindow()->getDisplay()->setEngine(_scene);
        }
    }

    void Window::loop()
    {
        SDL::App::getInstance().getWindow()->mainLoop();
    }


}
}
