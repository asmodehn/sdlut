
/* Test program to compare the compile-time version of SDL with the linked
   version of SDL
*/

#include "SDL.hh"

using namespace RAGE;
using namespace SDLut;

int main(int argc, char *argv[])
{
    RAGE::Logger testlog("testver");

    testlog <<nl << "SDL : " << Version(Version::Main)<< std::endl;
    testlog <<nl << "TTF : " << Version(Version::TTF)<< std::endl;
    testlog <<nl << "Image : " << Version(Version::Image)<< std::endl;
    testlog <<nl << "Mixer : " << Version(Version::Mixer)<< std::endl;
    testlog <<nl << "Net : " << Version(Version::Net)<< std::endl;

    return 0;
}
