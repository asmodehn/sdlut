#ifndef SDL_KEYBOARD_HH
#define SDL_KEYBOARD_HH

#include <vector>
#include <map>
#include <string>

struct SDL_keysym;

namespace RAGE
{
    namespace SDL
    {

        class EventManager;

        ///This class is not suitable for Full Text Input. Use TextInput instead.
        ///However this class is well adapted to key press / release detection, for gaming purpose...
        class Keyboard
        {

            //State of the Keyboard, updated only on demand by getKeyState
            std::vector<bool> _state;

            friend class EventManager;

        public:

            enum Modifier
            {
                Mod_None = 0,
                Mod_LShift, Mod_RShift,
                Mod_LCtrl, Mod_RCtrl,
                Mod_LAlt, Mod_RAlt,
                Mod_LMeta, Mod_RMeta,
                Mod_Num,
                Mod_Caps,
                Mod_Mode,
                Mod_Ctrl,
                Mod_Shift,
                Mod_Alt,
                Mod_Meta
            };

		private :
	    static std::vector<short> Modrage2sdl;
	    static std::map<short,Modifier> Modsdl2rage;
	    static std::map<std::string,Modifier> Modstr2rage;
		static std::map<Modifier,std::string> Modrage2str;

	    static std::vector<short> InitModMapping();

		public :
			
			static short Modifier2sdl(Modifier m);
			static Modifier sdl2Modifier(short sdlm);
			static Modifier str2Modifier(std::string strm);
			static std::string Modifier2str(Modifier m);
			
            //TO BE CONTINUED
            enum Key
            {
                Key_Backspace = 1,
                Key_Tab,
                Key_Clear,
                Key_Return,
                Key_Pause,
                Key_Escape,
                Key_Space,
                Key_Exclaim,
                Key_Quotedbl,
                Key_Hash,
                Key_Dollar,
                Key_Ampersand,
                Key_Quote,
                Key_Leftparen,
                Key_Rightparen,
                Key_Asterisk,
                Key_Plus,
                Key_Comma,
                Key_Minus,
                Key_Period,
                Key_Slash,
                Key_0,
                Key_1,
                Key_2,
                Key_3,
                Key_4,
                Key_5,
                Key_6,
                Key_7,
                Key_8,
				Key_9, //31
                Key_Colon, Key_Semicolon, Key_Less, Key_Equals, Key_Greater, Key_Question, Key_At, Key_Leftbracket, Key_Backslash, Key_Rightbracket, Key_Caret, Key_Underscore, Key_Backquote,
				Key_A, Key_B, Key_C, Key_D, Key_E, Key_F, Key_G, Key_H, Key_I, Key_J, Key_K, Key_L, Key_M, Key_N, Key_O, Key_P , Key_Q, Key_R, Key_S, Key_T, Key_U, Key_V, Key_W, Key_X, Key_Y, Key_Z,
				Key_Delete,
				Key_World0,Key_World1,Key_World2,Key_World3, Key_World4, Key_World5, Key_World6, Key_World7, Key_World8, Key_World9, //81
                Key_World10,Key_World11,Key_World12,Key_World13, Key_World14, Key_World15, Key_World16, Key_World17, Key_World18, Key_World19,
                Key_World20,Key_World21,Key_World22,Key_World23, Key_World24, Key_World25, Key_World26, Key_World27, Key_World28, Key_World29,
                Key_World30,Key_World31,Key_World32,Key_World33, Key_World34, Key_World35, Key_World36, Key_World37, Key_World38, Key_World39,
                Key_World40,Key_World41,Key_World42,Key_World43, Key_World44, Key_World45, Key_World46, Key_World47, Key_World48, Key_World49,
                Key_World50,Key_World51,Key_World52,Key_World53, Key_World54, Key_World55, Key_World56, Key_World57, Key_World58, Key_World59,
                Key_World60,Key_World61,Key_World62,Key_World63, Key_World64, Key_World65, Key_World66, Key_World67, Key_World68, Key_World69,
                Key_World70,Key_World71,Key_World72,Key_World73, Key_World74, Key_World75, Key_World76, Key_World77, Key_World78, Key_World79,
                Key_World80,Key_World81,Key_World82,Key_World83, Key_World84, Key_World85, Key_World86, Key_World87, Key_World88, Key_World89,
				Key_World90,Key_World91,Key_World92,Key_World93, Key_World94, Key_World95, //167
                Key_Kp0,
				Key_Kp1,
				Key_Kp2,
				Key_Kp3,
				Key_Kp4,
				Key_Kp5,
				Key_Kp6,
				Key_Kp7,
				Key_Kp8,
				Key_Kp9,
				Key_KPeriod,
                Key_KDivide,
				Key_KMultiply,
				Key_KMinus,
				Key_KPlus,
				Key_KEnter,
				Key_KEquals,
                Key_Up,
                Key_Down,
                Key_Right,
                Key_Left,
                Key_Insert, Key_Home, Key_End, Key_Pageup, Key_Pagedown,
				Key_F1,
				Key_F2,
				Key_F3,
				Key_F4,
				Key_F5,
				Key_F6,
				Key_F7,
				Key_F8,
				Key_F9,
				Key_F10,
				Key_F11, //200
				Key_F12,
				Key_F13,
				Key_F14,
				Key_F15,
                Key_Numlock, Key_Capslock, Key_Scrollock,
				Key_RShift,
				Key_Lshift,
				Key_Lctrl,
				Key_Rctrl,
				Key_Ralt,
				Key_Lalt,
				Key_Rmeta, Key_Lmeta, Key_Rsuper, Key_Lsuper, Key_Mode, Key_Compose, Key_Help, Key_Printscreen, Key_Sysreq, Key_Break, Key_Menu, Key_Power, Key_Euro, Key_Undo //227
            };

