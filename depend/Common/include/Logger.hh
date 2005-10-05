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
    Logger(const std::string & filename, Loglevel filelvl = verbose, int indentwidth = LOGINDENTWIDTH ) throw (std::logic_error);
    ///Default Destructor that flush the Log Buffer
    ~Logger();
    
    bool add(std::string, Loglevel lvl = normal, int indentlevel = LOGINDENTLVL);
    
    void flush(void);

};

inline Logger::Logger(Loglevel lvl, int indentwidth)
: _loglevel(lvl), _indentwidth(indentwidth)
{
	
}

inline Logger::Logger(const std::string & filename, Loglevel lvl, int indentwidth) throw (std::logic_error)
try : _loglevel(lvl), _indentwidth(indentwidth)
{
	std::ofstream logfile(filename.c_str());
  if ( logfile )
    std::clog.rdbuf(logfile.rdbuf());
  else
    throw std::logic_error( "Failed to open " + filename );
}
catch (std::exception &e )
{
	std::cerr << "Exception catched in Logger constructor ! " << e.what();
  std::clog << filename << " can't be opened. Going on with console log output.";
}

inline bool Logger::add(std::string msg, Loglevel lvl, int indentlevel)
{
	std::string s(indentlevel * _indentwidth, ' ');
	bool getmsg = (lvl <=_loglevel);
	if ( getmsg )
    std::clog << s << LOGPREFIX << " : " << msg;
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
