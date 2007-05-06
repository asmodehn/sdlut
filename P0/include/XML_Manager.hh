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

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdexcept>
#include "libxml/xmlreader.h"

using namespace std;

//XML Manager Class
class XML_Manager
{
private:
	
			
public:
	//clean everything related to libxml2
	static void Clean_Up();

	//parse a file and validate it: check file exist, validate file vs is dtd, check pedantic error
	static bool Validate_File(const string &filename);

	static string Get_Option_String(const string &filename, const char* Option_Name, bool force_validation = false);
	static int Get_Option_Value(const string &filename, const char* Option_Name, bool force_validation = false);
	static long Get_Option_Value_Long(const string &filename, const char* Option_Name, bool force_validation = false);
	
};

#endif
