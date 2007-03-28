#ifndef Sounds_HH
#define Sounds_HH

#include "SDL.hh"

using namespace RAGE;
using namespace RAGE::SDL;

//Null sound (the default sound)
extern Sound NullSound;
//Channel of the null sound (the default chan)
const int NullSound_Chan = 0;

//Fxs
extern Sound EscMenuButtonFx;
extern Sound MissFx;
extern Sound HitFx;
extern Sound BowFx;
extern Sound SwordFx;

//Fx Channels
extern int EscMenuButtonFx_Chan;
extern int MissFx_Chan;
extern int HitFx_Chan;
extern int BowFx_Chan;
extern int SwordFx_Chan;

//Musics
extern Sound GlobalMusic;

//Music Channels
extern int GlobalMusic_Chan;

//Methods
bool Set_Sounds_Channels();


#endif
