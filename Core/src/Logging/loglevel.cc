#include "Core/Logging/loglevel.hh"

namespace Core {
    namespace loglevel {
std::ostream& operator<<( std::ostream& os, const Level& lvl )
{
   switch( lvl )
   {
      case FATAL: os << "FTL"; break;
      case ERROR: os << "ERR"; break;
      case WARNING: os << "WRN"; break;
      case INFO: os << "INF"; break;
      case DEBUG: os << "DBG"; break;
   }
   return os;
}

    } //loglevel
}//Core
