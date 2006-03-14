#ifndef SDLRWOPS_HH
#define SDLRWOPS_HH

#include "SDLConfig.hh"

namespace RAGE
{
    namespace SDL
    {


        /**
        * \class RWOps
        *
        * \ingroup RWOps
        *
        * \brief This class is a wrapper for RWOps
        *
        * \author Alex
        *
        * \date 2006/03/11
        *
        * Contact: asmodehn@gna.org
        *
        */


        class RWOps
        {

			typedef enum {Set = SEEK_SET, Cur = SEEK_CUR, End = SEEK_END }Seek;

			SDL_RWops * _rwops;
		protected:
			RWOps() throw (std::logic_error);
		public:
			RWOps(const std::string & file, const char *mode) throw (std::logic_error);
			RWOps(FILE *fp, int autoclose) throw (std::logic_error);
			RWOps(void *mem, int size) throw (std::logic_error);
			RWOps(const void *mem, int size) throw (std::logic_error);
			~RWOps();

			/*int Seek(int offset,Seek start);
			Tell();
			read();
			write();
			close();*/
        };

    }

}

#endif
