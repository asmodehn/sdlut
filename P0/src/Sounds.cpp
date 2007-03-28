#include "Sounds.hh"

//init each chan to the default chan
	//sfxs
int EscMenuButtonFx_Chan = NullSound_Chan;
int MissFx_Chan = NullSound_Chan;
int HitFx_Chan = NullSound_Chan;
int BowFx_Chan = NullSound_Chan;
int SwordFx_Chan = NullSound_Chan;

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
	Sound MissFx("Datas/SFXs/Miss.wav");
	Sound HitFx("Datas/SFXs/Hit.wav");
	Sound BowFx("Datas/SFXs/Bow.wav");
	Sound SwordFx("Datas/SFXs/Sword.wav");

	//Set Fxs Channels
	EscMenuButtonFx_Chan = App::getInstance().getMixer()->mixSound(EscMenuButtonFx, false, false);
	MissFx_Chan = App::getInstance().getMixer()->mixSound(MissFx, false, false);
	HitFx_Chan = App::getInstance().getMixer()->mixSound(HitFx, false, false);
	BowFx_Chan = App::getInstance().getMixer()->mixSound(BowFx, false, false);
	SwordFx_Chan = App::getInstance().getMixer()->mixSound(SwordFx, false, false);

	//Load Musics Sounds
	Sound GlobalMusic("Datas/Musics/Temple.wav");

	//Set Musics Channels
	GlobalMusic_Chan = App::getInstance().getMixer()->mixSound(GlobalMusic, true, false);

	return true; //no error

} catch (...) {
    return false; //error occured
}
}
