#include "Ini_Manager.hh"

bool Ini_Manager::Write_New_Ini_File(const string &filename, const string &content)
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

bool Ini_Manager::Append_To_Ini_File(const string &filename, const string &content)
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

/*bool Ini_Manager::Read_Ini_File(const string &filename, char* string)
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
	string res;

	ifstream fi(filename.c_str());
	if ( fi.fail() )
	{
		fi.close();
		return res;
	}

	string newline_str;
	while (! fi.eof() )
	{
		getline(fi, newline_str);

		if (newline_str.find("#", 0) == string::npos ) //Only check un-commented line
		{
			//find the option string is in this line
			if ( newline_str.find(Option_Name, 0) != string::npos )
			{
				//Check if after the option name there is a space (for option name that have the same beginning)
				if ( newline_str.substr( ((string)Option_Name).length() , 1) == " " )
				{
					string::size_type equal_loc = newline_str.find("=", 0);  //find the '='
					if ( equal_loc != string::npos )
					{
						//find if string is between " "
						string::size_type quote_1_loc = newline_str.find("\"", 0);
						
						if ( quote_1_loc == string::npos ) //no " found
						{
							//remove whitespace: result is the clear string
							std::stringstream( newline_str.substr(equal_loc+1) ) >> skipws >> res;
							break;
						}
						else
						{
							//find the 2nd quote
							string::size_type quote_2_loc = (newline_str.substr(quote_1_loc+1)).find("\"", 0);
							if ( quote_2_loc == string::npos ) //the 2nd " wasn't found
							{
								//result is the all string after the = (even with the only ")
								res = newline_str.substr(equal_loc+1);
								break;

							} else {
								//result is the string between the " "
								res = newline_str.substr(quote_1_loc+1, quote_2_loc);
								break;
							}
						}
					}
				}
			}
		}
	}
		
	fi.close();

	return res;
}
