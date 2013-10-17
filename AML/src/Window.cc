#include "Window.hh"

namespace RAGE
{
    namespace AML
    {
        Window::Window(std::string title, std::string icon, int width, int height)
        {
#ifdef DEBUG
            Log << nl << "Window::Window() called ..." ;
 #endif
            SDL::App::getInstance().setName ( title );
            SDL::App::getInstance().setIcon( icon);
            if (SDL::App::getInstance().initVideo(false,false,true,false) )
            {
               SDL::App::getInstance().getWindow()->reset(width,height);
                _scene = new Scene();
                SDL::App::getInstance().getWindow()->setEngine(_scene);



            }
#ifdef DEBUG
            Log << nl << "Window::Window() done." ;
 #endif
        }

        void Window::loop()
        {
#ifdef DEBUG
            Log << nl << "Window::loop() called ..." ;
 #endif
            SDL::App::getInstance().getWindow()->mainLoop();
#ifdef DEBUG
            Log << nl << "Window::loop() done." ;
 #endif
        }


    }
}
