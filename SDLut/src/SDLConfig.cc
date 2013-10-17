#include "SDLConfig.hh"

namespace SDLut
{

Core::Logger Log("SDLut::SDL");

std::string GetError()
{
    return SDL_GetError();
}

namespace Optional
{
std::string GetError(Module m)
{
    switch (m)
    {
    case Net:
#ifdef WK_SDLut_FOUND_SDLNET
        return SDLNet_GetError();
#endif
        break;
    case TTF:
#ifdef WK_SDLut_FOUND_SDLTTF
        return TTF_GetError();
#endif
        break;
    case Image:
#ifdef WK_SDLut_FOUND_SDLIMAGE
        return IMG_GetError();
#endif
        break;
    case Mixer:
#ifdef WK_SDLut_FOUND_SDLMIXER
#endif
        break;
    }
    return SDL_GetError();
}

bool isCompiled(Module m)
{
    switch (m)
    {
    case Net:
#ifdef WK_SDLut_FOUND_SDLNET
        return true;
#endif
        break;
    case TTF:
#ifdef WK_SDLut_FOUND_SDLTTF
        return true;
#endif
        break;
    case Image:
#ifdef WK_SDLut_FOUND_SDLIMAGE
        return true;
#endif
        break;
    case Mixer:
#ifdef WK_SDLut_FOUND_SDLMIXER
        return true;
#endif
        break;
    }
    return false;
}






bool isLinked(Module m)
{
    switch (m)
    {
    case Net:
#ifdef WK_SDLut_FOUND_SDLNET
        return SDLNet_Linked_Version() != NULL;
#endif
        break;
    case TTF:
#ifdef WK_SDLut_FOUND_SDLTTF
        return TTF_Linked_Version() != NULL;
#endif
        break;
    case Image:
#ifdef WK_SDLut_FOUND_SDLIMAGE
        return IMG_Linked_Version() != NULL;
#endif
        break;
    case Mixer:
#ifdef WK_SDLut_FOUND_SDLMIXER
        return Mix_Linked_Version() != NULL;
#endif
        break;
    }
    return false;
}


//to work around SDL_Net limitation
static bool isNetInit = false;

bool Init(Module m)
{
    switch (m)
    {
    case Net:
#ifdef WK_SDLut_FOUND_SDLNET
        return isNetInit = (SDLNet_Init() == 0);
#endif
        break;
    case TTF:
#ifdef WK_SDLut_FOUND_SDLTTF
        return TTF_Init() != 0;
#endif
        break;
    case Image:
#ifdef WK_SDLut_FOUND_SDLIMAGE
        return true; //no init needed
#endif
        break;

    case Mixer:
#ifdef WK_SDLut_FOUND_SDLMIXER
        return true; //no init needed though might be similar to openaudio...
#endif
        break;
    }
    return false;
}


bool WasInit(Module m)
{
    switch (m)
    {
    case Net:
#ifdef WK_SDLut_FOUND_SDLNET
        return isNetInit;
#endif
        break;
    case TTF:
#ifdef WK_SDLut_FOUND_SDLTTF
        //TODO : change int to bool with a check
        return TTF_WasInit() == SDL_TRUE;
#endif
        break;
    case Image:
#ifdef WK_SDLut_FOUND_SDLIMAGE
        return true; //no init needed
#endif
        break;
    case Mixer:
#ifdef WK_SDLut_FOUND_SDLMIXER
        return true; //no init needed though might be similar to openaudio...
#endif
        break;
    }
    return false;
}

void Quit(Module m)
{
    switch (m)
    {
    case Net:
#ifdef WK_SDLut_FOUND_SDLNET
        SDLNet_Quit(), isNetInit = false;
        return;
#endif
        break;
    case TTF:
#ifdef WK_SDLut_FOUND_SDLTTF
        //TODO : change int to bool with a check
        TTF_Quit();
        return;
#endif
        break;
    case Image:
#ifdef WK_SDLut_FOUND_SDLIMAGE
        return; //no quit needed
#endif
        break;
    case Mixer:
#ifdef WK_SDLut_FOUND_SDLMIXER
        return; //no quit needed though might be similar to openaudio...
#endif
        break;
    }
    return;
}
}

#if SDL_VERSION_ATLEAST(1, 2, 7)
bool CPU::hasRDTSC()
{
    return ( SDL_HasRDTSC() !=0) ;
}
bool CPU::hasMMX()
{
    return (SDL_HasMMX()!=0);
}
bool CPU::hasMMXExt()
{
    return (SDL_HasMMXExt()!=0);
}
bool CPU::has3DNow()
{
    return (SDL_Has3DNow()!=0);
}
bool CPU::has3DNowExt()
{
    return (SDL_Has3DNowExt()!=0);
}
//        bool CPU::hasSSE()
//        {
//            return (SDL_hasSSE()!=0);
//        }
//        bool CPU::hasSSEExt()
//        {
//            return (SDL_hasSSEExt()!=0);
//        }
bool CPU::hasAltiVec()
{
    return (SDL_HasAltiVec()!=0);
}

#endif

}
