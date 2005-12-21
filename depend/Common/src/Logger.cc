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
    add("LOG ERROR : Failed to open " + filename );
    res=false;
  }
  return res;
}

void Logger::add( const std::string & msg)
{
	std::string s(_indentlvl * _indentwidth, ' ');
	s +=_logprefix + " : ";
	std::istringstream iss(msg);
	std::string outmsg;
	//need to parse the string to append the prefix on each newline
	while ( getline(iss, outmsg) )
	{
		if (_clogSwitch)
			std::clog << s << outmsg << std::endl;
		if (ofstr)
			ofstr << s << outmsg << std::endl;
	}
//	if (_clogSwitch)
//		std::clog << std::endl;
//	if (ofstr)
//		ofstr << std::endl;
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
}

//to enable ostream manipulators on Logger
Logger& Logger::operator << (std::ostream& (*manip)(std::ostream&))
{
		if (_clogSwitch) (*manip)(std::clog);
		if (ofstr) (*manip)(ofstr);
	return *this;
}

//to enable ostream manipulators on Logger
Logger& Logger::operator << (Logger& (*manip)(Logger&))
{
		if (_clogSwitch) (*manip)(*this);
		if (ofstr) (*manip)(*this);
	return *this;
}

Logger::~Logger()
{
	flush();
}

