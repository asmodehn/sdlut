#include "Input/SDLKeyboard.hh"
#include "System/SDLEventManager.hh"
#include "SDLApp.hh" //for default behavior

#include "SDLConfig.hh"
#include <cassert>

namespace SDLut
{
namespace input
{
std::map<short,Keyboard::Key> Keyboard::Keysdl2SDLut;
std::map<std::string,Keyboard::Key> Keyboard::Keystr2SDLut;
std::map<Keyboard::Key,std::string> Keyboard::KeySDLut2str;

std::map<short,Keyboard::Modifier> Keyboard::Modsdl2SDLut;
std::map<std::string,Keyboard::Modifier> Keyboard::Modstr2SDLut;
std::map<Keyboard::Modifier,std::string> Keyboard::ModSDLut2str;

short Keyboard::Key2sdl(Keyboard::Key k)
{
    return KeySDLut2sdl[k];
}
Keyboard::Key Keyboard::sdl2Key(short sdlk)
{
    return Keysdl2SDLut[sdlk];
}
std::string Keyboard::Key2str(Keyboard::Key k)
{
    return (k == 0) ? ("") : (KeySDLut2str[k]);
}
Keyboard::Key Keyboard::str2Key(std::string strk)
{
    return Keystr2SDLut[strk];
}


short Keyboard::Modifier2sdl(Keyboard::Modifier m)
{
    return ModSDLut2sdl[m];
}
Keyboard::Modifier Keyboard::sdl2Modifier(short sdlm)
{
    return Modsdl2SDLut[sdlm];
}
std::string Keyboard::Modifier2str(Keyboard::Modifier m)
{
    return ModSDLut2str[m];
}
Keyboard::Modifier Keyboard::str2Modifier(std::string strm)
{
    return Modstr2SDLut[strm];
}

//based on the fact that SDLut's enum map to in [0..number-1]. This way the vector is easily built
std::vector<short> Keyboard::InitKeyMapping()
{
    std::vector<short> result;
    std::map<Key,SDLKey> KeySDLut2sdlmap;

    //using a max here to support partial mapping list...
    int maxvecindex =0;

#define ASSOCIATE( key, sdlkey, strkey ) KeySDLut2sdlmap[key] = sdlkey; Keysdl2SDLut[sdlkey] = key; Keystr2SDLut[strkey] = key; KeySDLut2str[key] = strkey; maxvecindex = (maxvecindex>key)? maxvecindex : key;
#include "SDLKeyMapping.inl"
#undef ASSOCIATE

    {
        result.resize(maxvecindex+1, SDLK_UNKNOWN);

        std::map<Key, SDLKey>::iterator it = KeySDLut2sdlmap.begin();
        std::map<Key, SDLKey>::iterator itEnd = KeySDLut2sdlmap.end();
        for (; it != itEnd; ++it)
        {
            assert((*it).first >= 0 && (*it).first < static_cast<int>(result.size()));
            result[(*it).first] = (short int)(*it).second;
        }
    }
    return result;
}

//using vector because the values of enum are cointiguous
std::vector<short> Keyboard::KeySDLut2sdl = InitKeyMapping();

std::vector<short> Keyboard::InitModMapping()
{
    std::vector<short> result;
    std::map<Modifier,SDLMod> ModSDLut2sdlmap;

    int maxvecindex =0;
#define ASSOCIATE( mod, sdlmod, strmod ) ModSDLut2sdlmap[mod] = sdlmod; Modsdl2SDLut[sdlmod] = mod; Modstr2SDLut[strmod] = mod; ModSDLut2str[mod] = strmod; maxvecindex = (maxvecindex>mod)? maxvecindex : mod;
#include "SDLModMapping.inl"
#undef ASSOCIATE

    {
        result.resize(maxvecindex+1, KMOD_NONE);

        std::map<Modifier, SDLMod>::iterator it = ModSDLut2sdlmap.begin();
        std::map<Modifier, SDLMod>::iterator itEnd = ModSDLut2sdlmap.end();
        for (; it != itEnd; ++it)
        {
            assert((*it).first >= 0 && (*it).first < static_cast<int>(result.size()));
            result[(*it).first] = (short int)(*it).second;
        }
    }
    return result;
}

std::vector<short> Keyboard::ModSDLut2sdl = InitModMapping();

//initialises state at size 255 because of the ASCII table size.
Keyboard::Keyboard() : _state(255,false)
{
}
Keyboard::~Keyboard()
{
}

const std::vector<bool> & Keyboard::updateKeyState()
{
    int size;
    Uint8 *keystate = SDL_GetKeyState(&size);
    _state.clear();
//            _state.reserve(size);
    _state.resize(size,false);

    for (int i=0; i< size; i++)
    {
        _state[i]= (keystate[i] !=0);
    }
    delete keystate;
    return _state;
}

std::string Keyboard::getSDLKeyName(Key k)
{
    return std::string(SDL_GetKeyName(static_cast<SDLKey>(Key2sdl(k))));
}
std::string Keyboard::getKeyName(Key k)
{
    return Key2str(k);
}
std::string Keyboard::getModifierName(Modifier m)
{
    return Modifier2str(m);
}


bool Keyboard::isModDown (Modifier m)
{
    return (Modifier2sdl(m) & SDL_GetModState()) !=0;
}

void Keyboard::setModDown(Modifier m)
{
    SDL_SetModState(static_cast<SDLMod>(Modifier2sdl(m)));
}

bool Keyboard::enableKeyRepeat()
{
    return SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL) == 0;
}
bool Keyboard::enableKeyRepeat(int delay)
{
    return SDL_EnableKeyRepeat(delay, SDL_DEFAULT_REPEAT_INTERVAL) == 0;
}
bool Keyboard::enableKeyRepeat(int delay, int interval)
{
    return SDL_EnableKeyRepeat(delay, interval) == 0;
}


bool Keyboard::handleKeyEvent (const Sym &s, bool pressed)
{
    return false;
}


Keyboard::Sym::Sym(const SDL_keysym & ksym) : _key(sdl2Key((short int)ksym.sym)), _mod(sdl2Modifier((short int)ksym.mod)), _unicode(ksym.unicode)
{
}


bool DefaultKeyboard::handleKeyEvent (const Sym &s, bool pressed)
{
    bool res = false;

    //default keyboard behaviour :

    switch ( s.getKey() )
    {
        //ESC quits
    case Key_Escape:
        if (pressed==false)
        {
            App::getInstance().requestTermination();
            res=true;
        }
        break;
    case Key_F4: //ALT+F4 quits
        if ( (pressed==true) && (isModDown(Mod_Alt)) )
            App::getInstance().requestTermination();
        res = true;
        break;
    case Key_F11: //F11 toggles fullscreen
        if (pressed==true)
            App::getInstance().getDisplay().getScreenBuffer().setFullscreen(
                !App::getInstance().getDisplay().getScreenBuffer().isFullscreen());
        res = true;
        break;
    default:
        res = false;
    }
    return res;
}

TextInput::TextInput()
{
    SDL_EnableUNICODE(1);
}

TextInput::~TextInput()
{
    SDL_EnableUNICODE(0);
}


bool TextInput::handleKeyEvent (const Sym &s, bool pressed)
{
    bool res = false;

    //get the unicode character
    if (!res && pressed)
    {
        if ( s.isUnicode())
        {
            std::cout << "unicode char : " << Unicode2Char(s.getUnicode()) << std::endl;
            res=true;
        }
        else //mess with international codes...
        {
            switch ( s.getKey() )
            {
                //TODO deal with international characters
            default:
                break;
            }
            res=false;
        }
    }
    //TODO on every Event Loop (not critical, and not only keyboard...
    std::cout << std::flush;

    return res;

}
}
}
