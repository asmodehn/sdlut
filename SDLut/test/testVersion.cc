#include "TestCommon.hh" // for argParser only

Logger testlog("testVersion");

using namespace SDLut;

int main(int argc, char *argv[])
{
    testlog.enableFileLog("testVersion.log");

    bool exitstatus = true;

    //SDL lib
    //TODO : find a lower limit in supported SDL 1.2 versions
    Version sdlv(Version::Main);
    testlog << nl << sdlv;
    exitstatus = exitstatus && sdlv.check();
    testlog << nl << (exitstatus? "OK" : "ERROR");

    //TTF lib
    //TODO : find a lower limit in supported SDL 1.2 versions
    Version ttfv(Version::TTF);
    testlog << nl << ttfv;
    exitstatus = exitstatus && ttfv.check();
    testlog << nl << (exitstatus? "OK" : "ERROR");

    //Image lib
    //TODO : find a lower limit in supported SDL 1.2 versions
    Version imgv(Version::Image);
    testlog << nl << imgv;
    exitstatus = exitstatus && imgv.check();
    testlog << nl << (exitstatus? "OK" : "ERROR");

    //Mixer lib
    //TODO : find a lower limit in supported SDL 1.2 versions
    Version mixv(Version::Mixer);
    testlog << nl << mixv;
    exitstatus = exitstatus && mixv.check();
    testlog << nl << (exitstatus? "OK" : "ERROR");

    //Net lib
    //TODO : find a lower limit in supported SDL 1.2 versions
    Version netv(Version::Net);
    testlog << nl << netv;
    exitstatus = exitstatus && netv.check();
    testlog << nl << (exitstatus? "OK" : "ERROR");


    return exitstatus? 0 : -1;
}
