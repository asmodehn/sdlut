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

using namespace std;

int main(int argc, char* argv [] )
{
	
		Logger testlog;
		
		//mandatory call to initialize
		Config::setConfig(true,false,false,false,false);
		
   Sprite * s = new Sprite("../data/spritelib_gpl/paddle/arinoid.bmp");
		//Layer l;
		
    //l.add(s);
		
		
    //creating the display // STILL NOT RIGHT !!!! -> TO INVESTIGATE
		Display screen;
		//1 ) looks like Display must be created before the sprite, otherwise there is no DisplayFormat to optimise the sprite
		//should be handled in sprite constructor... in progress...
		//2 ) error when sprite moves... ->TO INVESTIGATE
		screen.update();
		system("pause");
		//screen is BAD... if we resize it, or timeout windows (app not responding) then it becomes fine... -> to investigate
		
		
		Camera * c=Camera::getCamera(); // has been created by Display
		
		//if not using layer, the sprite has to be attached directly to the camera
		c->add(s);
		//c.add(l);
		
		Vector2 up(100.0,0.0);
		Vector2 down(-100.0,0.0);


		
		testlog.add ("Display created");
		screen.update();
		
		
		
		system("pause");
		cout << "moving sprite up" << endl;
		s->move(up);
		screen.update();
		
		system("pause");
		
		//cout << "moving layer down" << endl;
		//l.move(down);
		screen.update();
		
		system("pause");
		cout << "moving sprite up" << endl;
		s->move(up);
		screen.update();
		
		system("pause");
		cout << "moving camera up" << endl;
		c->move(up);
		screen.update();
		
		system("pause");
		
		

		
		return 0;
}


