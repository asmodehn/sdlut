#include "SDLConfig.hh"

//used once, but may be deleted at the end if nothing here ;)

//Logger always enabled..
namespace SDL {
Logger* Config::_log=new Logger("SDLwrap");
}

