#include "Core/Logging/logstream.hh"

namespace Core
{

logstream::logstream ()
        : std::ostream(0)
{

    pvm_lsb = new logstreambuf();

    this->init(pvm_lsb);

    //setup default flags
    this->flags ( std::ios::left | std::ios::hex | std::ios::showbase | std::ios::boolalpha );

}

logstream::~logstream()
{
    delete pvm_lsb;
}

/*
///Formatted output
///Insert data with format (public member function)
logstream& logstream::operator<< (bool& val )
{
    flags()
    return *this << std::alpha(true) << val << std::boolalpha;
}
logstream& logstream::operator<< (short& val )
{
    return dynamic_cast<logstream&>(std::ostream::operator<<(val));
}
logstream& logstream::operator<< (unsigned short& val )
{
    return dynamic_cast<logstream&>(std::ostream::operator<<(val));
}
logstream& logstream::operator<< (int& val )
{
    return dynamic_cast<logstream&>(std::ostream::operator<<(val));
}
logstream& logstream::operator<< (unsigned int& val )
{
    return dynamic_cast<logstream&>(std::ostream::operator<<(val));
}
logstream& logstream::operator<< (long& val )
{
    return dynamic_cast<logstream&>(std::ostream::operator<<(val));
}
logstream& logstream::operator<< (unsigned long& val )
{
    return dynamic_cast<logstream&>(std::ostream::operator<<(val));
}
logstream& logstream::operator<< (float& val )
{
    return dynamic_cast<logstream&>(std::ostream::operator<<(val));
}
logstream& logstream::operator<< (double& val )
{
    return dynamic_cast<logstream&>(std::ostream::operator<<(val));
}
logstream& logstream::operator<< (long double& val )
{
    return dynamic_cast<logstream&>(std::ostream::operator<<(val));
}
logstream& logstream::operator<< (const void* val )
{
    return dynamic_cast<logstream&>(std::ostream::operator<<(val));
}


logstream& logstream::operator<< (logstreambuf* sb )
{
    return dynamic_cast<logstream&>(std::ostream::operator<<(sb));
}

logstream& logstream::operator<< (std::ostream& ( *pf )(std::ostream&))
{
    return dynamic_cast<logstream&>(std::ostream::operator<<(pf));
}
logstream& logstream::operator<< (std::ios& ( *pf )(std::ios&))
{
    return dynamic_cast<logstream&>(std::ostream::operator<<(pf));
}
logstream& logstream::operator<< (std::ios_base& ( *pf )(std::ios_base&))
{
    return dynamic_cast<logstream&>(std::ostream::operator<<(pf));
}
*/

///Unformatted output
///Put character (public member function)
logstream& logstream::put ( char c )
{
    return dynamic_cast<logstream&>(std::ostream::put(c));
}
///Write block of data (public member function)
logstream& logstream::write ( const char* s , std::streamsize n )
{
    return dynamic_cast<logstream&>(std::ostream::write(s,n));
}


///Positioning
///Get position of put pointer (public member function)
std::streampos logstream::tellp ( )
{
    return std::ostream::tellp();
}
///Set position of put pointer (public member function)
logstream& logstream::seekp ( std::streampos pos )
{
    return dynamic_cast<logstream&>(std::ostream::seekp(pos));
}
logstream& logstream::seekp ( std::streamoff off, std::ios_base::seekdir dir )
{
    return dynamic_cast<logstream&>(std::ostream::seekp(off,dir));
}

///Synchronization
///Flush output stream buffer (public member function)
logstream& logstream::flush ( )
{
    return dynamic_cast<logstream&>(std::ostream::flush());
}

/*
///Prefix/Suffix:
///Perform exception safe prefix/suffix operations (public member classes)
logstream::sentry::sentry ( std::ostream& os )
        : std::ostream::sentry::sentry(os)
{
}
logstream::sentry::~sentry()
{
    //calling destructor
}
logstream::sentry::operator bool() const
{
    return std::ostream::sentry::operator bool();
}
*/

/*
logstream& operator<< (logstream& out, char c )
{
    return dynamic_cast<logstream&>(std::operator<<(static_cast<std::ostream&>(out),c));
}

logstream& operator<< (logstream& out, signed char c )
{
    return dynamic_cast<logstream&>(std::operator<<(static_cast<std::ostream&>(out),c));
}
logstream& operator<< (logstream& out, unsigned char c )
{
    return dynamic_cast<logstream&>(std::operator<<(static_cast<std::ostream&>(out),c));
}

logstream& operator<< (logstream& out, const char* s )
{
    return dynamic_cast<logstream&>(std::operator<<(static_cast<std::ostream&>(out),s));
}
logstream& operator<< (logstream& out, const signed char* s )
{
    return dynamic_cast<logstream&>(std::operator<<(static_cast<std::ostream&>(out),s));
}
logstream& operator<< (logstream& out, const unsigned char* s )
{
    return dynamic_cast<logstream&>(std::operator<<(static_cast<std::ostream&>(out),s));
}
*/

} // Core


