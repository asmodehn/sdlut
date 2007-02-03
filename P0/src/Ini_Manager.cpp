#include "Ini_Manager.hh"

bool Ini_Manager::Write_New_Ini_File(const string &filename, const char* content)
{
	ofstream fo(filename.c_str());
	if ( !fo.fail() )
	{
		fo << content;
		fo.close();
		return true;
	} else {
		fo.close();
		return false;
	}
}

bool Ini_Manager::Append_To_Ini_File(const string &filename, const char* content)
{
	ofstream fo(filename.c_str(), ofstream::app);
	if ( !fo.fail() )
	{
		fo << content;
		fo.close();
		return true;
	} else {
		fo.close();
		return false;
	}
}

/*bool Ini_Manager::Read_Ini_File(const string &filename, char* content)
{
	ifstream fi(filename.c_str());
	if ( !fi.fail() )
	{
		fo.close();
		return true;
	} else {
		fo.close();
		return false;
	}
}*/

string Ini_Manager::Get_Option_String(const string &filename, const char* Option_Name)
{
	ifstream fi(filename.c_str());
	if ( fi.fail() )
	{
		fi.close();
		return NULL;
	}

	char* newline = new char;
	string* newline_str = new string;
	while (! fi.eof() )
	{
		fi.getline(newline, 256);
		newline_str = new string(newline);
		if (newline_str->find("#", 0) == string::npos ) //Only check un-commented line
		{
			//find the option string is in this line
			if ( newline_str->find(Option_Name, 0) != string::npos )
			{
				//Check if after the option name there is a space (for option name that have the same beginning)
				if ( newline_str->substr( ((string)Option_Name).length() , 1) == " " )
				{
					string::size_type equal_loc = newline_str->find("=", 0);  //find the '='
					if ( equal_loc != string::npos )
					{
						//find if string is between " "
						string::size_type quote_1_loc = newline_str->find("\"", 0);
						
						if ( quote_1_loc == string::npos ) //no " found
						{
							char* temp_res = new char;
							//remove whitespace
							std::stringstream( newline_str->substr(equal_loc+1) ) >> skipws >> temp_res;
							//return the final clear string
							fi.close();
							return (string)temp_res;
						}
						else
						{
							//find the 2nd quote
							string::size_type quote_2_loc = (newline_str->substr(quote_1_loc+1)).find("\"", 0);
							if ( quote_2_loc == string::npos ) //the 2nd " wasn't found
							{
								fi.close();
								//return the all string after the = (even with the only ")
								return newline_str->substr(equal_loc+1);
							} else {
								fi.close();
								//we return the string between the " "
								return newline_str->substr(quote_1_loc+1, quote_2_loc);
							}
						}
					}
				}
			}
		}
		//free before looping
		//delete(newline_str);
	}
	
	//Option not found !?!
	fi.close();
	return NULL;
}

