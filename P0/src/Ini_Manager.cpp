#include "Ini_Manager.hh"

bool Ini_Manager::Write_New_Ini_File(const string &filename, string content)
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

bool Ini_Manager::Append_To_Ini_File(const string &filename, string content)
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
