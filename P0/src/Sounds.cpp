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
	//Set the null sound to the channel 0 (the 1st one)
	if (App::getInstance().getMixer()->mixSound(Sound("Data/SFXs/null.wav"), false, false) != 0)
	{
		return false; //Error: NULL Sound was not mix to the channel 0, impossible !?!
	}

	//Set Fxs Channels
	EscMenuButtonFx_Chan = App::getInstance().getMixer()->mixSound(Sound("Data/SFXs/esc_menu_sound.wav"), false, false);
	MissFx_Chan = App::getInstance().getMixer()->mixSound(Sound("Data/SFXs/Miss.wav"), false, false);
	HitFx_Chan = App::getInstance().getMixer()->mixSound(Sound("Data/SFXs/Hit.wav"), false, false);
	BowFx_Chan = App::getInstance().getMixer()->mixSound(Sound("Data/SFXs/Bow.wav"), false, false);
	SwordFx_Chan = App::getInstance().getMixer()->mixSound(Sound("Data/SFXs/Sword.wav"), false, false);

	//Set Musics Channels
	GlobalMusic_Chan = App::getInstance().getMixer()->mixSound(Sound("Data/Musics/Temple.wav"), true, false);

	return true; //no error

} catch (...) {
    return false; //error occured
}
}

bool Clean_Sounds_Channels()
{
try {
	App::getInstance().getMixer()->freeChannel(NullSound_Chan);

	App::getInstance().getMixer()->freeChannel(EscMenuButtonFx_Chan);
	App::getInstance().getMixer()->freeChannel(MissFx_Chan);
	App::getInstance().getMixer()->freeChannel(HitFx_Chan);
	App::getInstance().getMixer()->freeChannel(BowFx_Chan);
	App::getInstance().getMixer()->freeChannel(SwordFx_Chan);

	App::getInstance().getMixer()->freeChannel(GlobalMusic_Chan);

return true; //no error

} catch (...) {
    return false; //error occured
}
}