//Get the keyboard's key value from it's name
int Ini_Manager::Get_Key_Value_From_Key_Name(string key_str)
{
	int value=-1;
	if (key_str == "KUNKNOWN")
	{
		value = SDLK_UNKNOWN;
	}
	if (key_str == "KFIRST")
	{
		value = SDLK_FIRST;
	}
	if (key_str == "KBACKSPACE")
	{
		value = SDLK_BACKSPACE;
	}
	if (key_str == "KTAB")
	{
		value = SDLK_TAB;
	}
	if (key_str == "KCLEAR")
	{
		value = SDLK_CLEAR;
	}
	if (key_str == "KRETURN")
	{
		value = SDLK_RETURN;
	}
	if (key_str == "KPAUSE")
	{
		value = SDLK_PAUSE;
	}
	if (key_str == "KESCAPE")
	{
		value = SDLK_ESCAPE;
	}
	if (key_str == "KSPACE")
	{
		value = SDLK_SPACE;
	}
	if (key_str == "KEXCLAIM")
	{
		value = SDLK_EXCLAIM;
	}
	if (key_str == "KQUOTEDBL")
	{
		value = SDLK_QUOTEDBL;
	}
	if (key_str == "KHASH")
	{
		value = SDLK_HASH;
	}
	if (key_str == "KDOLLAR")
	{
		value = SDLK_DOLLAR;
	}
	if (key_str == "KAMPERSAND")
	{
		value = SDLK_AMPERSAND;
	}
	if (key_str == "KQUOTE")
	{
		value = SDLK_QUOTE;
	}
	if (key_str == "KLEFTPAREN")
	{
		value = SDLK_LEFTPAREN;
	}
	if (key_str == "KRIGHTPAREN")
	{
		value = SDLK_RIGHTPAREN;
	}
	if (key_str == "KASTERISK")
	{
		value = SDLK_ASTERISK;
	}
	if (key_str == "KPLUS")
	{
		value = SDLK_PLUS;
	}
	if (key_str == "KCOMMA")
	{
		value = SDLK_COMMA;
	}
	if (key_str == "KMINUS")
	{
		value = SDLK_MINUS;
	}
	if (key_str == "KPERIOD")
	{
		value = SDLK_PERIOD;
	}
	if (key_str == "KSLASH")
	{
		value = SDLK_SLASH;
	}
	if (key_str == "K0")
	{
		value = SDLK_0;
	}
	if (key_str == "K1")
	{
		value = SDLK_1;
	}
	if (key_str == "K2")
	{
		value = SDLK_2;
	}
	if (key_str == "K3")
	{
		value = SDLK_3;
	}
	if (key_str == "K4")
	{
		value = SDLK_4;
	}
	if (key_str == "K5")
	{
		value = SDLK_5;
	}
	if (key_str == "K6")
	{
		value = SDLK_6;
	}
	if (key_str == "K7")
	{
		value = SDLK_7;
	}
	if (key_str == "K8")
	{
		value = SDLK_8;
	}
	if (key_str == "K9")
	{
		value = SDLK_9;
	}
	if (key_str == "KCOLON")
	{
		value = SDLK_COLON;
	}
	if (key_str == "KSEMICOLON")
	{
		value = SDLK_SEMICOLON;
	}
	if (key_str == "KLESS")
	{
		value = SDLK_LESS;
	}
	if (key_str == "KEQUALS")
	{
		value = SDLK_EQUALS;
	}
	if (key_str == "KGREATER")
	{
		value = SDLK_GREATER;
	}
	if (key_str == "KQUESTION")
	{
		value = SDLK_QUESTION;
	}
	if (key_str == "KAT")
	{
		value = SDLK_AT;
	}
	if (key_str == "KLEFTBRACKET")
	{
		value = SDLK_LEFTBRACKET;
	}
	if (key_str == "KBACKSLASH")
	{
		value = SDLK_BACKSLASH;
	}
	if (key_str == "KRIGHTBRACKET")
	{
		value = SDLK_RIGHTBRACKET;
	}
	if (key_str == "KCARET")
	{
		value = SDLK_CARET;
	}
	if (key_str == "KUNDERSCORE")
	{
		value = SDLK_UNDERSCORE;
	}
	if (key_str == "KBACKQUOTE")
	{
		value = SDLK_BACKQUOTE;
	}
	if (key_str == "Ka")
	{
		value = SDLK_a;
	}
	if (key_str == "Kb")
	{
		value = SDLK_b;
	}
	if (key_str == "Kc")
	{
		value = SDLK_c;
	}
	if (key_str == "Kd")
	{
		value = SDLK_d;
	}
	if (key_str == "Ke")
	{
		value = SDLK_e;
	}
	if (key_str == "Kf")
	{
		value = SDLK_f;
	}
	if (key_str == "Kg")
	{
		value = SDLK_g;
	}
	if (key_str == "Kh")
	{
		value = SDLK_h;
	}
	if (key_str == "Ki")
	{
		value = SDLK_i;
	}
	if (key_str == "Kj")
	{
		value = SDLK_j;
	}
	if (key_str == "Kk")
	{
		value = SDLK_k;
	}
	if (key_str == "Kl")
	{
		value = SDLK_l;
	}
	if (key_str == "Km")
	{
		value = SDLK_m;
	}
	if (key_str == "Kn")
	{
		value = SDLK_n;
	}
	if (key_str == "Ko")
	{
		value = SDLK_o;
	}
	if (key_str == "Kp")
	{
		value = SDLK_p;
	}
	if (key_str == "Kq")
	{
		value = SDLK_q;
	}
	if (key_str == "Kr")
	{
		value = SDLK_r;
	}
	if (key_str == "Ks")
	{
		value = SDLK_s;
	}
	if (key_str == "Kt")
	{
		value = SDLK_t;
	}
	if (key_str == "Ku")
	{
		value = SDLK_u;
	}
	if (key_str == "Kv")
	{
		value = SDLK_v;
	}
	if (key_str == "Kw")
	{
		value = SDLK_w;
	}
	if (key_str == "Kx")
	{
		value = SDLK_x;
	}
	if (key_str == "Ky")
	{
		value = SDLK_y;
	}
	if (key_str == "Kz")
	{
		value = SDLK_z;
	}
	if (key_str == "KDELETE")
	{
		value = SDLK_DELETE;
	}
	if (key_str == "KWORLD_0")
	{
		value = SDLK_WORLD_0;
	}
	if (key_str == "KWORLD_1")
	{
		value = SDLK_WORLD_1;
	}
	if (key_str == "KWORLD_2")
	{
		value = SDLK_WORLD_2;
	}
	if (key_str == "KWORLD_3")
	{
		value = SDLK_WORLD_3;
	}
	if (key_str == "KWORLD_4")
	{
		value = SDLK_WORLD_4;
	}
	if (key_str == "KWORLD_5")
	{
		value = SDLK_WORLD_5;
	}
	if (key_str == "KWORLD_6")
	{
		value = SDLK_WORLD_6;
	}
	if (key_str == "KWORLD_7")
	{
		value = SDLK_WORLD_7;
	}
	if (key_str == "KWORLD_8")
	{
		value = SDLK_WORLD_8;
	}
	if (key_str == "KWORLD_9")
	{
		value = SDLK_WORLD_9;
	}
	if (key_str == "KWORLD_10")
	{
		value = SDLK_WORLD_10;
	}
	if (key_str == "KWORLD_11")
	{
		value = SDLK_WORLD_11;
	}
	if (key_str == "KWORLD_12")
	{
		value = SDLK_WORLD_12;
	}
	if (key_str == "KWORLD_13")
	{
		value = SDLK_WORLD_13;
	}
	if (key_str == "KWORLD_14")
	{
		value = SDLK_WORLD_14;
	}
	if (key_str == "KWORLD_15")
	{
		value = SDLK_WORLD_15;
	}
	if (key_str == "KWORLD_16")
	{
		value = SDLK_WORLD_16;
	}
	if (key_str == "KWORLD_17")
	{
		value = SDLK_WORLD_17;
	}
	if (key_str == "KWORLD_18")
	{
		value = SDLK_WORLD_18;
	}
	if (key_str == "KWORLD_19")
	{
		value = SDLK_WORLD_19;
	}
	if (key_str == "KWORLD_20")
	{
		value = SDLK_WORLD_20;
	}
	if (key_str == "KWORLD_21")
	{
		value = SDLK_WORLD_21;
	}
	if (key_str == "KWORLD_22")
	{
		value = SDLK_WORLD_22;
	}
	if (key_str == "KWORLD_23")
	{
		value = SDLK_WORLD_23;
	}
	if (key_str == "KWORLD_24")
	{
		value = SDLK_WORLD_24;
	}
	if (key_str == "KWORLD_25")
	{
		value = SDLK_WORLD_25;
	}
	if (key_str == "KWORLD_26")
	{
		value = SDLK_WORLD_26;
	}
	if (key_str == "KWORLD_27")
	{
		value = SDLK_WORLD_27;
	}
	if (key_str == "KWORLD_28")
	{
		value = SDLK_WORLD_28;
	}
	if (key_str == "KWORLD_29")
	{
		value = SDLK_WORLD_29;
	}
	if (key_str == "KWORLD_30")
	{
		value = SDLK_WORLD_30;
	}
	if (key_str == "KWORLD_31")
	{
		value = SDLK_WORLD_31;
	}
	if (key_str == "KWORLD_32")
	{
		value = SDLK_WORLD_32;
	}
	if (key_str == "KWORLD_33")
	{
		value = SDLK_WORLD_33;
	}
	if (key_str == "KWORLD_34")
	{
		value = SDLK_WORLD_34;
	}
	if (key_str == "KWORLD_35")
	{
		value = SDLK_WORLD_35;
	}
	if (key_str == "KWORLD_36")
	{
		value = SDLK_WORLD_36;
	}
	if (key_str == "KWORLD_37")
	{
		value = SDLK_WORLD_37;
	}
	if (key_str == "KWORLD_38")
	{
		value = SDLK_WORLD_38;
	}
	if (key_str == "KWORLD_39")
	{
		value = SDLK_WORLD_39;
	}
	if (key_str == "KWORLD_40")
	{
		value = SDLK_WORLD_40;
	}
	if (key_str == "KWORLD_41")
	{
		value = SDLK_WORLD_41;
	}
	if (key_str == "KWORLD_42")
	{
		value = SDLK_WORLD_42;
	}
	if (key_str == "KWORLD_43")
	{
		value = SDLK_WORLD_43;
	}
	if (key_str == "KWORLD_44")
	{
		value = SDLK_WORLD_44;
	}
	if (key_str == "KWORLD_45")
	{
		value = SDLK_WORLD_45;
	}
	if (key_str == "KWORLD_46")
	{
		value = SDLK_WORLD_46;
	}
	if (key_str == "KWORLD_47")
	{
		value = SDLK_WORLD_47;
	}
	if (key_str == "KWORLD_48")
	{
		value = SDLK_WORLD_48;
	}
	if (key_str == "KWORLD_49")
	{
		value = SDLK_WORLD_49;
	}
	if (key_str == "KWORLD_50")
	{
		value = SDLK_WORLD_50;
	}
	if (key_str == "KWORLD_51")
	{
		value = SDLK_WORLD_51;
	}
	if (key_str == "KWORLD_52")
	{
		value = SDLK_WORLD_52;
	}
	if (key_str == "KWORLD_53")
	{
		value = SDLK_WORLD_53;
	}
	if (key_str == "KWORLD_54")
	{
		value = SDLK_WORLD_54;
	}
	if (key_str == "KWORLD_55")
	{
		value = SDLK_WORLD_55;
	}
	if (key_str == "KWORLD_56")
	{
		value = SDLK_WORLD_56;
	}
	if (key_str == "KWORLD_57")
	{
		value = SDLK_WORLD_57;
	}
	if (key_str == "KWORLD_58")
	{
		value = SDLK_WORLD_58;
	}
	if (key_str == "KWORLD_59")
	{
		value = SDLK_WORLD_59;
	}
	if (key_str == "KWORLD_60")
	{
		value = SDLK_WORLD_60;
	}
	if (key_str == "KWORLD_61")
	{
		value = SDLK_WORLD_61;
	}
	if (key_str == "KWORLD_62")
	{
		value = SDLK_WORLD_62;
	}
	if (key_str == "KWORLD_63")
	{
		value = SDLK_WORLD_63;
	}
	if (key_str == "KWORLD_64")
	{
		value = SDLK_WORLD_64;
	}
	if (key_str == "KWORLD_65")
	{
		value = SDLK_WORLD_65;
	}
	if (key_str == "KWORLD_66")
	{
		value = SDLK_WORLD_66;
	}
	if (key_str == "KWORLD_67")
	{
		value = SDLK_WORLD_67;
	}
	if (key_str == "KWORLD_68")
	{
		value = SDLK_WORLD_68;
	}
	if (key_str == "KWORLD_69")
	{
		value = SDLK_WORLD_69;
	}
	if (key_str == "KWORLD_70")
	{
		value = SDLK_WORLD_70;
	}
	if (key_str == "KWORLD_71")
	{
		value = SDLK_WORLD_71;
	}
	if (key_str == "KWORLD_72")
	{
		value = SDLK_WORLD_72;
	}
	if (key_str == "KWORLD_73")
	{
		value = SDLK_WORLD_73;
	}
	if (key_str == "KWORLD_74")
	{
		value = SDLK_WORLD_74;
	}
	if (key_str == "KWORLD_75")
	{
		value = SDLK_WORLD_75;
	}
	if (key_str == "KWORLD_76")
	{
		value = SDLK_WORLD_76;
	}
	if (key_str == "KWORLD_77")
	{
		value = SDLK_WORLD_77;
	}
	if (key_str == "KWORLD_78")
	{
		value = SDLK_WORLD_78;
	}
	if (key_str == "KWORLD_79")
	{
		value = SDLK_WORLD_79;
	}
	if (key_str == "KWORLD_80")
	{
		value = SDLK_WORLD_80;
	}
	if (key_str == "KWORLD_81")
	{
		value = SDLK_WORLD_81;
	}
	if (key_str == "KWORLD_82")
	{
		value = SDLK_WORLD_82;
	}
	if (key_str == "KWORLD_83")
	{
		value = SDLK_WORLD_83;
	}
	if (key_str == "KWORLD_84")
	{
		value = SDLK_WORLD_84;
	}
	if (key_str == "KWORLD_85")
	{
		value = SDLK_WORLD_85;
	}
	if (key_str == "KWORLD_86")
	{
		value = SDLK_WORLD_86;
	}
	if (key_str == "KWORLD_87")
	{
		value = SDLK_WORLD_87;
	}
	if (key_str == "KWORLD_88")
	{
		value = SDLK_WORLD_88;
	}
	if (key_str == "KWORLD_89")
	{
		value = SDLK_WORLD_89;
	}
	if (key_str == "KWORLD_90")
	{
		value = SDLK_WORLD_90;
	}
	if (key_str == "KWORLD_91")
	{
		value = SDLK_WORLD_91;
	}
	if (key_str == "KWORLD_92")
	{
		value = SDLK_WORLD_92;
	}
	if (key_str == "KWORLD_93")
	{
		value = SDLK_WORLD_93;
	}
	if (key_str == "KWORLD_94")
	{
		value = SDLK_WORLD_94;
	}
	if (key_str == "KWORLD_95")
	{
		value = SDLK_WORLD_95;
	}
	if (key_str == "KKP0")
	{
		value = SDLK_KP0;
	}
	if (key_str == "KKP1")
	{
		value = SDLK_KP1;
	}
	if (key_str == "KKP2")
	{
		value = SDLK_KP2;
	}
	if (key_str == "KKP3")
	{
		value = SDLK_KP3;
	}
	if (key_str == "KKP4")
	{
		value = SDLK_KP4;
	}
	if (key_str == "KKP5")
	{
		value = SDLK_KP5;
	}
	if (key_str == "KKP6")
	{
		value = SDLK_KP6;
	}
	if (key_str == "KKP7")
	{
		value = SDLK_KP7;
	}
	if (key_str == "KKP8")
	{
		value = SDLK_KP8;
	}
	if (key_str == "KKP9")
	{
		value = SDLK_KP9;
	}
	if (key_str == "KKPPERIOD")
	{
		value = SDLK_KP_PERIOD;
	}
	if (key_str == "KKPDIVIDE")
	{
		value = SDLK_KP_DIVIDE;
	}
	if (key_str == "KKPMULTIPLY")
	{
		value = SDLK_KP_MULTIPLY;
	}
	if (key_str == "KKPMINUS")
	{
		value = SDLK_KP_MINUS;
	}
	if (key_str == "KKPPLUS")
	{
		value = SDLK_KP_PLUS;
	}
	if (key_str == "KKPENTER")
	{
		value = SDLK_KP_ENTER;
	}
	if (key_str == "KKPEQUALS")
	{
		value = SDLK_KP_EQUALS;
	}
	if (key_str == "KUP")
	{
		value = SDLK_UP;
	}
	if (key_str == "KDOWN")
	{
		value = SDLK_DOWN;
	}
	if (key_str == "KRIGHT")
	{
		value = SDLK_RIGHT;
	}
	if (key_str == "KLEFT")
	{
		value = SDLK_LEFT;
	}
	if (key_str == "KINSERT")
	{
		value = SDLK_INSERT;
	}
	if (key_str == "KHOME")
	{
		value = SDLK_HOME;
	}
	if (key_str == "KEND")
	{
		value = SDLK_END;
	}
	if (key_str == "KPAGEUP")
	{
		value = SDLK_PAGEUP;
	}
	if (key_str == "KPAGEDOWN")
	{
		value = SDLK_PAGEDOWN;
	}
	if (key_str == "KF1")
	{
		value = SDLK_F1;
	}
	if (key_str == "KF2")
	{
		value = SDLK_F2;
	}
	if (key_str == "KF3")
	{
		value = SDLK_F3;
	}
	if (key_str == "KF4")
	{
		value = SDLK_F4;
	}
	if (key_str == "KF5")
	{
		value = SDLK_F5;
	}
	if (key_str == "KF6")
	{
		value = SDLK_F6;
	}
	if (key_str == "KF7")
	{
		value = SDLK_F7;
	}
	if (key_str == "KF8")
	{
		value = SDLK_F8;
	}
	if (key_str == "KF9")
	{
		value = SDLK_F9;
	}
	if (key_str == "KF10")
	{
		value = SDLK_F10;
	}
	if (key_str == "KF11")
	{
		value = SDLK_F11;
	}
	if (key_str == "KF12")
	{
		value = SDLK_F12;
	}
	if (key_str == "KF13")
	{
		value = SDLK_F13;
	}
	if (key_str == "KF14")
	{
		value = SDLK_F14;
	}
	if (key_str == "KF15")
	{
		value = SDLK_F15;
	}
	if (key_str == "KNUMLOCK")
	{
		value = SDLK_NUMLOCK;
	}
	if (key_str == "KCAPSLOCK")
	{
		value = SDLK_CAPSLOCK;
	}
	if (key_str == "KSCROLLOCK")
	{
		value = SDLK_SCROLLOCK;
	}
	if (key_str == "KRSHIFT")
	{
		value = SDLK_RSHIFT;
	}
	if (key_str == "KLSHIFT")
	{
		value = SDLK_LSHIFT;
	}
	if (key_str == "KRCTRL")
	{
		value = SDLK_RCTRL;
	}
	if (key_str == "KLCTRL")
	{
		value = SDLK_LCTRL;
	}
	if (key_str == "KRALT")
	{
		value = SDLK_RALT;
	}
	if (key_str == "KLALT")
	{
		value = SDLK_LALT;
	}
	if (key_str == "KRMETA")
	{
		value = SDLK_RMETA;
	}
	if (key_str == "KLMETA")
	{
		value = SDLK_LMETA;
	}
	if (key_str == "KLSUPER")
	{
		value = SDLK_LSUPER;
	}
	if (key_str == "KRSUPER")
	{
		value = SDLK_RSUPER;
	}
	if (key_str == "KMODE")
	{
		value = SDLK_MODE;
	}
	if (key_str == "KCOMPOSE")
	{
		value = SDLK_COMPOSE;
	}
	if (key_str == "KHELP")
	{
		value = SDLK_HELP;
	}
	if (key_str == "KPRINT")
	{
		value = SDLK_PRINT;
	}
	if (key_str == "KSYSREQ")
	{
		value = SDLK_SYSREQ;
	}
	if (key_str == "KBREAK")
	{
		value = SDLK_BREAK;
	}
	if (key_str == "KMENU")
	{
		value = SDLK_MENU;
	}
	if (key_str == "KPOWER")
	{
		value = SDLK_POWER;
	}
	if (key_str == "KEURO")
	{
		value = SDLK_EURO;
	}
	if (key_str == "KUNDO")
	{
		value = SDLK_UNDO;
	}

	return value;
}
