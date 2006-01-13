#ifndef AML_WINDOW_HH
#define AML_WINDOW_HH

#include "Config.hh"
#include "Camera.hh"
#include "Scene.hh"

#include <string>

namespace AML
{


/**
  * This class manages the Window created by AML
  */
    class Window
    {
        Scene * _scene;

        public:
        Window(std::string title, std::string icon, int width, int height);

        Scene * getScene() { return _scene;}
        void loop();
    };
}


#endif

