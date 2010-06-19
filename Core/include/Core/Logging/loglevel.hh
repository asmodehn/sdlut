#ifndef CORE_LOGLEVEL_HH
#define CORE_LOGLEVEL_HH

//TODO
// we ned to keep an enum
// we just need to add proper operators around it
//http://www.edm2.com/0405/enumeration.html

#include <ostream>

namespace Core{

    namespace loglevel{


        enum Level {
            FATAL = 0,
            ERROR = 1,
            WARNING = 2,
            INFO = 3,
            DEBUG = 4
        };


//beware ++ means more important that is opposite in integer value in enums
//logleve can not be more important than FATAL (=0)
inline void operator++(Level& lvl) { lvl = (lvl == FATAL)?FATAL:Level(lvl-1); }
inline void operator++(Level& lvl, int) { lvl = (lvl == FATAL)?FATAL:Level(lvl-1); }
//loglevel can be as uninteressant as we want.
inline void operator--(Level& lvl) { lvl = Level(lvl+1); }
inline void operator--(Level& lvl, int) { lvl = Level(lvl+1); }

std::ostream& operator<<( std::ostream& os, const Level& lvl );

    } //loglevel



} //Core



#endif
