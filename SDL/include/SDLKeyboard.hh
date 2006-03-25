#ifndef SDL_KEYBOARD_HH
#define SDL_KEYBOARD_HH

#include "SDLConfig.hh"

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

            typedef enum
            {
                None=KMOD_NONE,
                LShift=KMOD_LSHIFT, RShift=KMOD_RSHIFT,
                LCtrl = KMOD_LCTRL, RCtrl = KMOD_RCTRL,
                LAlt = KMOD_LALT, RAlt = KMOD_RALT,
                LMeta =KMOD_LMETA, RMeta = KMOD_RMETA,
                Num = KMOD_NUM,
                Caps = KMOD_CAPS,
                Mode = KMOD_MODE,
                Ctrl = KMOD_CTRL,
                Shift = KMOD_SHIFT,
                Alt = KMOD_ALT,
                Meta = KMOD_META
            }
            Modifier;

            //TO BE CONTINUED
            typedef enum
            {
                KBackspace = SDLK_BACKSPACE,
                KTab = SDLK_TAB,
                KClear = SDLK_CLEAR,
                KReturn = SDLK_RETURN,
                KPause = SDLK_PAUSE,
                KEscape = SDLK_ESCAPE,
                KSpace = SDLK_SPACE,
                KExclaim = SDLK_EXCLAIM,
                KQuotedbl = SDLK_QUOTEDBL,
                KHash = SDLK_HASH,
                KDollar = SDLK_DOLLAR,
                KAmpersand = SDLK_AMPERSAND,
                KQuote = SDLK_QUOTE,
                KLeftparen = SDLK_LEFTPAREN,
                KRightparen = SDLK_RIGHTPAREN,
                KAsterisk = SDLK_ASTERISK,
                KPlus = SDLK_PLUS,
                KComma = SDLK_COMMA,
                KMinus = SDLK_MINUS,
                KPeriod = SDLK_PERIOD,
                KSlash = SDLK_SLASH,
                K0 = SDLK_0,
                K1 = SDLK_1,
                K2 = SDLK_2,
                K3 = SDLK_3,
                K4 = SDLK_4,
                K5 = SDLK_5,
                K6 = SDLK_6,
                K7 = SDLK_7,
                K8 = SDLK_8,
                K9 = SDLK_9,
                KColon, KSemicolon, KLess, KEquals, KGreater, KQuestion, KAt, KLeftbracket, KBackslash, KRightbracket, KCaret, KUnderscore, KBackquote, KA, KB, KC, KD, KE, KF, KG, KH, KI, KJ, KK, KL, KM, KN, KO, KP , KQ, KR, KS, KT, KU, KV, KW, KX, KY, KZ, KDelete,
                KWorld0,KWorld1,KWorld2,KWorld3, KWorld4, KWorld5, KWorld6, KWorld7, KWorld8, KWorld9,
                KWorld10,KWorld11,KWorld12,KWorld13, KWorld14, KWorld15, KWorld16, KWorld17, KWorld18, KWorld19,
                KWorld20,KWorld21,KWorld22,KWorld23, KWorld24, KWorld25, KWorld26, KWorld27, KWorld28, KWorld29,
                KWorld30,KWorld31,KWorld32,KWorld33, KWorld34, KWorld35, KWorld36, KWorld37, KWorld38, KWorld39,
                KWorld40,KWorld41,KWorld42,KWorld43, KWorld44, KWorld45, KWorld46, KWorld47, KWorld48, KWorld49,
                KWorld50,KWorld51,KWorld52,KWorld53, KWorld54, KWorld55, KWorld56, KWorld57, KWorld58, KWorld59,
                KWorld60,KWorld61,KWorld62,KWorld63, KWorld64, KWorld65, KWorld66, KWorld67, KWorld68, KWorld69,
                KWorld70,KWorld71,KWorld72,KWorld73, KWorld74, KWorld75, KWorld76, KWorld77, KWorld78, KWorld79,
                KWorld80,KWorld81,KWorld82,KWorld83, KWorld84, KWorld85, KWorld86, KWorld87, KWorld88, KWorld89,
                KWorld90,KWorld91,KWorld92,KWorld93, KWorld94, KWorld95,
                KKp0 = SDLK_KP0,
				KKp1 = SDLK_KP1,
				KKp2 = SDLK_KP2,
				KKp3 = SDLK_KP3,
				KKp4 = SDLK_KP4,
				KKp5 = SDLK_KP5,
				KKp6 = SDLK_KP6,
				KKp7 = SDLK_KP7,
				KKp8 = SDLK_KP8,
				KKp9 = SDLK_KP9,
                KKDivide = SDLK_KP_DIVIDE,
				KKMultiply = SDLK_KP_MULTIPLY,
				KKEnter = SDLK_KP_ENTER,
                KUp = SDLK_UP,
                KDown = SDLK_DOWN,
                KRight = SDLK_RIGHT,
                KLeft = SDLK_LEFT,
                KInsert, KHome, KEnd, KPageup, KPagedown, KF1, KF2, KF3, KF4, KF5, KF6, KF7, KF8, KF9, KF10, KF11, KF12, KF13, KF14, KF15,
                KNumlock, KCapslock, KScrollock,
				KRShift = SDLK_RSHIFT,
				KLshift = SDLK_LSHIFT,
				KLctrl = SDLK_LCTRL,
				KRctrl = SDLK_RCTRL,
				KRalt = SDLK_RALT,
				KLalt = SDLK_LALT,
				KRmeta, KLmeta, KRsuper, KLsuper, KMode, KCompose, KHelp, KPrintscreen, KSysreq, KBreak, KMenu, KPower, KEuro, KUndo
            }
            Key;

            class  Sym
            {
                Key _key;
                Modifier _mod;
                long unsigned int _unicode;

                //the only class allowed to create Sym object from SDL_keysym
                friend class CriticalEvent;
                friend class Event;

                Sym(const SDL_keysym & ksym) : _key(static_cast<Key>(ksym.sym)), _mod(static_cast<Modifier>(ksym.mod)), _unicode(ksym.unicode)
                {}

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
            Keyboard() : _state(255,false), _quitRequested(false)
            {}
            virtual ~Keyboard()
            {}

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
            bool enableKeyRepeat (int delay = SDL_DEFAULT_REPEAT_DELAY,
                                  int interval = SDL_DEFAULT_REPEAT_INTERVAL);


            //Callbacks on SDL_KEYUP or SDL_KEYDOWN
            virtual bool handleKeyEvent (const Sym &s, bool pressed) = 0;
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
