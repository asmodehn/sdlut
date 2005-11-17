#include "Logger.hh"



Logger::Logger(const std::string & LogPrefix,int indentlvl, int indentwidth)
: _indentlvl(indentlvl), _indentwidth(indentwidth),_logprefix(LogPrefix)
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
	if (_clogSwitch)
		std::clog << std::endl;
	if (ofstr)
		ofstr << std::endl;
}

void Logger::flush(void)
{
	if (_clogSwitch)
		std::clog.flush();
	if (ofstr)
		ofstr.flush();
}

Logger::~Logger()
{
	flush();
}
