#include "Logger.hh"

Logger::Logger(std::ostream & ostr) : _ostr(ostr)
{
}

bool Logger::add(std::string msg)
{
	_ostr << msg;
	return true;
}

bool Logger::flush(void)
{
	_ostr << std::endl;
	return true;
}

Logger::~Logger()
{
	flush();
}

