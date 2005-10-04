#ifndef LOGGER_HH
#define LOGGER_HH

#include "AML_config.hh"

#include <iostream>

///just a LOGINDENT value to be defined at build time. this way you have indent levels depending on built libraries

#ifndef LOGINDENTLVL
#define LOGINDENTLVL 0
#endif

#ifndef LOGINDENTWIDTH
#define LOGINDENTWIDTH 2
#endif


/**
 * \class Logger
 *
 * \brief This class defines loglevel on top of clog
 *
 * This Logger use indentation levels, and also filters using 3 loglevel : quiet / normal / verbose
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
	
  public :
  
    ///Default Constructor that defines the loglevel of messages stored
    Logger(Loglevel lvl = verbose, int indentwidth = LOGINDENTWIDTH );
    //TODO Logger (std::string filename, Loglevel memlvl, Loglevel filelvl, indentstuff );
    ///Default Destructor that flush the Log Buffer
    ~Logger();
    
    bool add(std::string, Loglevel lvl = normal, int indentlevel = LOGINDENTLVL);
    
    void flush(void);
    
    
};

inline Logger::Logger(Loglevel lvl, int indentwidth)
: _loglevel(lvl), _indentwidth(indentwidth)
{
	
}

inline bool Logger::add(std::string msg, Loglevel lvl, int indentlevel)
{
	std::string s(indentlevel * _indentwidth, ' ');
	bool getmsg = (lvl <=_loglevel);
	if ( getmsg )
    std::clog << s << msg;
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
