#ifndef NEWLOGGER_HH
#define NEWLOGGER_HH

#include "Core/Logging/logstream.hh"

namespace Core
{

    /***
     *
     * \class NewLogger
     * \brief NewLogger manages the Logging outputs for the application.
     *
     */

class NewLogger : std::ostream
{
    public:
    NewLogger();
    NewLogger(const NewLogger& );
    ~NewLogger();

    ///by default outputs to std::clog
    //enable more Sinks
    enableFileLog(std::string filename);
    enableSysLog();
    enableWinLog();

    disableFileLog();
    disableSysLog();
    disableWinLog();


    //accessors to logstream ( to set levels for example )
    logstream& getFileLog();
    logstream& getSysLog();
    logstream& getWinLog();

    protected :
    //list of logstream. Each logstream has one output and only one
    logstream pvm_filelogstream;
    logstream pvm_syslogstream;
    logstream pvm_winlogstream;

    private :
    //list of logstreambuf. Each logstreambuf provide a different ouput to logstream
    logstreambuf pvm_filelsb;
    logstreambuf pvm_syslsb;
    logstreambuf pvm_winlsb;

};

}


#endif
