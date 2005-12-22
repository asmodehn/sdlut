#include "Logger.hh"



Logger::Logger(const std::string & LogPrefix,int indentlvl, int indentwidth)
: /*std::ostream(new std::stringbuf(std::ios_base::out)),*/ _indentlvl(indentlvl), _indentwidth(indentwidth),_logprefix(LogPrefix)
{
	_clogSwitch = true;
}

//TO TEST
bool Logger::setLogfile( const std::string & filename)
{
	bool res=true;
	ofstr.open(filename.c_str(),std::ofstream::out | std::ofstream::app);
  if ( !ofstr )
  {
    operator<< ("LOG ERROR : Failed to open " + filename );
    res=false;
  }
  return res;
}


Logger& nl (Logger& log) // adds a new line with the prefix
{
				std::string s(log._indentlvl * log._indentwidth, ' ');
				s +=log._logprefix + " : ";

				log << "\n" << s;
				return log;
}

Logger & Logger::flush(void)
{

	if (_clogSwitch) std::clog.flush();
	if (ofstr) ofstr.flush();
	return *this;
}

//to enable ostream manipulators on Logger
Logger& Logger::operator << (std::ostream& (*manip)(std::ostream&))
{
	if (_clogSwitch) (*manip)(std::clog);
	if (ofstr)(*manip)(ofstr);
	return *this;
}

//to enable ios manipulators on Logger
Logger& Logger::operator << (std::ios_base& (*manip)(std::ios_base&))
{
    if (_clogSwitch) (*manip)(std::clog);
	if (ofstr)(*manip)(ofstr);
	return *this;
}

//to enable ostream manipulators on Logger
Logger& Logger::operator << (Logger& (*manip)(Logger&))
{
	(*manip)(*this);
	return *this;
}

Logger::~Logger()
{
	flush();
}