		private :
	    static std::vector<short> Keyrage2sdl;
	    static std::map<short,Key> Keysdl2rage;
	    static std::map<std::string,Key> Keystr2rage;
		static std::map<Key,std::string> Keyrage2str;

	    static std::vector<short> InitKeyMapping();

		public :
	    static short Key2sdl(Key k);
	    static Key sdl2Key(short sdlk);
		static std::string Key2str(Keyboard::Key k);
	    static Key str2Key(std::string strk);

            class  Sym
            {
                Key _key;
                Modifier _mod;
                long unsigned int _unicode;

                //the only class allowed to create Sym object from SDL_keysym
                friend class CriticalEvent;
                friend class Event;

				Sym(const SDL_keysym & ksym);

				public :

				inline Key getKey() const
				{
					return _key;
				}
				inline Modifier getMod() const
				{
					return _mod;
				}
				//WARNING Will return 0 if unicode not enabled
				inline long unsigned int getUnicode() const
				{
					return _unicode;
				}
				//just to convert the unicode value
				inline char getChar() const
				{
					//special cases
					if ( _key == Key_Return )
						return('\n');
					
					return(static_cast<char>(_unicode & 0x7F));
				}

				inline bool isUnicode() const
				{
					return (_unicode & 0xff80) == 0 ;
				}
			};



            //initialises state at size 255 because of the ASCII table size.
	    //also intialize the mapping between used dependency librairy and rage's enum
	    Keyboard();
	    virtual ~Keyboard();

            //Get a snapshot of the current keyboard state
            ///return a vector indexed by Key
            const std::vector<bool> & updateKeyState (void);
            //return true if key down.
            bool getKeyState(Key k )
            {
                updateKeyState();
                return _state[k];
            }

            //get the name of an SDL virtual key symbol
            std::string getSDLKeyName(Key k);
			std::string getKeyName(Key k);
			std::string getModifierName(Modifier m);

            //get the current key modifier state
            bool isModDown (Modifier m = Mod_None);
            //set the current key modifier state
            void setModDown(Modifier m = Mod_None);


            // Unicode keyboard translation
            bool enableUNICODE(void);
            bool disableUNICODE(void);
            bool isUNICODEEnabled(void);

            //Params Key repeat
	    //overload to support SDL defaults
	    bool enableKeyRepeat ();
	    bool enableKeyRepeat (int delay);
            bool enableKeyRepeat (int delay, int interval);


            //Callbacks on SDL_KEYUP or SDL_KEYDOWN
            virtual bool handleKeyEvent (const Sym &s, bool pressed);
            inline bool handleKeyPressEvent (const Sym &s)
            {
                return handleKeyEvent (s, true);
            }
            inline bool handleKeyReleaseEvent (const Sym &s)
            {
                return handleKeyEvent (s, false);
            }

        };

		//This class defines default behavior
		class DefaultKeyboard: public Keyboard
		{
			public:
				virtual bool handleKeyEvent (const Sym &s, bool pressed);
		};



        ///This class is not suitable for Gaming Input (doesnt detect key releases). Use Keyboard instead.
        ///However this class is well adapted for accurate text typing, with unicode enabled.
        class TextInput : public DefaultKeyboard
        {
        public:
            TextInput();
            virtual ~TextInput();

            static char Unicode2Char (long unsigned int unicode)
            {
                return char(unicode & 0x7F);
            }

            //Callbacks on SDL_KEYUP or SDL_KEYDOWN
            virtual bool handleKeyEvent (const Sym &s, bool pressed);

        };
    }
}

#endif
