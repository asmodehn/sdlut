#ifndef SDL_KEYBOARD_HH
#define SDL_KEYBOARD_HH

#include <vector>
#include <map>

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
        protected:
            bool _quitRequested;

        public:

	//NB : this is lined to implementation to make accurate conversion from and to SDLMod
            typedef enum
            {
                None = 0,
                LShift, RShift,
                LCtrl, RCtrl,
                LAlt, RAlt,
                LMeta, RMeta,
                Num,
                Caps,
                Mode,
                Ctrl,
                Shift,
                Alt,
                Meta
            }
            Modifier;

		private :
	    static std::vector<short> Modrage2sdl;
	    static std::map<short,Modifier> Modsdl2rage;
	    static std::map<std::string,Modifier> Modstr2rage;

	    static std::vector<short> InitModMapping();

		public :
			
			static short Modifier2sdl(Modifier m);
			static Modifier sdl2Modifier(short sdlm);
			static Modifier str2Modifier(std::string strm);
			
            //TO BE CONTINUED
            typedef enum
            {
                KBackspace = 0,
                KTab,
                KClear,
                KReturn,
                KPause,
                KEscape,
                KSpace,
                KExclaim,
                KQuotedbl,
                KHash,
                KDollar,
                KAmpersand,
                KQuote,
                KLeftparen,
                KRightparen,
                KAsterisk,
                KPlus,
                KComma,
                KMinus,
                KPeriod,
                KSlash,
                K0,
                K1,
                K2,
                K3,
                K4,
                K5,
                K6,
                K7,
                K8,
		K9, //31
                KColon, KSemicolon, KLess, KEquals, KGreater, KQuestion, KAt, KLeftbracket, KBackslash, KRightbracket, KCaret, KUnderscore, KBackquote, KA, KB, KC, KD, KE, KF, KG, KH, KI, KJ, KK, KL, KM, KN, KO, KP , KQ, KR, KS, KT, KU, KV, KW, KX, KY, KZ, KDelete,
		KWorld0,KWorld1,KWorld2,KWorld3, KWorld4, KWorld5, KWorld6, KWorld7, KWorld8, KWorld9, //81
                KWorld10,KWorld11,KWorld12,KWorld13, KWorld14, KWorld15, KWorld16, KWorld17, KWorld18, KWorld19,
                KWorld20,KWorld21,KWorld22,KWorld23, KWorld24, KWorld25, KWorld26, KWorld27, KWorld28, KWorld29,
                KWorld30,KWorld31,KWorld32,KWorld33, KWorld34, KWorld35, KWorld36, KWorld37, KWorld38, KWorld39,
                KWorld40,KWorld41,KWorld42,KWorld43, KWorld44, KWorld45, KWorld46, KWorld47, KWorld48, KWorld49,
                KWorld50,KWorld51,KWorld52,KWorld53, KWorld54, KWorld55, KWorld56, KWorld57, KWorld58, KWorld59,
                KWorld60,KWorld61,KWorld62,KWorld63, KWorld64, KWorld65, KWorld66, KWorld67, KWorld68, KWorld69,
                KWorld70,KWorld71,KWorld72,KWorld73, KWorld74, KWorld75, KWorld76, KWorld77, KWorld78, KWorld79,
                KWorld80,KWorld81,KWorld82,KWorld83, KWorld84, KWorld85, KWorld86, KWorld87, KWorld88, KWorld89,
		KWorld90,KWorld91,KWorld92,KWorld93, KWorld94, KWorld95, //167
                KKp0,
				KKp1,
				KKp2,
				KKp3,
				KKp4,
				KKp5,
				KKp6,
				KKp7,
				KKp8,
				KKp9,
                KKDivide,
				KKMultiply,
				KKEnter,
                KUp,
                KDown,
                KRight,
                KLeft,
                KInsert, KHome, KEnd, KPageup, KPagedown,
				KF1,
				KF2,
				KF3,
				KF4,
				KF5,
				KF6,
				KF7,
				KF8,
				KF9,
				KF10,
				KF11, //200
				KF12,
				KF13,
				KF14,
				KF15,
                KNumlock, KCapslock, KScrollock,
				KRShift,
				KLshift,
				KLctrl,
				KRctrl,
				KRalt,
				KLalt,
				KRmeta, KLmeta, KRsuper, KLsuper, KMode, KCompose, KHelp, KPrintscreen, KSysreq, KBreak, KMenu, KPower, KEuro, KUndo //227
            }
            Key;

		private :
	    static std::vector<short> Keyrage2sdl;
	    static std::map<short,Key> Keysdl2rage;
	    static std::map<std::string,Key> Keystr2rage;

	    static std::vector<short> InitKeyMapping();

		public :
	    static short Key2sdl(Key k);
	    static Key sdl2Key(short sdlk);
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
            std::string getKeyName(Key k);

            //get the current key modifier state
            bool isModDown (Modifier m = None);
            //set the current key modifier state
            void setModDown(Modifier m = None);


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

        ///This class is not suitable for Gaming Input (doesnt detect key releases). Use Keyboard instead.
        ///However this class is well adapted for accurate text typing, with unicode enabled.
        class TextInput : public Keyboard
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
