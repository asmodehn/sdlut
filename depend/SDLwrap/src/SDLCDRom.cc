#include "SDLCDRom.hh"

namespace SDL
{

    CDRom::CDRom(int drive ) throw (std::logic_error)
    try
    :
        m_drive(SDL_CDOpen(drive))
    {
        // Check for the CD drive
        if(SDL_CDNumDrives() < drive)
        {
            std::string errstr("the CDROM device number ");
            errstr+= drive + " is not available";
            throw std::logic_error(errstr);
        }
        /* Did if open? Check if cdrom is NULL */
        if(m_drive==NULL)
        {
            std::string errstr("Couldn't open drive number: ");
            errstr+= SDL_GetError();
            throw std::logic_error(errstr);
        }
    }
    catch (std::exception & e)
    {
        Config::addLog( e.what() );
    }

    CDRom::~CDRom()
    {
        SDL_CDClose(m_drive);
    }
}
