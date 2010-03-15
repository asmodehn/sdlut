#include "Video/internal/SDLOverlay.hh"
#include "SDLConfig.hh"

namespace RAGE
{
namespace SDL
{

unsigned long Overlay::formatConvert(Format f )
{
    unsigned long format = 0;
    switch (f)
    {
    case YV12 :
        format = SDL_YV12_OVERLAY;
        break;
    case IYUV :
        format = SDL_IYUV_OVERLAY;
        break;
    case YUY2 :
        format = SDL_YUY2_OVERLAY;
        break;
    case UYVY :
        format = SDL_UYVY_OVERLAY;
        break;
    case YVYU :
        format = SDL_YVYU_OVERLAY;
        break;
    default :
        break;//should not happen
    }
    return format;
}

//Constructor
//maybe the current display size must be used ?
Overlay::Overlay(Format f, int width, int height, VideoSurface* dsurf)
        : _overlay( SDL_CreateYUVOverlay( width, height, formatConvert(f), const_cast<SDL_Surface*>(&dsurf->get_rSDL()) ) )
{}
//Destructor
Overlay::~Overlay()
{
    SDL_FreeYUVOverlay(_overlay);
}


Overlay::Format Overlay::getFormat(void) const
{
    Format res; //TOOD : find a sensible default value
    if ( _overlay->format & SDL_YV12_OVERLAY )
        res = YV12;
    else if ( _overlay->format & SDL_IYUV_OVERLAY )
        res = IYUV;
    else if ( _overlay->format & SDL_YUY2_OVERLAY )
        res = YUY2;
    else if ( _overlay->format & SDL_UYVY_OVERLAY )
        res = UYVY;
    else if ( _overlay->format & SDL_YVYU_OVERLAY )
        res = YVYU;
    return res;
}


int Overlay::getHeight(void) const
{
    return _overlay->w;
}
int Overlay::getWidth(void) const
{
    return _overlay->h;
}
int Overlay::getPlanes(void) const
{
    return _overlay->planes;
}
bool Overlay::isHWAccel(void) const
{
    return _overlay->hw_overlay;
}

//locks
bool Overlay::lock(void)
{
    return SDL_LockYUVOverlay(_overlay)==0;
}
void Overlay::unlock(void)
{
    SDL_UnlockYUVOverlay(_overlay);
}


bool Overlay::display(Rect r)
{
    return SDL_DisplayYUVOverlay(_overlay,const_cast<SDL_Rect*>(r.get_pSDL())) == 0;
}
}
} //namespace RAGE::SDL

