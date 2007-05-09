#ifndef Ini_Manager_HH
#define Ini_Manager_HH

#include "Base.hh"

//Ini Manager Class
class Ini_Manager
{
private:
	void Parse_Line();
		
public:
	static bool Write_New_Ini_File(const string &filename, const string &content);
	static bool Append_To_Ini_File(const string &filename, const string &content);
	//static bool Read_Ini_File(const string &filename, string content);

	static string Get_Option_String(const string &filename, const char* Option_Name);

};

#endif
