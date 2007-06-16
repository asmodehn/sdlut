#include "Sounds.hh"

//SFXs
auto_ptr<Sound> EscMenuButtonFx(0);
auto_ptr<Sound> MissFx(0);
auto_ptr<Sound> HitFx(0);
auto_ptr<Sound> BowFx(0);
auto_ptr<Sound> SwordFx(0);

//Musics
auto_ptr<Music> GlobalMusic(NULL);

//Initial Sounds infos
int ALL_SOUNDS_VOLUME = 100, SFXS_VOLUME = 100, MUSIC_VOLUME = 100, VOICE_VOLUME = 100, VIDEO_VOLUME = 100, INTERFACE_VOLUME = 100;
bool ENABLE_ALL_SOUNDS = 1, ENABLE_SFXS_SOUNDS = 1, ENABLE_MUSIC_SOUNDS = 1, ENABLE_VOICE_SOUNDS = 1, ENABLE_VIDEO_SOUNDS = 1, ENABLE_INTERFACE_SOUNDS = 1;

//initialize all sounds & musics
void Init_Sounds_And_Musics()
{
try {
	//SFXs
	EscMenuButtonFx.reset( new Sound("Data/SFXs/esc_menu_sound.wav") );
	MissFx.reset(new Sound("Data/SFXs/Miss.wav"));
	HitFx.reset(new Sound("Data/SFXs/Hit.wav"));
	BowFx.reset(new Sound("Data/SFXs/Bow.wav"));
	SwordFx.reset(new Sound("Data/SFXs/Sword.wav"));

	//Musics
	GlobalMusic.reset(new Music("Data/Musics/Temple.wav", true ));

} catch (std::exception &exc) {
	throw std::logic_error( "From Init_Sounds_And_Musics(), " + (string)exc.what() );
} catch (...) {
	throw std::logic_error("Unhandled Error In Init_Sounds_And_Musics()");  
}
}

//called by the interface to change sounds infos
void Change_Sounds_Infos()
{
try {
	App::getInstance().getMixer().setMusicVolume(MUSIC_VOLUME);
	SFXS_VOLUME = SFXS_VOLUME;

} catch (std::exception &exc) {
	throw std::logic_error( "From Change_Sounds_Infos(), " + (string)exc.what() );
} catch (...) {
	throw std::logic_error("Unhandled Error In Change_Sounds_Infos()");  
}
}
