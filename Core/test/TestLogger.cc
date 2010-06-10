/*
 Test program for Core Logger
*/

#include "Core.hh"
using namespace Core;

/*
//Utils for tests...
//generate random test value, depending the type
template <class T> T makeTestType()
{
    //default : return newly constructed object
    return T();
}

template <class T=std::string> T makeTestType()
{
    return "fortytwo";
}

template <class T=int> T makeTestType()
{
    return 42;
}

//basic test functions
template <class T> bool testout(Logger log, T testval)
{
    std::string logged;
    log.addOutput(&logged);

    std::stringstream expected;
    for ( int i = 0 ; i < log.getIndent(); ++i) expected << "\t";
    expected << log.getPrefix() << ": " << testval << std::endl;

    log << testval << std::endl;
    return logged == expected.str();
}

*/

int main(int argc, char *argv[])
{
    bool res = 0;

    //streambuffer for formatting log messages
    //logstreambuf logbuf;


    std::stringstream ss;
    ss << "Test stringstream sentence" << std::endl;
    std::cout << ss.str();

    logstream ls;
    ls << "Test logstream sentence" << std::endl;
    std::cout << ls.str();



    return res;



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

