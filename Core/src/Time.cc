#include "Time.hh"

namespace Core
{

/********** Date ***********/
Date::Date(int year , int month , int mday , int hour , int min , int sec  )
{
    //recomendd for safety
    struct tm zerod = {0} ;

    zerod.tm_sec = sec;
    zerod.tm_min = min;
    zerod.tm_hour = hour;
    zerod.tm_mday = mday;
    zerod.tm_mon = month -1; //month starts at 0;
    zerod.tm_year = year -1900; //year starts at 1900 ( EPOCH )

    d = zerod;
}

Date::~Date()
{}


const std::string Date::ascii()
{
    return std::string(asctime(&d));
}

Time Date::mkTime()
{
    return Time(mktime( &d));
}

/************ Time *************/

Time::Time()
{
    time(&tt);
}

Time::Time( Date & d )
{

    tt = mktime (& d.d);

}

Time::~Time()
{
}

void Time::sleep (unsigned int sec)
{

#ifdef _WIN32
    Sleep (sec * 1000);
#else
#  if _POSIX_VERSION > 198808L
    sleep (sec);
#  else
    clock_t start, end;

    end = start = clock ();
    if (start != -1)
    {
        while ((end - start) / CLOCKS_PER_SEC < sec)
        {
            //That uses system resources, better solution should be possible
            end = clock ();
        }
    }
#  endif /* _POSIX_VERSION */
#endif /* _WIN32 */
}

unsigned long Time::clock (bool sec)
{

    clock_t clk = clock();

    //0 is an error code here : information not availalbe
    unsigned long res = 0;

    if ( clk != -1 )
    {
        res = (unsigned long)clk;
        if ( sec)
        {
            res= (unsigned long) (res/ CLOCKS_PER_SEC) ;
        }
    }
    //lk == -1 -> information nto available we return 0

    return res;
}

Time Time::now()
{
    return Time(time(NULL));

}

std::string Time::localascii()
{
    return std::string(ctime( & tt ) );
}

Date Time::GMT()
{
    Date gmt(gmtime( & tt ));
    return gmt;
}


Date Time::local()
{
    Date loc(localtime( & tt ));
    return loc;
}

}//Core
