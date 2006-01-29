#include <iostream>
#include "AML.hh"

using namespace RAGE;
using namespace RAGE::AML;

int main()
{

    Config c; //temporary just to get the log

    Logger testlog("TankBrigade.log");

    testlog << nl << "Loading data..." << std::endl;
    Image img("spritelib_gpl/maze/tankbrigade.bmp",SDL::Color(0,0,0));

    Sprite testbmp(img);

    testlog << nl << "Creating the window..." << std::endl;
    Window mainWin("AML test", "data/AML_icon.bmp",640,480);

    testlog << nl << "Setting up the Scene..." << std::endl;
    mainWin.getScene()->put(&testbmp);

    testlog << nl << "Starting the main loop..." << std::endl;
    mainWin.loop();

    return 0;
}
