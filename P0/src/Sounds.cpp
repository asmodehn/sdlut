#include "Sounds.hh"

//SFXs
Sound EscMenuButtonFx = Sound("Data/SFXs/esc_menu_sound.wav");
Sound MissFx = Sound("Data/SFXs/Miss.wav");
Sound HitFx = Sound("Data/SFXs/Hit.wav");
Sound BowFx = Sound("Data/SFXs/Bow.wav");
Sound SwordFx = Sound("Data/SFXs/Sword.wav");

//Musics
Music GlobalMusic = Music("Data/Musics/Temple.wav");

//Initial Sounds infos
int ALL_SOUNDS_VOLUME = 100, SFXS_VOLUME = 100, MUSIC_VOLUME = 100, VOICE_VOLUME = 100, VIDEO_VOLUME = 100, INTERFACE_VOLUME = 100;
bool ENABLE_ALL_SOUNDS = 1, ENABLE_SFXS_SOUNDS = 1, ENABLE_MUSIC_SOUNDS = 1, ENABLE_VOICE_SOUNDS = 1, ENABLE_VIDEO_SOUNDS = 1, ENABLE_INTERFACE_SOUNDS = 1;

//called by the interface to change sounds infos
bool Change_Sounds_Infos()
{
try {
	App::getInstance().getMixer().setMusicVolume(MUSIC_VOLUME);
	SFXS_VOLUME = SFXS_VOLUME;

	return true; //no error

} catch (...) {
    return false; //error occured
}
}
