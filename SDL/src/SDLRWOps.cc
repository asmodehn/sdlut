#include "SDLRWOps.hh"

namespace RAGE {
	namespace SDL{

		RWOps::RWOps() throw (std::logic_error)
		try : _rwops(NULL)
		{
			if(NULL==(_rwops=SDL_AllocRW()))
				throw std::logic_error("Initialising empty RWOps failed");

		}
		catch (std::exception & e)
		{
			Log << "Exception cought in RWOps Constructor : " << e.what();
		};


		RWOps::RWOps(const std::string & file, const char *mode) throw (std::logic_error)
				try : _rwops(NULL)
		{
			if(NULL==(_rwops=SDL_RWFromFile(file.c_str(),mode)))
				throw std::logic_error("Initialising RWOps from " + file +" failed");

		}
		catch (std::exception & e)
		{
			Log << "Exception cought in RWOps Constructor : " << e.what();
		};

		RWOps::RWOps(FILE *fp, int autoclose) throw (std::logic_error)
				try : _rwops(NULL)
		{
			if(NULL==(_rwops=SDL_RWFromFP(fp,autoclose)))
				throw std::logic_error("Initialising RWOps from FP failed");

		}
		catch (std::exception & e)
		{
			Log << "Exception cought in RWOps Constructor : " << e.what();
		};

		RWOps::RWOps(void *mem, int size) throw (std::logic_error)
			try : _rwops(NULL)
		{
			if(NULL==(_rwops=SDL_RWFromMem(mem,size)))
				throw std::logic_error("Initialising RWOps from mem failed");

		}
		catch (std::exception & e)
		{
			Log << "Exception cought in RWOps Constructor : " << e.what();
		};
		
		RWOps::RWOps(const void *mem, int size) throw (std::logic_error)
			try : _rwops(NULL)
		{
			if(NULL==(_rwops=SDL_RWFromConstMem(mem,size)))
				throw std::logic_error("Initialising RWOps from const mem failed");

		}
		catch (std::exception & e)
		{
			Log << "Exception cought in RWOps Constructor : " << e.what();
		};

		RWOps::~RWOps()
		{
			SDL_FreeRW(_rwops);
		}

		bool RWOps::dumpCode(const std::string & filename, const std::string & id)
		{
			
			std::ofstream dumpfile(filename.c_str());

			dumpfile << "const unsigned char "<< id <<"[] = {";

			const char HexTable[] = "0123456789abcdef";
			const int BytesPerLine = 20;
			
			
			//getting length of the RWOps in memory
			unsigned int length=SDL_RWseek(_rwops,0,SEEK_END);
			
			unsigned char* ch = new unsigned char[length];
			//reading 16-bytes blocks (arbitrary choice...
			int bytes = SDL_RWread( _rwops, ch ,16,length/16) ;

			
			for (int i=0 ; i< bytes; i++)
			{
				if ( bytes % BytesPerLine == 0 )
					dumpfile << "\n\t";
				dumpfile << "'\\x";
				dumpfile.put(HexTable[ ( (ch[i]) >> 4 ) & 0x0f ]);
				dumpfile.put(HexTable[ (ch[i]) & 0x0f ]);
				dumpfile << "',";
				bytes ++;
			}

			dumpfile << "\n};" << std::endl;
			
			dumpfile.close();
			return true;
		}


	}
}