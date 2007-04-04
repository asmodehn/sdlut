#ifndef LOGGER_HH
#define LOGGER_HH

#include <iostream>
#include <fstream>
#include <sstream>

///just a LOGINDENT value to be defined at build time. this way you have indent levels depending on built libraries
#ifndef LOGINDENTLVL
#define LOGINDENTLVL 0
#endif

///the default tab width for the indent...
#ifndef LOGINDENTWIDTH
#define LOGINDENTWIDTH 2
#endif

///just a LOGPREFIX value to be defined at build time. this way you can have a prefix for the whole project binary (library or executable)
#ifndef LOGPREFIX
#define LOGPREFIX "RAGE Log"
#endif

///To disable logging
#ifndef NRAGELOG
#define RAGELOG
#endif

namespace RAGE
{

    /**
     * \class Logger
     *
     * \brief This class defines loglevel on top of Logger
     *
     * This Logger use indentation levels, usually defined on build time.
     * TODO : Add LogLevels to filter the console output as well as the file output (3 loglevel : quiet / normal / verbose)
     * Not yet in SDL namespace because it doesnt depend on SDL. However, later it should be made threadsafe, somehow...
     *
     * \author Alex
     *
     * \date 2005/10/05
     *
     * Contact: asmodehn@gna.org
     *
     */


    typedef enum
    {
        quiet,normal,verbose
    }
    Loglevel;
    
    class Logger //: public std::ostream
    {
        int _indentlvl,_indentwidth;
        std::string _logprefix;

        std::ofstream _ofstr;
        bool _consoleLog;
        bool _fileLog;

        bool setLogfile( const std::string & filename);

    public :

        ///Default Constructor that defines how to write the log
        Logger(const std::string & LogPrefix = LOGPREFIX, int indentlevel = LOGINDENTLVL, int indentwidth = LOGINDENTWIDTH );

        ///Default Destructor that flush the Log Buffer
        ~Logger();



        void toggleConsoleLog()
        {
            _consoleLog = !_consoleLog ;
        }
        void enableConsoleLog()
        {
            _consoleLog= true ;
        }
        void disableConsoleLog()
        {
            _consoleLog = false ;
        }

	//warning, this is likely to return false in release build
        bool enableFileLog( const std::string & filename)
        {
#ifdef RAGELOG
            _fileLog= true ;
            return setLogfile(filename);
#else
	return false;
#endif
        }
        void disableFileLog()
        {
#ifdef RAGELOG
            _fileLog = false ;
            _ofstr.close();
#endif
        }

        //void add(const std::string & message); // not const because of initial '\n' in string from streams...
        template<typename M>
        Logger& operator << (const M & msg);
        //to enable manipulators on Logger
        Logger& operator << (std::ostream& (*manip)(std::ostream&));
        Logger& operator << (std::ios_base& (*manip)(std::ios_base&));
        Logger& operator << (Logger& (*manip)(Logger&));//to enable specific manipulators on Logger

        friend Logger& nl (Logger& log); // adds a prefix
        friend Logger& endl (Logger& log); // adds a prefix

        Logger & flush(void);

        //TODO : handle operator<< and
        //http://www.mactech.com/articles/mactech/Vol.16/16.04/StreamforAllSeasons/
        //http://www.horstmann.com/cpp/iostreams.html
        //http://spec.winprog.org/streams/

    };

    template<typename M>
    Logger& Logger::operator<< ( const M & msg)
    {
#ifdef RAGELOG
        if (_consoleLog)
            std::clog << msg;
        if (_fileLog)
            _ofstr << msg;
#endif
        return *this;
    }

    Logger& nl (Logger& log); // adds a new line with the prefix

}


#endif
