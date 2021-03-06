

#ifndef GCN_SDLut_HPP
#define GCN_SDLut_HPP

/*Checking memory leaks with VLD under Win32 only !*/
#ifdef WIN32
#ifdef VLD
#include "vld.h"
#endif
#endif

#include "guichan/sdlut/sdlutgraphics.hpp"
#include "guichan/sdlut/sdlutimage.hpp"
#include "guichan/sdlut/sdlutimageloader.hpp"
#include "guichan/sdlut/sdlutinput.hpp"
#include "guichan/sdlut/sdlutfont.hpp"

#include "guichan/widgets/widget_ImageSlider.hh"

#include "guichan/platform.hpp"

#endif
