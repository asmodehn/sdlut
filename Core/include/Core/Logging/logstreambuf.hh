#ifndef LOGSTREAMBUF_HH
#define LOGSTREAMBUF_HH

#include <cstdio> // for EOF
#include <iostream>
#include <fstream>
#include <sstream>
#include <locale>


namespace Core
{

//we define here logstream and logstreambuf which should integrates well with iostream from STL

/**
 * \class logstreambuf
 *
 * \brief This class defines an overloaded streambuf, to be used with logstream
 * It adds a prefix to each line logged with date and other useful information
 *
 * Custom Prefix (set by logstream) | Date (internally added) | Time (internally added) [| ThreadID (internally added)] | Message ( sent by logstream )
 */

class logstreambuf: public std::streambuf
{
    //prefix pointer. can be 0x0.
    std::string* ptm_prefix;

    //this is the actual streambuffer on which we will redirect calls
    //after some little adjustments if required
    std::stringbuf ptm_buf;

    //IDEA : ptm_buf is a temporary buffer that is accessible just like a stringstream.
    //On flush, the content of the stringbuf is tranferred to clog ( and other sinks )

    //clog as default sink on sync()
    std::streambuf* ptm_clogbuf;

public:
    logstreambuf();
    ~logstreambuf();

//to manage prefix
void resetprefix(std::string *newprefix = 0);
std::string* getprefix() const;

//from stringbuf
std::string str ( ) const { return ptm_buf.str(); }
void str ( const std::string & s ) {return ptm_buf.str(s); }

///Inherited, overload not needed
/*
//The common functionality for all stream buffers is provided through the following public member functions:
//Locales:
///Imbue locale (public member function)
    std::locale pubimbue ( const std::locale & loc );
///Get current locale (public member function)
    std::locale getloc ( ) const;
//Buffer management and positioning:
///Set buffer array (public member function)
    logstreambuf* pubsetbuf ( char* s, std::streamsize n );
///Set internal position pointer to relative position (public member function)
    std::streampos pubseekoff ( std::streamoff off, std::ios_base::seekdir way, std::ios_base::openmode which = std::ios_base::in | std::ios_base::out );
///Set internal position pointer to absolute position (public member function)
    std::streampos pubseekpos ( std::streampos sp, std::ios_base::openmode which = std::ios_base::in | std::ios_base::out );
///Synchronize stream buffer (public member function)
    int pubsync ( );
//Input functions (get):
///Get number of characters available to read (public member function)
    std::streamsize in_avail ( );
///Increase get pointer and return next character (public member function)
    int snextc ( );
///	Get current character and increase get pointer (public member function)
    int sbumpc ( );
///Get current character (public member function)
    int sgetc ( );
///	Get sequence of characters (public member function)
    std::streamsize sgetn ( char * s, std::streamsize n );
///Put character back (public member function)
    int sputbackc ( char c );
///Decrease get pointer (public member function)
    int sungetc ( );
//Output functions (put):
///Store character at current put position and increase put pointer (public member function)
    int sputc ( char c );
///Write a sequence of characters (public member function)
    std::streamsize sputn ( const char * s, std::streamsize n );

*/

protected:

    //BUG : Doesnt com here on test... just like virtual is not working...
    //TOFIX
    ///Locales
    ///Imbue locale (virtual protected member function)
    virtual void imbue ( const std::locale & loc );

    ///Buffer management and positioning
    ///Set buffer
    virtual logstreambuf* setbuf ( char* s, std::streamsize n );
    ///Set internal position pointer to relative position
    virtual std::streampos seekoff ( std::streamoff off, std::ios_base::seekdir way, std::ios_base::openmode which = std::ios_base::in | std::ios_base::out );
    ///Set internal position pointer to absolute position
    virtual std::streampos seekpos ( std::streampos sp, std::ios_base::openmode which = std::ios_base::in | std::ios_base::out );
    ///Synchronize stream buffer
    virtual int sync ( );

    ///for now only output buffer used
    /*
    ///Input functions (get)
    ///Get number of characters available in the sequence
    //virtual std::streamsize showmanyc ( );
    ///Get sequence of characters
    //virtual std::streamsize xsgetn ( char * s, std::streamsize n );
    ///Get character in the case of underflow
    //virtual int underflow ( );
    ///Get character in the case of underflow and advance get pointer
    //virtual int uflow ( );
    ///Put character back in the case of backup underflow
    //virtual int pbackfail ( int c = EOF );
    */

    ///Output functions (put)
    ///Write sequence of characters
    virtual std::streamsize xsputn ( const char * s, std::streamsize n );
    ///Write character in the case of overflow
    //no need here as called by xsputn in members streambuf
    //virtual int overflow ( int c = EOF );


};



}// Core

#endif // LOGSTREAMBUF_HH
