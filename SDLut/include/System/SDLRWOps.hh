#ifndef SDLRWOPS_HH
#define SDLRWOPS_HH

#include <fstream>
#include <string>
#include <memory>
#include <stdexcept>

//forward declaration for late time binding...
struct SDL_RWops;

namespace SDLut
{
namespace system
{

/**
* \class RWOps
*
* \ingroup RWOps
*
* \brief This class is a wrapper for RWOps
*
* \author Alex
*
* \date 2006/03/11
*
* Contact: asmodehn@gna.org
*
*/

class RWOps
{
    std::auto_ptr<SDL_RWops> pvm_rwops;

    friend class Sound;

protected:
    RWOps() throw (std::logic_error);
public:
    RWOps(const std::string & file, const char *mode) throw (std::logic_error);

    //this one is not safe to use on Win32 platforms ( dll properties of SDL and libc have to match... tricky heh ?)
    //might be useless to have it then
    //RWOps(FILE *fp, int autoclose) throw (std::logic_error);

    RWOps(void *mem, int size) throw (std::logic_error);
    RWOps(const void *mem, int size) throw (std::logic_error);
    RWOps(const RWOps & rwops) throw (std::logic_error);
    ~RWOps();

    SDL_RWops get_SDL() const;
    inline SDL_RWops & get_rSDL() const
    {
        return *pvm_rwops;
    }
    inline SDL_RWops * get_pSDL() const
    {
        return pvm_rwops.get();
    }

    enum Seek {Set, Cur, End};

    int tell() const;
    int seek(int offset,Seek start);

    //TODO : read();
    //TODO : write();

    bool close();

    //TODO : http://www.xgarreau.org/aide/devel/sdl/rwops.php
    //faire un packer / unpacker similaire...
    bool dumpCode(const std::string & filename, const std::string & id);

    inline friend std::ostream& operator << (std::ostream& os, const RWOps& r)
    {
        return os << std::hex << "RWOps "<< &r << " @ " << r.tell();
    }

};

}

}

#endif
