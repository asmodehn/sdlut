#ifndef LOGGER_HH
#define LOGGER_HH

#include "AML_config.hh"

#include <iostream>

class Logger
{
	std::ostream& _ostr;
	
  public :
    Logger(std::ostream & ostr = std::cout);
    //TODO Logger (std::string filename);
    ~Logger();
    
    bool add(std::string);
	
    bool flush(void);
    
    
};

#endif
