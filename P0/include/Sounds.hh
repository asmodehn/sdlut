#ifndef Sounds_HH
#define Sounds_HH

#include "SDL.hh"

using namespace RAGE;
using namespace RAGE::SDL;

//Channel of the null sound (the default chan)
const int NullSound_Chan = 0;

//Fx Channels
extern int EscMenuButtonFx_Chan;
extern int MissFx_Chan;
extern int HitFx_Chan;
extern int BowFx_Chan;
extern int SwordFx_Chan;

//Music Channels
extern int GlobalMusic_Chan;

//Methods
bool Set_Sounds_Channels();


#endif
