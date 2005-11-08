#ifndef SDLCDROM_HH
#define SDLCDROM_HH

#include "SDLConfig.hh"

namespace SDL
{

    class CDRom
    {
        SDL_CD * m_drive;

    public:
        static inline int numDrives(void)
        {
            return SDL_CDNumDrives();
        }

        CDRom(int drive = 0) throw (std::logic_error);
        ~CDRom(void);
    };


}
#endif
