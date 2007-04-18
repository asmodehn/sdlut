#include "SDLRWOps.hh"
#include "SDLConfig.hh"

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
		}


		RWOps::RWOps(const std::string & file, const char *mode) throw (std::logic_error)
				try : _rwops(NULL)
		{
			if(NULL==(_rwops=SDL_RWFromFile(file.c_str(),mode)))
				throw std::logic_error("Initialising RWOps from " + file +" failed" + GetError());

		}
		catch (std::exception & e)
		{
			Log << "Exception cought in RWOps Constructor : " << e.what();
		}

		//RWOps::RWOps(FILE *fp, int autoclose) throw (std::logic_error)
		//		try : _rwops(NULL)
		//{
		//	if(NULL==(_rwops=SDL_RWFromFP(fp,autoclose)))
		//		throw std::logic_error("Initialising RWOps from FP failed");

		//}
		//catch (std::exception & e)
		//{
		//	Log << "Exception cought in RWOps Constructor : " << e.what();
		//};

		RWOps::RWOps(void *mem, int size) throw (std::logic_error)
			try : _rwops(NULL)
		{
			if(NULL==(_rwops=SDL_RWFromMem(mem,size)))
				throw std::logic_error("Initialising RWOps from mem failed");

		}
		catch (std::exception & e)
		{
			Log << "Exception cought in RWOps Constructor : " << e.what();
		}
		
		RWOps::RWOps(const void *mem, int size) throw (std::logic_error)
			try : _rwops(NULL)
		{
			if(NULL==(_rwops=SDL_RWFromConstMem(mem,size)))
				throw std::logic_error("Initialising RWOps from const mem failed");

		}
		catch (std::exception & e)
		{
			Log << "Exception cought in RWOps Constructor : " << e.what();
		}

		SDL_RWops RWOps::get_SDL() const
		{
			return *_rwops;
		}

		const SDL_RWops * RWOps::get_pSDL() const
		{
			return _rwops;
		}
		
		RWOps::~RWOps()
		{
			SDL_FreeRW(_rwops);
		}


		int RWOps::tell() const
		{
			return SDL_RWtell(_rwops);
		}
		
		int RWOps::seek(int offset,Seek start)
		{
			int newoffset = 0;
			switch(start)
			{
			case Set:
				newoffset = SDL_RWseek(_rwops,offset,SEEK_SET);
				break;
			case Cur:
				newoffset = SDL_RWseek(_rwops,offset,SEEK_CUR);
				break;
			case End:
				newoffset = SDL_RWseek(_rwops,offset,SEEK_END);
				break;
			}
			return newoffset;
		}

		bool RWOps::close()
		{
			return SDL_RWtell(_rwops) == 0;
		}

		bool RWOps::dumpCode(const std::string & filename, const std::string & id)
		{
			
			std::ofstream dumpfile(filename.c_str());

			
			const char HexTable[] = "0123456789abcdef";
			const int BytesPerLine = 20;
			
			
			//getting length of the RWOps in memory
			unsigned int length=SDL_RWseek(_rwops,0,SEEK_END);
			SDL_RWseek(_rwops,0,SEEK_SET);
			
			unsigned char* ch = new unsigned char[length];
			//reading 16-bytes blocks (arbitrary choice...)
			int blocks = SDL_RWread( _rwops, ch ,16,length/16) ;

#ifdef DEBUG
			Log << nl << blocks << " 16-bytes blocks read";
#endif

			dumpfile << "const unsigned char "<< id <<"["<< length <<"] = {";

			for (int i=0 ; i< blocks * 16; i++)
			{
				if ( i % BytesPerLine == 0 )
					dumpfile << "\n\t";
				dumpfile << "'\\x";
				dumpfile.put(HexTable[ ( (ch[i]) >> 4 ) & 0x0f ]);
				dumpfile.put(HexTable[ (ch[i]) & 0x0f ]);
				dumpfile << "',";
			}

			dumpfile << "\n};" << std::endl;
			
			dumpfile.close();
			return true;
		}


	}
}
