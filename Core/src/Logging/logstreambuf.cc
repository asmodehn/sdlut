#include "Core/Logging/logstreambuf.hh"

namespace Core
{

logstreambuf::logstreambuf()
        : std::streambuf(),
        ptm_prefix(0), //default no prefix
        ptm_logdate(true),ptm_logtime(true),
        ptm_buf(), //initializes stringbuffer
        ptm_clogbuf(std::clog.rdbuf())//using clog as sink
        //to hook up to it also :
        //ptm_clogbuf(std::clog.rdbuf(&ptm_buf))
{
}

logstreambuf::~logstreambuf()
{
    //restoring proper streambuffer for clog
    //only if we hooked up to it
    //std::clog.rdbuf(ptm_clogbuf);
}


void logstreambuf::resetprefix(std::string* newprefix)
{
    ptm_prefix = newprefix;
}

std::string* logstreambuf::getprefix() const
{
    return ptm_prefix;
}


//The common functionality for all stream buffers is provided through the following public member functions:
///Inherited, shouldnt be neeeded to overload
/*
//Locales:
///Imbue locale (public member function)
std::locale logstreambuf::pubimbue ( const std::locale & loc )
{
    return ptm_buf.pubimbue(loc);
}
///Get current locale (public member function)
std::locale logstreambuf::getloc ( ) const
{
    return ptm_buf.getloc();
}
//Buffer management and positioning:
///Set buffer array (public member function)
logstreambuf* logstreambuf::pubsetbuf ( char* s, std::streamsize n )
{
    return dynamic_cast<logstreambuf*>(ptm_buf.pubsetbuf(s,n));
}
///Set internal position pointer to relative position (public member function)
std::streampos logstreambuf::pubseekoff ( std::streamoff off, std::ios_base::seekdir way, std::ios_base::openmode which )
{
    return ptm_buf.pubseekoff(off,way,which);
}
///Set internal position pointer to absolute position (public member function)
std::streampos logstreambuf::pubseekpos ( std::streampos sp, std::ios_base::openmode which )
{
    return ptm_buf.pubseekpos(sp,which);
}
///Synchronize stream buffer (public member function)
int logstreambuf::pubsync ( )
{
    return ptm_buf.pubsync();
}
//Input functions (get):
///Get number of characters available to read (public member function)
std::streamsize logstreambuf::in_avail ( )
{
    return ptm_buf.in_avail();
}
///Increase get pointer and return next character (public member function)
int logstreambuf::snextc ( )
{
    return ptm_buf.snextc();
}
///	Get current character and increase get pointer (public member function)
int logstreambuf::sbumpc ( )
{
    return ptm_buf.sbumpc();
}
///Get current character (public member function)
int logstreambuf::sgetc ( )
{
    return ptm_buf.sgetc();
}
///	Get sequence of characters (public member function)
std::streamsize logstreambuf::sgetn ( char * s, std::streamsize n )
{
    return ptm_buf.sgetn (s,n);
}
///Put character back (public member function)
int logstreambuf::sputbackc ( char c )
{
    return ptm_buf.sputbackc(c);
}
///Decrease get pointer (public member function)
int logstreambuf::sungetc ( )
{
    return ptm_buf.sungetc();
}
//Output functions (put):
///Store character at current put position and increase put pointer (public member function)
int logstreambuf::sputc ( char c )
{
    return ptm_buf.sputc(c);
}
///Write a sequence of characters (public member function)
std::streamsize logstreambuf::sputn ( const char * s, std::streamsize n )
{
    return ptm_buf.sputn(s,n);
}

*/

///Locales
///Imbue locale (virtual protected member function)
void logstreambuf::imbue ( const std::locale & loc )
{
    ptm_buf.pubimbue(loc);
}

///Buffer management and positioning
///Set buffer
logstreambuf* logstreambuf::setbuf ( char* s, std::streamsize n )
{
    ptm_buf.pubsetbuf(s,n);
    return this;
}

///Set internal position pointer to relative position
std::streampos logstreambuf::seekoff ( std::streamoff off, std::ios_base::seekdir way, std::ios_base::openmode which )
{
    return ptm_buf.pubseekoff(off,way,which);
}

///Set internal position pointer to absolute position
std::streampos logstreambuf::seekpos ( std::streampos sp, std::ios_base::openmode which )
{
    return ptm_buf.pubseekpos(sp,which);
}

///Synchronizes (flush) the stream buffer
int logstreambuf::sync ( )
{
    int res=0;

          //TODO : insert useful prefixes
       //maybe distinction date / time useless
        char timebuf[80];
        if (ptm_logtime || ptm_logdate)
        {
            time_t rawtime;
            struct tm * timeinfo;

            time ( &rawtime );
            timeinfo = localtime ( &rawtime );
            if ( ptm_logtime && !ptm_logdate)
            {
                strftime (timebuf,80,"%X %Z : ",timeinfo);
            }else if (ptm_logdate && !ptm_logtime)
            {
                strftime (timebuf,80,"%x %Z : ",timeinfo);
            }else if (ptm_logdate && ptm_logtime)
            {
                strftime (timebuf,80,"%x %X %Z : ",timeinfo);
            }
        }

        if (ptm_logtime || ptm_logdate)
        {
            //TODO : speed up with fixed string size
            //passon prefixes strings
            ptm_clogbuf->sputn(timebuf,strlen(timebuf));
        }

    //transfer ptm_buf to clogbuf
    //copy character one by one...
    //maybe better to lock buffer, and get it whole at once...
    char c = ptm_buf.sbumpc();
    while( c != EOF )
    {
        ptm_clogbuf->sputc(c);
        c = ptm_buf.sbumpc();
    }
    ptm_clogbuf->sputc('\n');

    res += ptm_buf.pubsync();
    res += ptm_clogbuf->pubsync();

    return res;
}

/*
///Input functions (get)
///Get number of characters available in the sequence
std::streamsize logstreambuf::showmanyc ( )
{}

///Get sequence of characters
std::streamsize logstreambuf::xsgetn ( char * s, std::streamsize n )
{}
///Get character in the case of underflow
int logstreambuf::underflow ( )
{}
///Get character in the case of underflow and advance get pointer
int logstreambuf::uflow ( )
{}
///Put character back in the case of backup underflow
int logstreambuf::pbackfail ( int c )
{}
*/

///Output functions (put)
///Write sequence of characters
std::streamsize logstreambuf::xsputn ( const char * s, std::streamsize n )
{
    std::streamsize ressize = 0;
    char* laststr = (char*)s;

    //last string
    ressize += ptm_buf.sputn(laststr,strlen(laststr));
    return ressize;
}

} //Core
