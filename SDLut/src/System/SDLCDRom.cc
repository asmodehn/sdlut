#include "System/SDLCDRom.hh"
#include "SDLConfig.hh"

namespace RAGE
{
namespace SDL
{

int CDRom::numDrives(void)
{
    return SDL_CDNumDrives();
}

CDRom::CDRom(int drive ) throw (std::logic_error)
try
:
    m_drive(SDL_CDOpen(drive))
{
    // Check for the CD drive
    if (SDL_CDNumDrives() < drive)
    {
        std::string errstr("the CDROM device number ");
        errstr+= drive + " is not available";
        throw std::logic_error(errstr);
    }
    /* Did if open? Check if cdrom is NULL */
    if (m_drive==NULL)
    {
        std::string errstr("Couldn't open drive number: ");
        errstr+= SDL_GetError();
        throw std::logic_error(errstr);
    }
}
catch (std::exception & e)
{
    Log << e.what() << std::endl;
}

CDRom::~CDRom()
{
    SDL_CDClose(m_drive);
}
}
}
