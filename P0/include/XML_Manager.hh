/*!
 * Description: This file content a small xml manager.
 * This manager is based on the libxml2 library
 * 
 * Author: XorfacX <xorfacx@gmail.com>
 *
 * Creation: 02/05/2007
 *
 * Copyright: See licence for info
 */

#ifndef XML_Manager_HH
#define XML_Manager_HH

#include "Base.hh"

//XML Manager Class
class XML_Manager
{
private:
	
			
public:
	//clean everything related to libxml2
	static void Clean_Up();

	//parse a file and validate it: check file exist, validate file vs is dtd, check pedantic error. Throw an error when file is invalid
	static void Validate_File(const string &filename);

	//Check if a node exists inside an xml file
	static bool Check_Node_Exists(const string &filename, const char* Option_Name, bool force_validation = false);

	//Get an option value string from an xml file and throw an error when option not found
	static string Get_Option_String(const string &filename, const char* Option_Name, bool force_validation = false);
	//Get an option value from an xml file when the option is an int and throw an error when option not found
	static int Get_Option_Value(const string &filename, const char* Option_Name, bool force_validation = false);
	//Get an option value from an xml file when the option is a long and throw an error when option not found
	static long Get_Option_Value_Long(const string &filename, const char* Option_Name, bool force_validation = false);
	
};

#endif
