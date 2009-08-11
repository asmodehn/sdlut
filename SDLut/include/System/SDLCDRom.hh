#ifndef SDL_CDROM_HH
#define SDL_CDROM_HH

#include <stdexcept>

struct SDL_CD;

namespace RAGE
{
namespace SDL
{

class CDRom
{
    SDL_CD * m_drive;

public:
    static int numDrives(void);

    CDRom(int drive = 0) throw (std::logic_error);
    ~CDRom(void);
};

}
}
#endif
