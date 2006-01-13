//test program
#include "AML.hh"

//tmp : logger is aimed only for internal use in AML
#include "Logger.hh"

//would be nice if we can put that in AML.hh
#ifdef __MINGW32__
#ifdef main
#undef main
#endif
#endif

using namespace AML;

int main ( int argc, char * argv [])
{
    Logger testlog("AMLtest.log");

    //If using external resources :
    //testlog << nl << "Loading resources" << std::endl;
    //Resources.loadimage("");
    testlog << nl << "Loading sprite..." << std::endl;
    Sprite testbmp("../data/AML_ico.bmp");

    //If using specific input
    //testlog << nl << "Defining Input" << std::endl;

    testlog << nl << "Creating the window..." << std::endl;
    Window mainWin("AML test", "../data/AML_ico.bmp",640,480);

    testlog << nl << "Setting up the Scene..." << std::endl;
    mainWin.getScene()->put(testbmp, 320, 240);

    testlog << nl << "Starting the main loop..." << std::endl;
    mainWin.loop();

    return 0;
}
