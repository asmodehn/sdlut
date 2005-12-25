#include "Window.hh"


namespace AML
{
Window::Window(std::string title, std::string icon, int width, int height)
        {
          	App::getInstance().setName ( title );
          	App::getInstance().setIcon( icon);
            if (App::getInstance().initWindow(false,false,true,false) )
                App::getInstance().getAppWindow()->reset(width,height);
            _scene = new Scene();
        }

Window::loop()
{
    App::getInstance().mainLoop();
}


}
