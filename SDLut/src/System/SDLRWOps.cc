#include "System/SDLRWOps.hh"
#include "SDLConfig.hh"

namespace RAGE
{
namespace SDL
{

RWOps::RWOps() throw (std::logic_error)
try :
    pvm_rwops(SDL_AllocRW())
{
    if (!pvm_rwops.get())
    {
        throw std::logic_error("Initialising empty RWOps failed");
    }

}
catch (std::exception & e)
{
    Log << "Exception cought in RWOps Constructor : " << e.what();
}


RWOps::RWOps(const std::string & file, const char *mode) throw (std::logic_error)
try :
    pvm_rwops(SDL_RWFromFile(file.c_str(),mode))
{
    if (!pvm_rwops.get())
    {
        throw std::logic_error("Initialising RWOps from " + file +" failed" + GetError());
    }

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
try :
    pvm_rwops(SDL_RWFromMem(mem,size))
{
    if (!pvm_rwops.get())
    {
        throw std::logic_error("Initialising RWOps from mem failed");
    }
}
catch (std::exception & e)
{
    Log << "Exception cought in RWOps Constructor : " << e.what();
}

RWOps::RWOps(const void *mem, int size) throw (std::logic_error)
try :
    pvm_rwops(SDL_RWFromConstMem(mem,size))
{
    if (!pvm_rwops.get())
    {
        throw std::logic_error("Initialising RWOps from const mem failed");
    }
}
catch (std::exception & e)
{
    Log << nl <<"Exception cought in RWOps Constructor : " << e.what();
}

SDL_RWops RWOps::get_SDL() const
{
    return *pvm_rwops;
}

RWOps::RWOps(const RWOps & rwops) throw (std::logic_error)
try :
    pvm_rwops(SDL_AllocRW())
{
    if (!pvm_rwops.get())
    {
        throw std::logic_error("Initialising empty RWOps failed");
    }
    if ( rwops.pvm_rwops.get() != 0 )
    {
        *pvm_rwops = *(rwops.pvm_rwops);
    }
}
catch (std::exception & e)
{
    Log << nl <<"Exception cought in RWOps Copy Constructor : " << e.what();
}

RWOps::~RWOps()
{
    SDL_RWops * todel = pvm_rwops.release();
    SDL_FreeRW(todel);
}


int RWOps::tell() const
{
    return SDL_RWtell(pvm_rwops.get());
}

int RWOps::seek(int offset,Seek start)
{
    int newoffset = 0;
    switch (start)
    {
    case Set:
        newoffset = SDL_RWseek(pvm_rwops.get(),offset,SEEK_SET);
        break;
    case Cur:
        newoffset = SDL_RWseek(pvm_rwops.get(),offset,SEEK_CUR);
        break;
    case End:
        newoffset = SDL_RWseek(pvm_rwops.get(),offset,SEEK_END);
        break;
    }
    return newoffset;
}

bool RWOps::close()
{
    return SDL_RWtell(pvm_rwops.get()) == 0;
}

bool RWOps::dumpCode(const std::string & filename, const std::string & id)
{

    std::ofstream dumpfile(filename.c_str());


    const char HexTable[] = "0123456789abcdef";
    const int BytesPerLine = 20;


    //getting length of the RWOps in memory
    unsigned int length=SDL_RWseek(pvm_rwops.get(),0,SEEK_END);
    SDL_RWseek(pvm_rwops.get(),0,SEEK_SET);

    unsigned char* ch = new unsigned char[length];
    //reading 16-bytes blocks (arbitrary choice...)
    int blocks = SDL_RWread( pvm_rwops.get(), ch ,16,length/16) ;

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
