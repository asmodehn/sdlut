#ifndef Sounds_HH
#define Sounds_HH

#include "Base.hh"

//FX Sounds
extern Sound EscMenuButtonFx;
extern Sound MissFx;
extern Sound HitFx;
extern Sound BowFx;
extern Sound SwordFx;

//Music Sounds
extern Music GlobalMusic;

//Sounds infos
extern int ALL_SOUNDS_VOLUME;
extern int SFXS_VOLUME;
extern int MUSIC_VOLUME;
extern int VOICE_VOLUME;
extern int VIDEO_VOLUME;
extern int INTERFACE_VOLUME;

extern bool ENABLE_ALL_SOUNDS;
extern bool ENABLE_SFXS_SOUNDS;
extern bool ENABLE_MUSIC_SOUNDS;
extern bool ENABLE_VOICE_SOUNDS;
extern bool ENABLE_VIDEO_SOUNDS;
extern bool ENABLE_INTERFACE_SOUNDS;

//Methods
bool Change_Sounds_Infos();

#endif
