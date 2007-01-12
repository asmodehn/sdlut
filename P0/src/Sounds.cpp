#include "Sounds.hh"

//init each chan to the default chan
int EscMenuButtonFx_Chan = NullSound_Chan;


bool Set_Fx_Sound_Channels()
{
try {
	//define the null sound
	Sound NullSound("Datas/SFXs/null.wav", false);

	//Set the null sound to the channel 0 (the 1st one)
	if (App::getInstance().getMixer()->mixSound(NullSound, false) != 0)
	{
		return false; //Error: NULL Sound was not mix to the channel 0, impossible !?!
	}

	//Load Fxs Sounds
	Sound EscMenuButtonFx("Datas/SFXs/esc_menu_sound.wav", false);

	//Set Fxs Channels
	EscMenuButtonFx_Chan = App::getInstance().getMixer()->mixSound(EscMenuButtonFx, false);

	return true; //no error

} catch (...) {
    return false; //error occured
}
}
