#ifndef LOGSTREAM_HH
#define LOGSTREAM_HH

#include "Core/Logging/logstreambuf.hh"


namespace Core
{

/**
 * \class logstream
 * \brief logstream provide log-style formatting in a stream
 *
 */

class logstream : public std::ostream
{
protected:

public :

/// user pass a streambuf as in normal ostream
    explicit logstream (std::streambuf * sb);
    ~logstream();

///Formatted output
///Insert data with format (public member function)
    logstream& operator<< (bool& val );
    logstream& operator<< (short& val );
    logstream& operator<< (unsigned short& val );
    logstream& operator<< (int& val );
    logstream& operator<< (unsigned int& val );
    logstream& operator<< (long& val );
    logstream& operator<< (unsigned long& val );
    logstream& operator<< (float& val );
    logstream& operator<< (double& val );
    logstream& operator<< (long double& val );
    logstream& operator<< (const void* val );

    logstream& operator<< (logstreambuf* sb );

    logstream& operator<< (logstream& ( *pf )(logstream&));
    logstream& operator<< (std::ostream& ( *pf )(std::ostream&));
    logstream& operator<< (std::ios& ( *pf )(std::ios&));
    logstream& operator<< (std::ios_base& ( *pf )(std::ios_base&));


    ///Unformatted output
    ///Put character (public member function)
    logstream& put ( char c );
    ///Write block of data (public member function)
    logstream& write ( const char* s , std::streamsize n );


    ///Positioning
    ///Get position of put pointer (public member function)
    std::streampos tellp ( );
    ///Set position of put pointer (public member function)
    logstream& seekp ( std::streampos pos );
    logstream& seekp ( std::streamoff off, std::ios_base::seekdir dir );

    ///Synchronization
    ///Flush output stream buffer (public member function)
    logstream& flush ( );


    ///Prefix/Suffix:
    ///Perform exception safe prefix/suffix operations (public member classes)
    class sentry : public std::ostream::sentry
    {
    public:
        explicit sentry ( std::ostream& os );
        ~sentry();
        operator bool() const;
    private:
        sentry (const sentry&);             // not defined
        sentry& operator= (const sentry& ); // not defined
    };


};

logstream& operator<< (logstream& out, char c );
logstream& operator<< (logstream& out, signed char c );
logstream& operator<< (logstream& out, unsigned char c );

logstream& operator<< (logstream& out, const char* s );
logstream& operator<< (logstream& out, const signed char* s );
logstream& operator<< (logstream& out, const unsigned char* s );





} //Core



#endif // LOGSTREAM_HH


