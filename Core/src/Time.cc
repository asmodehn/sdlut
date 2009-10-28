#include "Time.hh"


void sleep (unsigned int sec)
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
            end = clock ();
        }
    }
#  endif /* _POSIX_VERSION */
#endif /* _WIN32 */
}




