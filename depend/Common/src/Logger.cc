#include "Logger.hh"



Logger::Logger(const std::string & LogPrefix,int indentlvl, int indentwidth)
: /*std::ostream(new std::stringbuf(std::ios_base::out)),*/ _indentlvl(indentlvl), _indentwidth(indentwidth),_logprefix(LogPrefix)
{
	_consoleLog = true; _fileLog = false;
}

//TO TEST
bool Logger::setLogfile( const std::string & filename)
{
	bool res=true;
	_ofstr.open(filename.c_str(),std::ofstream::out | std::ofstream::app);
  if (!_ofstr )
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

	if (_consoleLog) std::clog.flush();
	if (_fileLog) _ofstr.flush();
	return *this;
}

//to enable ostream manipulators on Logger
Logger& Logger::operator << (std::ostream& (*manip)(std::ostream&))
{
	if (_consoleLog) (*manip)(std::clog);
	if (_fileLog)(*manip)(_ofstr);
	return *this;
}

//to enable ios manipulators on Logger
Logger& Logger::operator << (std::ios_base& (*manip)(std::ios_base&))
{
    if (_consoleLog) (*manip)(std::clog);
	if (_fileLog)(*manip)(_ofstr);
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

