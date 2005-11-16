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
#define LOGPREFIX "Default Log"
#endif




/**
 * \class Logger
 *
 * \brief This class defines loglevel on top of clog
 *
 * This Logger use indentation levels, usually defined on build time.
 * TODO : need to be improved to be used with streams as well as strings.
 * TODO : Add LogLevels to filter the console output as well as the file output (3 loglevel : quiet / normal / verbose)
 *
 * \author Alex
 *
 * \date 2005/10/05
 *
 * Contact: asmodehn@gna.org
 *
 */


typedef enum {quiet,normal,verbose} Loglevel;

class Logger
{
	int _indentlvl,_indentwidth;
	std::string _logprefix;
	std::ofstream ofstr;
	bool _clogSwitch;

  public :

    ///Default Constructor that defines how to write the log
    Logger(const std::string & LogPrefix = LOGPREFIX, int indentlevel = LOGINDENTLVL, int indentwidth = LOGINDENTWIDTH );

    ///Default Destructor that flush the Log Buffer
    ~Logger();

    bool setLogfile( const std::string & filename);

    void toggleclog() { _clogSwitch = !_clogSwitch ; }
    void enableclog() { _clogSwitch= true ; }
    void disableclog() { _clogSwitch = false ; }

    void add(const std::string & message); // not const because of initial '\n' in string from streams...

  //TODO : handle operator<<
  //http://www.mactech.com/articles/mactech/Vol.16/16.04/StreamforAllSeasons/
  //http://www.horstmann.com/cpp/iostreams.html
  //http://spec.winprog.org/streams/

    void flush(void);

};


#endif
