#include "Core/Logging/logstream.hh"

namespace Core
{

logstream::logstream ()
        : std::ostream(0)
{
    //to hook up to usual stream design
    pvm_lsb = new logstreambuf();
    this->init(pvm_lsb);

    //setup default flags
    this->flags ( std::ios::left | std::ios::hex | std::ios::showbase | std::ios::boolalpha );

    //setup default prefix
    resetprefix();

}

logstream::~logstream()
{
    delete pvm_lsb;
}

//to manage prefix
void logstream::resetprefix(std::string newprefix)
{
    ptm_prefix = newprefix;
    pvm_lsb->resetprefix(&ptm_prefix);
}

std::string logstream::getprefix() const
{
    return ptm_prefix;
}


logstream& operator<<(logstream &ls, loglevel::Level lvl)
{
    if ( ls.getLevel() >= lvl )
    {
        ls.rdbuf()->filterin();
        //dynamic casting to call the ostream << ( ostream, loglevel) operator
        dynamic_cast<std::ostream&>(ls) << lvl;
    }
    else
    {
        ls.rdbuf()->filterout();
    }
    return ls ;
}

logstream& logstream::level(loglevel::Level l)
{
    *this << l;
    return *this;
}

} // Core


