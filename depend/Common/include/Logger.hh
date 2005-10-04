#ifndef LOGGER_HH
#define LOGGER_HH

#include "AML_config.hh"

#include <iostream>

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
    Logger(Loglevel lvl = verbose, int indentwidth = 2);
    //TODO Logger (std::string filename, Loglevel memlvl, Loglevel filelvl);
    ///Default Destructor that flush the Log Buffer
    ~Logger();
    
    bool add(std::string, Loglevel lvl);
    bool add(int indentlevel, std::string, Loglevel lvl);
	
    void flush(void);
    
    
};

inline Logger::Logger(Loglevel lvl, int indentwidth)
: _loglevel(lvl), _indentwidth(indentwidth)
{
	
}

inline bool Logger::add(std::string msg,Loglevel lvl)
{
	bool getmsg = (lvl <=_loglevel);
	if ( getmsg )
    std::clog << msg;
	return getmsg;
}

inline bool Logger::add(int indentlevel, std::string msg,Loglevel lvl)
{
  std::string s(indentlevel * _indentwidth, ' ');
	std::clog << s;
	return add(msg, lvl);
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
