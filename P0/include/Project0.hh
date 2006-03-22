#ifndef Project0_HH
#define Project0_HH

#include "Monster.hh"
#include "Character_Base.hh"
#include "Monster_Factory.hh"
#include "Input_Management.hh"

//Gnerate Background
void generate_bg(VideoSurface* Screen_Surface);
//Initialization
bool InitEverything();
//Load Images Files
void Load_Files();
//Clean Up Surface
void Clean_Up();


#endif
