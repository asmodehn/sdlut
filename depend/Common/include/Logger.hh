#ifndef LOGGER_HH
#define LOGGER_HH

#include <iostream>
#include <fstream>

///just a LOGINDENT value to be defined at build time. this way you have indent levels depending on built libraries
#ifndef LOGINDENTLVL
#define LOGINDENTLVL 0
#endif

///just a LOGPREFIX value to be defined at build time. this way you can have a prefix for the whole project binary (library or executable)
#ifndef LOGPREFIX
#define LOGPREFIX "Default Log"
#endif

///the default tab width for the indent...
#ifndef LOGINDENTWIDTH
#define LOGINDENTWIDTH 2
#endif


/**
 * \class Logger
 *
 * \brief This class defines loglevel on top of clog
 *
 * This Logger use indentation levels, and also filters using 3 loglevel : quiet / normal / verbose
 * TODO : need to be improved to be used with stream as well as strings.
 * TODO : Improve LogLevels to filter the console output as well as the file output...
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
  Loglevel _loglevel;
	int _indentwidth;
	std::string _logprefix;
	
  public :
  
    ///Default Constructor that defines the loglevel of messages stored
    Logger(const std::string & LogPrefix = LOGPREFIX,Loglevel lvl = verbose, int indentwidth = LOGINDENTWIDTH );
    
    ///Default Destructor that flush the Log Buffer
    ~Logger();
    
    bool setLogfile( const std::string & filename,  Loglevel outlvl = verbose);
    
    bool add(const std::string& message, Loglevel lvl = normal, int indentlevel = LOGINDENTLVL);
        
    void flush(void);

};

inline Logger::Logger(const std::string & LogPrefix,Loglevel lvl, int indentwidth)
: _loglevel(lvl), _indentwidth(indentwidth),_logprefix(LogPrefix)
{
	
}

inline bool Logger::setLogfile( const std::string & filename, Loglevel outlvl)
{
	bool res=false;
	// TODO : improve that to filter the messages by level.
	std::ofstream logfile(filename.c_str());
  if ( logfile )
  {
    std::clog.rdbuf(logfile.rdbuf());
    res=true;
  }
  else
  {
    add("Failed to open " + filename );
  }
  return res;
}


inline bool Logger::add( const std::string & msg, Loglevel lvl, int indentlevel)
{
	std::string s(indentlevel * _indentwidth, ' ');
	bool getmsg = (lvl <=_loglevel);
	if ( getmsg )
    std::clog << s << _logprefix << " : " << msg << "\n";
	return getmsg;
}


inline void Logger::flush(void)
{
	std::clog.flush();
}

inline Logger::~Logger()
{
	flush();
}


#endif
