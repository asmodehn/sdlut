#include "Sounds.hh"

//init each chan to the default chan
	//sfxs
int EscMenuButtonFx_Chan = NullSound_Chan;

	//musics
int GlobalMusic_Chan = NullSound_Chan;

bool Set_Sounds_Channels()
{
try {
	//define the null sound
	Sound NullSound("Datas/SFXs/null.wav");

	//Set the null sound to the channel 0 (the 1st one)
	if (App::getInstance().getMixer()->mixSound(NullSound, false, false) != 0)
	{
		return false; //Error: NULL Sound was not mix to the channel 0, impossible !?!
	}

	//Load Fxs Sounds
	Sound EscMenuButtonFx("Datas/SFXs/esc_menu_sound.wav");

	//Set Fxs Channels
	EscMenuButtonFx_Chan = App::getInstance().getMixer()->mixSound(EscMenuButtonFx, false, false);

	//Load Musics Sounds
	Sound GlobalMusic("Datas/Musics/Global Music.wav");

	//Set Musics Channels
	GlobalMusic_Chan = App::getInstance().getMixer()->mixSound(GlobalMusic, true, false);

	return true; //no error

} catch (...) {
    return false; //error occured
}
}
