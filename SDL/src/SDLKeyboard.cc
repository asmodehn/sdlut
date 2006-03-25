#include "SDLKeyboard.hh"
#include "SDLEventManager.hh"

namespace RAGE
{
    namespace SDL
    {
        //
        //SDLK_BACKSPACE 	'\b' 	backspace
        //SDLK_TAB 	'\t' 	tab
        //SDLK_CLEAR 		clear
        //SDLK_RETURN 	'\r' 	return
        //SDLK_PAUSE 		pause
        //SDLK_ESCAPE 	'^[' 	escape
        //SDLK_SPACE 	' ' 	space
        //SDLK_EXCLAIM 	'!' 	exclamation mark
        //SDLK_QUOTEDBL 	'"' 	double quote
        //SDLK_HASH 	'#' 	hash
        //SDLK_DOLLAR 	'$' 	dollar
        //SDLK_AMPERSAND 	'&' 	ampersand
        //SDLK_QUOTE 	'\'' 	single quote
        //SDLK_LEFTPAREN 	'(' 	left parenthesis
        //SDLK_RIGHTPAREN 	')' 	right parenthesis
        //SDLK_ASTERISK 	'*' 	asterisk
        //SDLK_PLUS 	'+' 	plus sign
        //SDLK_COMMA 	',' 	comma
        //SDLK_MINUS 	'-' 	minus sign
        //SDLK_PERIOD 	'.' 	period / full stop
        //SDLK_SLASH 	'/' 	forward slash
        //SDLK_0 	'0' 	0
        //SDLK_1 	'1' 	1
        //SDLK_2 	'2' 	2
        //SDLK_3 	'3' 	3
        //SDLK_4 	'4' 	4
        //SDLK_5 	'5' 	5
        //SDLK_6 	'6' 	6
        //SDLK_7 	'7' 	7
        //SDLK_8 	'8' 	8
        //SDLK_9 	'9' 	9
        //SDLK_COLON 	':' 	colon
        //SDLK_SEMICOLON 	';' 	semicolon
        //SDLK_LESS 	'<' 	less-than sign
        //SDLK_EQUALS 	'=' 	equals sign
        //SDLK_GREATER 	'>' 	greater-than sign
        //SDLK_QUESTION 	'?' 	question mark
        //SDLK_AT 	'@' 	at
        //SDLK_LEFTBRACKET 	'[' 	left bracket
        //SDLK_BACKSLASH 	'\\' 	backslash
        //SDLK_RIGHTBRACKET 	']' 	right bracket
        //SDLK_CARET 	'^' 	caret
        //SDLK_UNDERSCORE 	'_' 	underscore
        //SDLK_BACKQUOTE 	'`' 	grave
        //SDLK_a 	'a' 	a
        //SDLK_b 	'b' 	b
        //SDLK_c 	'c' 	c
        //SDLK_d 	'd' 	d
        //SDLK_e 	'e' 	e
        //SDLK_f 	'f' 	f
        //SDLK_g 	'g' 	g
        //SDLK_h 	'h' 	h
        //SDLK_i 	'i' 	i
        //SDLK_j 	'j' 	j
        //SDLK_k 	'k' 	k
        //SDLK_l 	'l' 	l
        //SDLK_m 	'm' 	m
        //SDLK_n 	'n' 	n
        //SDLK_o 	'o' 	o
        //SDLK_p 	'p' 	p
        //SDLK_q 	'q' 	q
        //SDLK_r 	'r' 	r
        //SDLK_s 	's' 	s
        //SDLK_t 	't' 	t
        //SDLK_u 	'u' 	u
        //SDLK_v 	'v' 	v
        //SDLK_w 	'w' 	w
        //SDLK_x 	'x' 	x
        //SDLK_y 	'y' 	y
        //SDLK_z 	'z' 	z
        //SDLK_DELETE 	'^?' 	delete
        //SDLK_WORLD_0 		world 0
        //SDLK_WORLD_1 		world 1
        //SDLK_WORLD_2 		world 2
        //SDLK_WORLD_3 		world 3
        //SDLK_WORLD_4 		world 4
        //SDLK_WORLD_5 		world 5
        //SDLK_WORLD_6 		world 6
        //SDLK_WORLD_7 		world 7
        //SDLK_WORLD_8 		world 8
        //SDLK_WORLD_9 		world 9
        //SDLK_WORLD_10 		world 10
        //SDLK_WORLD_11 		world 11
        //SDLK_WORLD_12 		world 12
        //SDLK_WORLD_13 		world 13
        //SDLK_WORLD_14 		world 14
        //SDLK_WORLD_15 		world 15
        //SDLK_WORLD_16 		world 16
        //SDLK_WORLD_17 		world 17
        //SDLK_WORLD_18 		world 18
        //SDLK_WORLD_19 		world 19
        //SDLK_WORLD_20 		world 20
        //SDLK_WORLD_21 		world 21
        //SDLK_WORLD_22 		world 22
        //SDLK_WORLD_23 		world 23
        //SDLK_WORLD_24 		world 24
        //SDLK_WORLD_25 		world 25
        //SDLK_WORLD_26 		world 26
        //SDLK_WORLD_27 		world 27
        //SDLK_WORLD_28 		world 28
        //SDLK_WORLD_29 		world 29
        //SDLK_WORLD_30 		world 30
        //SDLK_WORLD_31 		world 31
        //SDLK_WORLD_32 		world 32
        //SDLK_WORLD_33 		world 33
        //SDLK_WORLD_34 		world 34
        //SDLK_WORLD_35 		world 35
        //SDLK_WORLD_36 		world 36
        //SDLK_WORLD_37 		world 37
        //SDLK_WORLD_38 		world 38
        //SDLK_WORLD_39 		world 39
        //SDLK_WORLD_40 		world 40
        //SDLK_WORLD_41 		world 41
        //SDLK_WORLD_42 		world 42
        //SDLK_WORLD_43 		world 43
        //SDLK_WORLD_44 		world 44
        //SDLK_WORLD_45 		world 45
        //SDLK_WORLD_46 		world 46
        //SDLK_WORLD_47 		world 47
        //SDLK_WORLD_48 		world 48
        //SDLK_WORLD_49 		world 49
        //SDLK_WORLD_50 		world 50
        //SDLK_WORLD_51 		world 51
        //SDLK_WORLD_52 		world 52
        //SDLK_WORLD_53 		world 53
        //SDLK_WORLD_54 		world 54
        //SDLK_WORLD_55 		world 55
        //SDLK_WORLD_56 		world 56
        //SDLK_WORLD_57 		world 57
        //SDLK_WORLD_58 		world 58
        //SDLK_WORLD_59 		world 59
        //SDLK_WORLD_60 		world 60
        //SDLK_WORLD_61 		world 61
        //SDLK_WORLD_62 		world 62
        //SDLK_WORLD_63 		world 63
        //SDLK_WORLD_64 		world 64
        //SDLK_WORLD_65 		world 65
        //SDLK_WORLD_66 		world 66
        //SDLK_WORLD_67 		world 67
        //SDLK_WORLD_68 		world 68
        //SDLK_WORLD_69 		world 69
        //SDLK_WORLD_70 		world 70
        //SDLK_WORLD_71 		world 71
        //SDLK_WORLD_72 		world 72
        //SDLK_WORLD_73 		world 73
        //SDLK_WORLD_74 		world 74
        //SDLK_WORLD_75 		world 75
        //SDLK_WORLD_76 		world 76
        //SDLK_WORLD_77 		world 77
        //SDLK_WORLD_78 		world 78
        //SDLK_WORLD_79 		world 79
        //SDLK_WORLD_80 		world 80
        //SDLK_WORLD_81 		world 81
        //SDLK_WORLD_82 		world 82
        //SDLK_WORLD_83 		world 83
        //SDLK_WORLD_84 		world 84
        //SDLK_WORLD_85 		world 85
        //SDLK_WORLD_86 		world 86
        //SDLK_WORLD_87 		world 87
        //SDLK_WORLD_88 		world 88
        //SDLK_WORLD_89 		world 89
        //SDLK_WORLD_90 		world 90
        //SDLK_WORLD_91 		world 91
        //SDLK_WORLD_92 		world 92
        //SDLK_WORLD_93 		world 93
        //SDLK_WORLD_94 		world 94
        //SDLK_WORLD_95 		world 95
        //SDLK_KP0 		keypad 0
        //SDLK_KP1 		keypad 1
        //SDLK_KP2 		keypad 2
        //SDLK_KP3 		keypad 3
        //SDLK_KP4 		keypad 4
        //SDLK_KP5 		keypad 5
        //SDLK_KP6 		keypad 6
        //SDLK_KP7 		keypad 7
        //SDLK_KP8 		keypad 8
        //SDLK_KP9 		keypad 9
        //SDLK_KP_PERIOD 	'.' 	keypad period
        //SDLK_KP_DIVIDE 	'/' 	keypad divide
        //SDLK_KP_MULTIPLY 	'*' 	keypad multiply
        //SDLK_KP_MINUS 	'-' 	keypad minus
        //SDLK_KP_PLUS 	'+' 	keypad plus
        //SDLK_KP_ENTER 	'\r' 	keypad enter
        //SDLK_KP_EQUALS 	'=' 	keypad equals
        //SDLK_UP 		up arrow
        //SDLK_DOWN 		down arrow
        //SDLK_RIGHT 		right arrow
        //SDLK_LEFT 		left arrow
        //SDLK_INSERT 		insert
        //SDLK_HOME 		home
        //SDLK_END 		end
        //SDLK_PAGEUP 		page up
        //SDLK_PAGEDOWN 		page down
        //SDLK_F1 		F1
        //SDLK_F2 		F2
        //SDLK_F3 		F3
        //SDLK_F4 		F4
        //SDLK_F5 		F5
        //SDLK_F6 		F6
        //SDLK_F7 		F7
        //SDLK_F8 		F8
        //SDLK_F9 		F9
        //SDLK_F10 		F10
        //SDLK_F11 		F11
        //SDLK_F12 		F12
        //SDLK_F13 		F13
        //SDLK_F14 		F14
        //SDLK_F15 		F15
        //SDLK_NUMLOCK 		numlock
        //SDLK_CAPSLOCK 		capslock
        //SDLK_SCROLLOCK 		scrollock
        //SDLK_RSHIFT 		right shift
        //SDLK_LSHIFT 		left shift
        //SDLK_RCTRL 		right ctrl
        //SDLK_LCTRL 		left ctrl
        //SDLK_RALT 		right alt / alt gr
        //SDLK_LALT 		left alt
        //SDLK_RMETA 		right meta
        //SDLK_LMETA 		left meta
        //SDLK_LSUPER 		left windows key
        //SDLK_RSUPER 		right windows key
        //SDLK_MODE 		mode shift
        //SDLK_COMPOSE 		compose
        //SDLK_HELP 		help
        //SDLK_PRINT 		print-screen
        //SDLK_SYSREQ 		SysRq
        //SDLK_BREAK 		break
        //SDLK_MENU 		menu
        //SDLK_POWER 		power
        //SDLK_EURO 		euro
        //SDLK_UNDO 		undo
        //

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
            return _state;
        }

        std::string Keyboard::getKeyName(Key k)
        {
            return std::string(SDL_GetKeyName(static_cast<SDLKey>(k)));
        }

        bool Keyboard::isModDown (Modifier m)
        {
            return (m & SDL_GetModState()) !=0;
        }

        void Keyboard::setModDown(Modifier m)
        {
            SDL_SetModState(static_cast<SDLMod>(m));
        }



        bool Keyboard::enableKeyRepeat(int delay, int interval)
        {
            return SDL_EnableKeyRepeat(delay, interval) == 0;
        }

        //    bool Keyboard::handleKeyEvent (SDL_keysym &keysym, bool pressed)
        //    {
        //        bool res = false;
        //#ifdef DEBUG
        //            Log << nl << " Key Name : " << getKeyName(keysym.sym) <<  " pressed : " << pressed << std::endl;
        //            res=true;
        //#endif
        //        return res;
        //    }

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
