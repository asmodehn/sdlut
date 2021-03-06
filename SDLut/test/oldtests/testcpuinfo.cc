
/* Test program to check SDL's CPU feature detection */

#include <stdio.h>

//TODO : MINIMUM VERSION TO BUILD THIS TEST...


#include "SDL.hh"

using namespace std;
using namespace RAGE;

int main(int argc, char *argv[])
{

#if SDL_VERSION_ATLEAST(1, 2, 7)
	cout << "RDTSC " << (SDL::CPU::hasRDTSC() ? "detected" : "not detected")<< std::endl;
	cout << "MMX " <<  (SDL::CPU::hasMMX() ? "detected" : "not detected" )<< std::endl;
	cout << "MMX Ext" <<  (SDL::CPU::hasMMXExt() ? "detected" : "not detected")<< std::endl;
	cout << "3DNow " << (SDL::CPU::has3DNow() ? "detected" : "not detected")<< std::endl;
	cout << "3DNow Ext " << (SDL::CPU::has3DNowExt() ? "detected" : "not detected")<< std::endl;
	//1.2.9 needed for this one ?
	//cout << "SSE " << (SDL::CPU::hasSSE() ? "detected" : "not detected")<< std::endl;
	//cout << "SSE2 " << (SDL::CPU::hasSSE2() ? "detected" : "not detected")<< std::endl;
	cout << "AltiVec " << (SDL::CPU::hasAltiVec() ? "detected" : "not detected")<< std::endl;

#else

	cout << "Your SDL compiled version: " << SDL::App::getInstance().getVersion().getcompiledmajor() << "." << SDL::App::getInstance().getVersion().getcompiledminor() << "." << SDL::App::getInstance().getVersion().getcompiledpatch() << " doesnt support the cpuInfo feature." << std::endl;
#endif
	return(0);
}
