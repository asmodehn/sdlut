/*
 Test program for Core Logger
*/

#include "Core.hh"
#include <string>
using namespace Core;

int main(int argc, char *argv[])
{
    bool res = 0;

    logstream ls;


    ///Test logstream default prefix
    res = (ls.getprefix() == "");

    ///Test logstream added fields
    std::string nowstr;
    //date TODO
    //std::string nowstr = Date::today().localascii();
    //time (test should be fast enough) TODO
    //nowstr += Time::now().localascii();
    //thread TODO
    //message
    ls << "test";
    res = res && (ls.str() == nowstr + "test");

    //end test
    ls.flush();

    ///Test prefix
    ls.resetprefix("MyLog :");
    ls << "test";
    res = res && (ls.str() == "MyLog : test");

    ls.resetprefix();
    //Test default logstream formatting
    //TODO ( like for any stream )

    //endtest
    ls.flush();

    ls << "Test logstream sentence" << std::endl;

    return (res == true)?0:-1;



    /*
        //This test the main logger from Core
        res = testout(Logger::get(),makeTestType<std::string>());

        if ( ! res )
        {
            std::cerr << " ERROR : Logger cannot output strings. Aborting test." << std::endl;
            return -1;
        }

        //TODO : test more basic types

        //Test differents logger
        int level = 2;
        std::string prefix = "lvl2log";
        Logger log(prefix,level);

        res = res && testout(log,makeTestType<std::string>());



    */
    return 0;
}

