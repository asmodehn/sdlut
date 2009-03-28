
/* Test program to try Empty Loop...
*/


 #include "SDL.hh"
 using namespace RAGE;
 using namespace RAGE::SDL;

 int main(int argc, char *argv[])
 {
  Logger testlog("testApp");
  SDL::App::getInstance().setName ("RAGE::SDL Functionnal testing - App");
  //Minimum Init
  testlog << nl << " Minimum init... " << std::endl;
  testlog << ( (SDL::App::getInstance().init())? "OK" : "FAILED" );
  //testlog << nl << " Retrieving Manager... " << std::endl;
  //testlog << ( (SDL::App::getInstance().getManager() != NULL)? "OK" : "FAILED" );

  //Video Init
  testlog << nl << " Enabling Video... " << std::endl;
  testlog << ( (SDL::App::getInstance().initVideo(false,false,false,false))? "OK" : "FAILED" );

  //Audio Init
  testlog << nl << " Enabling Audio... " << std::endl;
  testlog << ( (SDL::App::getInstance().initAudio())? "OK" : "FAILED" );
  
  //Timer Init
  testlog << nl << " Enabling Timer... " << std::endl;
  testlog << ( (SDL::App::getInstance().initTimer())? "OK" : "FAILED" );
  
 #ifdef HAVE_SDLTTF
  //Font Init
  testlog << nl << " Enabling Text... " << std::endl;
  testlog << ( (SDL::App::getInstance().initText())? "OK" : "FAILED" );
 #endif
  
  App::getInstance().getWindow().resetDisplay(800,600);
  App::getInstance().getWindow().mainLoop();
  return 0;
 }
