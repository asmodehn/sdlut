#include "SDLOverlay.hh"

namespace SDL {
	
Overlay::Format Overlay::getFormat(void) const
{
	Format res;
	if ( _overlay->format & SDL_YV12_OVERLAY ) res = YV12;
	else if ( _overlay->format & SDL_IYUV_OVERLAY ) res = IYUV;
	else if ( _overlay->format & SDL_YUY2_OVERLAY ) res = YUY2;
	else if ( _overlay->format & SDL_UYVY_OVERLAY ) res = UYVY;
	else if ( _overlay->format & SDL_YVYU_OVERLAY ) res = YVYU;
	return res;
}

} //namespace SDL
