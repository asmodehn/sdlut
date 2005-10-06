//test program
#include "AML.hh"

//tmp : logger is aimed only for internal use in AML
#include "Logger.hh"

//would be nice if we can put that in AML.hh
#ifdef __MINGW32__
#ifdef main
#undef main
#endif
#endif


int main(int argc, char* argv [] )
{
	
		Logger testlog;
		
		//mandatory call to initialize
		Config conf;
		
		//creating the display
		Display screen;
		
		testlog.add ("Display created");
		
		return 0;
}


