
/* Test program to compare the compile-time version of SDL with the linked
   version of SDL
*/

#include <stdio.h>

#include "SDL.hh"
using namespace RAGE;

int main(int argc, char *argv[])
{
    Logger testlog("testver");

    testlog <<nl << "SDL : " << SDL::Version(SDL::Version::Main)<< std::endl;
    testlog <<nl << "TTF : " << SDL::Version(SDL::Version::TTF)<< std::endl;
    testlog <<nl << "Image : " << SDL::Version(SDL::Version::Image)<< std::endl;
    testlog <<nl << "Mixer : " << SDL::Version(SDL::Version::Mixer)<< std::endl;
    testlog <<nl << "Net : " << SDL::Version(SDL::Version::Net)<< std::endl;
    

	return 0;
}
