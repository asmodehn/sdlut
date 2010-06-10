#include "Core/Logging/logstreambuf.hh"

namespace Core
{

logstreambuf::logstreambuf()
        : std::streambuf()
{
}

logstreambuf::~logstreambuf()
{
    //destructor of streambuf should be called here
}


//The common functionality for all stream buffers is provided through the following public member functions:

//Locales:
///Imbue locale (public member function)
std::locale logstreambuf::pubimbue ( const std::locale & loc )
{
    return ptm_buf.pubimbue(loc);
}
///Get current locale (public member function)
std::locale logstreambuf::getloc ( ) const
{
    return std::streambuf::getloc();
}
//Buffer management and positioning:
///Set buffer array (public member function)
logstreambuf* logstreambuf::pubsetbuf ( char* s, std::streamsize n )
{
    return dynamic_cast<logstreambuf*>(std::streambuf::pubsetbuf(s,n));
}
///Set internal position pointer to relative position (public member function)
std::streampos logstreambuf::pubseekoff ( std::streamoff off, std::ios_base::seekdir way, std::ios_base::openmode which )
{
    return std::streambuf::pubseekoff(off,way,which);
}
///Set internal position pointer to absolute position (public member function)
std::streampos logstreambuf::pubseekpos ( std::streampos sp, std::ios_base::openmode which )
{
    return std::streambuf::pubseekpos(sp,which);
}
///Synchronize stream buffer (public member function)
int logstreambuf::pubsync ( )
{
    return std::streambuf::pubsync();
}
//Input functions (get):
///Get number of characters available to read (public member function)
std::streamsize logstreambuf::in_avail ( )
{
    return std::streambuf::in_avail();
}
///Increase get pointer and return next character (public member function)
int logstreambuf::snextc ( )
{
    return std::streambuf::snextc();
}
///	Get current character and increase get pointer (public member function)
int logstreambuf::sbumpc ( )
{
    return std::streambuf::sbumpc();
}
///Get current character (public member function)
int logstreambuf::sgetc ( )
{
    return std::streambuf::sgetc();
}
///	Get sequence of characters (public member function)
std::streamsize logstreambuf::sgetn ( char * s, std::streamsize n )
{
    return std::streambuf::sgetn (s,n);
}
///Put character back (public member function)
int logstreambuf::sputbackc ( char c )
{
    return std::streambuf::sputbackc(c);
}
///Decrease get pointer (public member function)
int logstreambuf::sungetc ( )
{
    return std::streambuf::sungetc();
}
//Output functions (put):
///Store character at current put position and increase put pointer (public member function)
int logstreambuf::sputc ( char c )
{
    return std::streambuf::sputc(c);
}
///Write a sequence of characters (public member function)
std::streamsize logstreambuf::sputn ( const char * s, std::streamsize n )
{
    return std::streambuf::sputn(s,n);
}






///Locales
///Imbue locale (virtual protected member function)
void logstreambuf::imbue ( const std::locale & loc )
{
    //TODO : overload this
}

///Buffer management and positioning
///Set buffer
logstreambuf* logstreambuf::setbuf ( char* s, std::streamsize n )
{
    return dynamic_cast<logstreambuf*>(std::streambuf::setbuf(s,n));
}

///Set internal position pointer to relative position
std::streampos logstreambuf::seekoff ( std::streamoff off, std::ios_base::seekdir way, std::ios_base::openmode which )
{
    return std::streambuf::seekoff (off,way,which);
}

///Set internal position pointer to absolute position
std::streampos logstreambuf::seekpos ( std::streampos sp, std::ios_base::openmode which )
{
    return std::streambuf::seekpos (sp,which);
}

///Synchronize stream buffer
int logstreambuf::sync ( )
{
    return std::streambuf::sync();
}


///Input functions (get)
///Get number of characters available in the sequence
std::streamsize logstreambuf::showmanyc ( )
{
    return std::streambuf::showmanyc();
}

///Get sequence of characters
std::streamsize logstreambuf::xsgetn ( char * s, std::streamsize n )
{
    return std::streambuf::xsgetn(s,n);
}
///Get character in the case of underflow
int logstreambuf::underflow ( )
{
    return std::streambuf::underflow();
}
///Get character in the case of underflow and advance get pointer
int logstreambuf::uflow ( )
{
    return std::streambuf::uflow();
}
///Put character back in the case of backup underflow
int logstreambuf::pbackfail ( int c )
{
    return std::streambuf::pbackfail(c);
}



///Output functions (put)
///Write sequence of characters
std::streamsize logstreambuf::xsputn ( const char * s, std::streamsize n )
{
    return std::streambuf::xsputn ( s , n);
}
///Write character in the case of overflow
int logstreambuf::overflow ( int c )
{
    return std::streambuf::overflow (c);
}

} //Core
