#ifndef LOGSTREAM_HH
#define LOGSTREAM_HH

#include "Core/Logging/nullstream.hh"
#include "Core/Logging/logstreambuf.hh"
#include "Core/Logging/loglevel.hh"

namespace Core
{

/**
 * \class logstream
 * \brief logstream provide filtering based on loglevel.
 *
 */

class logstream : public std::ostream
{
    //log prefix storage
    std::string ptm_prefix;

    //streambuff
    logstreambuf* pvm_lsb;

    //level of hte log stream.
    //anything less important than this level is ignored
    loglevel::Level loglvl;

public :

    logstream();
    ~logstream();

    //to manage prefix
    void resetprefix(std::string newprefix = "");
    std::string getprefix() const;

    //to use logstream as streamthrough
    friend std::ostream& operator<<(std::ostream& o, logstream& l) { return o << l.rdbuf(); };

    //to be able to access buffer ( after ofstream )
    logstreambuf* rdbuf() const { return pvm_lsb; }
    std::string str ( ) const { return rdbuf()->str(); }
    void str ( const std::string & s ) {return rdbuf()->str(s); }

    ///Unformatted output
    ///Put character (public member function)
    //logstream& put ( char c );
    ///Write block of data (public member function)
    //logstream& write ( const char* s , std::streamsize n );

    ///Synchronization
    ///Flush output stream buffer (public member function)
    ///flush will go to std::clog
    //logstream& flush ( );

    //set loglevel. Messages logged here will have at least this level
    void resetLevel(loglevel::Level l=loglevel::INFO) { loglvl = l; }
    loglevel::Level getLevel() { return loglvl;}

    //manipulator to set *messages's* level
    friend logstream& operator<<(logstream &o, loglevel::Level lvl);
    logstream& level(loglevel::Level l);

};

//overloading standard clog
//CORE_API logstream clog;


} //Core



#endif // LOGSTREAM_HH


