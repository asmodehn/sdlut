/*
 Test program for Core Logger
*/

#include "Core.hh"
#include <string>
using namespace Core;

int testlogstream(logstream & ls)
{
       ///test logstream default setup
    /// date insertion
    /// default "" prefix
    /// default loglevel

    ///test logstream date insertion
    ls << "test";
    //TODO
    //ls.str() == date + "test"
    ls << std::endl;

    ///test logstream custom prefix
    ls.resetprefix("LogTest :");
    ls << "test";
    //TODO
    //ls.str() == date + prefix + "test"
    ls <<std::endl;
    ls.resetprefix();

    ///test logstream and loglevel
    ls.resetLevel(loglevel::INFO);
    ls << loglevel::DEBUG << "Debug message" << std::endl; //ignored
    ls << loglevel::INFO << "Info message" << std::endl; // ok
    ls << loglevel::WARNING << "Warning message" << std::endl; //ok
    ls << loglevel::ERROR << "Error message" << std::endl; //ok
    ls << loglevel::FATAL << "Fatal message" << std::endl; //ok

    ls.resetLevel(loglevel::ERROR);


    ls << loglevel::DEBUG << "Debug message" << std::endl; //ignored
    ls << loglevel::INFO << "Info message" << std::endl; //ignored
    ls << loglevel::WARNING << "Warning message" << std::endl; //ignored
    ls << loglevel::ERROR << "Error message" << std::endl; //ok
    ls << loglevel::FATAL << "Fatal message" << std::endl; //ok


return 0;

}



int main(int argc, char *argv[])
{
    int res = 0;

    clogstreambuf clsb;
    logstream ls(&clsb);

    res += testlogstream(ls);

    filelogstreambuf flsb("MytestLog.txt");
    logstream fls(&flsb);

    res += testlogstream(fls);


    //this should not go anywhere or do anything
    cnull << "BLABLAALALAHAHAHA" << std::endl;


    //Test NewLogger
    NewLogger log;
    log.enableFileLog("newlogger.txt");
    res += testlogstream(log);



    return res;
}

