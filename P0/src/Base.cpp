#include "Base.hh"

//To check colission (small beginning of a physical engine^^)
bool check_collision(const Rect& A, const Rect& B)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.getx();
    rightA = A.getx() + A.getw();
    topA = A.gety();
    bottomA = A.gety() + A.geth();
        
    //Calculate the sides of rect B
    leftB = B.getx();
    rightB = B.getx() + B.getw();
    topB = B.gety();
    bottomB = B.gety() + B.geth();
            
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}
//random function between min and max
int random(int min, int max)
{
	//srand( (unsigned)time( NULL ) );
	return min + (rand()%(max+1-min));
}

std::string Int_To_String(const int &to_convert)
{
	std::stringstream s;
    if (s << to_convert) // conversion worked
        return s.str();

	//failed
	return NULL;
}

int String_To_Int(const std::string &to_convert)
{
	int res = 0;
	std::stringstream(to_convert) >> res;
	return res;
}

//Style the time to "Xd Xh Xmin Xs"
std::string Time_Style(const int& time)
{
	int day=0, hour=0, minute=0, second=0;
	
	if (time < 60)
	{
		return Int_To_String(time) + "s";
	} else if ( (time >= 60) && (time < 3600) ) 
	{
		minute = (int)(time / 60);
		second = time - (minute*60);
		return Int_To_String(minute) + "mn " + Int_To_String(second) + "s";
	} else if ( (time >=3600) && (time < 86400) )
	{
		hour = (int)(time / 3600);
		minute = (int)( (time - (hour*3600))/60 );
		second = time - (hour*3600) - (minute*60);
		return Int_To_String(hour) + "hr " + Int_To_String(minute) + "mn " + Int_To_String(second) + "s";
	} else if (time >=86400)
	{
		day = (int)(time / 86400);
		hour = (int)( (time - (day*86400))/3600);
		minute = (int) ( (time -(day*86400) -(hour*3600))/60);
		second = time -(day*86400) -(hour*3600) -(minute*60);
		return Int_To_String(day) + "day " + Int_To_String(hour) + "hr " + Int_To_String(minute) + "mn " + Int_To_String(second) + "s";

	}

	return NULL; //error
}
