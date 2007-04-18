#include "SDLKeyboard.hh"
#include "SDLEventManager.hh"
#include "SDLConfig.hh"
#include <cassert>

namespace RAGE
{
    namespace SDL
    {
	    std::map<short,Keyboard::Key> Keyboard::Keysdl2rage;
	    std::map<std::string,Keyboard::Key> Keyboard::Keystr2rage;

	    std::map<short,Keyboard::Modifier> Keyboard::Modsdl2rage;
	    std::map<std::string,Keyboard::Modifier> Keyboard::Modstr2rage;

	    
	    short Keyboard::Key2sdl(Keyboard::Key k)
	    {
		    return Keyrage2sdl[k];
	    }
	    Keyboard::Key Keyboard::sdl2Key(short sdlk)
	    {
		    return Keysdl2rage[sdlk];
	    }
	    Keyboard::Key Keyboard::str2Key(std::string strk)
	    {
		    return Keystr2rage[strk];
	    }

	    
	    short Keyboard::Modifier2sdl(Keyboard::Modifier m)
	    {
		    return Modrage2sdl[m];
	    }
	    Keyboard::Modifier Keyboard::sdl2Modifier(short sdlm)
	    {
		    return Modsdl2rage[sdlm];
	    }
	    Keyboard::Modifier Keyboard::str2Modifier(std::string strm)
	    {
		    return Modstr2rage[strm];
	    }
	    
	    //based on the fact that Rage's enum map to in [0..number-1]. This way the vector is easily built
	    std::vector<short> Keyboard::InitKeyMapping()
	    {
		std::vector<short> result;
		std::map<Key,SDLKey> Keyrage2sdlmap;

		//using a max here to support partial mapping list...
		int maxvecindex =0;
		
		#define ASSOCIATE( key, sdlkey, strkey ) Keyrage2sdlmap[key] = sdlkey; Keysdl2rage[sdlkey] = key; Keystr2rage[strkey] = key; maxvecindex = (maxvecindex>key)? maxvecindex : key;
		#include "SDLKeyMapping.inl"
		#undef ASSOCIATE

		{
			result.resize(maxvecindex+1, SDLK_UNKNOWN);

			std::map<Key, SDLKey>::iterator it = Keyrage2sdlmap.begin();
			std::map<Key, SDLKey>::iterator itEnd = Keyrage2sdlmap.end();
			for (; it != itEnd; ++it)
			{
				assert((*it).first >= 0 && (*it).first < static_cast<int>(result.size()));
				result[(*it).first] = (*it).second;
			}
		}
		return result;
	    }

	    //using vector because the values of enum are cointiguous
	    std::vector<short> Keyboard::Keyrage2sdl = InitKeyMapping();
	    
	    std::vector<short> Keyboard::InitModMapping()
	    {
		    std::vector<short> result;
		std::map<Modifier,SDLMod> Modrage2sdlmap;

		int maxvecindex =0;
#define ASSOCIATE( mod, sdlmod, strmod ) Modrage2sdlmap[mod] = sdlmod; Modsdl2rage[sdlmod] = mod; Modstr2rage[strmod] = mod; maxvecindex = (maxvecindex>mod)? maxvecindex : mod;
		#include "SDLModMapping.inl"
		#undef ASSOCIATE

		{
			result.resize(maxvecindex+1, KMOD_NONE);

			std::map<Modifier, SDLMod>::iterator it = Modrage2sdlmap.begin();
			std::map<Modifier, SDLMod>::iterator itEnd = Modrage2sdlmap.end();
			for (; it != itEnd; ++it)
			{
				assert((*it).first >= 0 && (*it).first < static_cast<int>(result.size()));
				result[(*it).first] = (*it).second;
			}
		}
		return result;
	    }

	    std::vector<short> Keyboard::Modrage2sdl = InitModMapping();
	    
	    //initialises state at size 255 because of the ASCII table size.
	    Keyboard::Keyboard() : _state(255,false), _quitRequested(false)
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

        std::string Keyboard::getKeyName(Key k)
        {
		return std::string(SDL_GetKeyName(static_cast<SDLKey>(Key2sdl(k))));
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
               bool res = false;
        #ifdef DEBUG
                   Log << nl << " Key Name : " << getKeyName(s.getKey()) <<  " pressed : " << pressed << std::endl;
                   res=true;
        #endif

	//default keyboard behaviour : ESC quits
            switch( s.getKey() )
            {
                case KEscape:
                if (pressed==false)
                {
#ifdef DEBUG
                    Log << nl << "Quit requested !" << std::endl;
#endif
                    _quitRequested=true;
                    res=true;
                }
                break;
                default:
                res = false;
            }
               return res;
           }

	
	Keyboard::Sym::Sym(const SDL_keysym & ksym) : _key(sdl2Key(ksym.sym)), _mod(sdl2Modifier(ksym.mod)), _unicode(ksym.unicode)
	{
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
                if( s.isUnicode())
                {
                    std::cout << "unicode char : " << Unicode2Char(s.getUnicode()) << std::endl;
                    res=true;
                }
                else //mess with international codes...
                {
                    switch( s.getKey() )
                    {
                        //deal with international characters TODO
                        default: break;
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
