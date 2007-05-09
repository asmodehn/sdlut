#include "XML_Manager.hh"

//clean everything related to libxml2
void XML_Manager::Clean_Up()
{
	xmlCleanupParser(); //Cleanup function for the XML library.
	xmlMemoryDump(); //Debug memory for regression tests
}

//parse a file and validate it: check file exist, validate file vs is dtd, check pedantic error
void XML_Manager::Validate_File(const string &filename)
{
try {
	xmlTextReaderPtr Reader = xmlReaderForFile( filename.c_str(), NULL,
		XML_PARSE_DTDLOAD |  // load the external subset 
		XML_PARSE_DTDVALID //|  // validate with the DTD
		//XML_PARSE_PEDANTIC    // pedantic error reporting 
		); 

	if ( Reader == NULL )
		throw std::logic_error("File " + filename + " doesn't exist");

	//parse the whole file & display non conformity errors
	int Read_Node = xmlTextReaderRead(Reader);
	if ( Read_Node == -1)
		throw std::logic_error("Error Parsing file: " + filename);
	while ( Read_Node == 1)
	{
		if ( Read_Node == -1)
			throw std::logic_error("Error Parsing file: " + filename);
		Read_Node = xmlTextReaderRead(Reader);
	}

	if ( xmlTextReaderIsValid(Reader) != 1)
		throw std::logic_error("File " + filename + " isn't valid");

	xmlFreeTextReader(Reader);

	//File validation OK

} catch (std::exception &exc) {
	throw std::logic_error(exc.what());
} catch (...) {
	throw std::logic_error("Unknown Exception When trying To Validate " + filename);
}
}

//Check if a node exists inside an xml file
bool XML_Manager::Check_Node_Exists(const string &filename, const char* Option_Name, bool force_validation /*=0*/)
{
try {
	if (force_validation) //the user ask for file validation
	{
		Validate_File(filename);
	}

	//node name
	const xmlChar *node_name;
	//parse file
	xmlTextReaderPtr Reader = xmlReaderForFile( filename.c_str(), NULL, XML_PARSE_NOBLANKS);
	//read the 1st node
	int Read_Node = xmlTextReaderRead(Reader);
	//loop while there is nodes
	while ( Read_Node == 1)
	{
		node_name = xmlTextReaderConstName(Reader);
		//check the current node for the option
		if (! xmlStrcmp( node_name, (const xmlChar*)Option_Name ) )
		{
			//node found
			xmlFreeTextReader(Reader); //free memory
			return true;
		}

		//read the next node
		Read_Node = xmlTextReaderRead(Reader);
	}

	//node not found
	xmlFreeTextReader(Reader);
	return false;

}
catch (std::exception &exc)
{
	throw std::logic_error(exc.what());
}
catch (...)
{
	throw std::logic_error("Error When Cheking Node Existance In File: " + filename );
}
}

//Get an option value string from an xml file and throw an error when option not found
std::string XML_Manager::Get_Option_String(const string &filename, const char* Option_Name, bool force_validation /*=0*/)
{
try {
	//result
	string res;

	if (force_validation) //the user ask for file validation
	{
		Validate_File(filename);
	}

	//node name & value
	const xmlChar *node_name, *node_value;
	//parse file
	xmlTextReaderPtr Reader = xmlReaderForFile( filename.c_str(), NULL, XML_PARSE_NOBLANKS);
	//read the 1st node
	int Read_Node = xmlTextReaderRead(Reader);
	//loop while there is nodes
	while ( Read_Node == 1)
	{
		node_name = xmlTextReaderConstName(Reader);
		//check the current node for the option
		if (! xmlStrcmp( node_name, (const xmlChar*)Option_Name ) )
		{
			//option found
			Read_Node = xmlTextReaderRead(Reader); //read the next node: the one containing the value
			node_value = xmlTextReaderConstValue(Reader); //get the node's value
			res =  (string)(const char*)node_value; //save the value
			xmlFreeTextReader(Reader); //free memory
			return res; //return the final clean string
		}

		//read the next node
		Read_Node = xmlTextReaderRead(Reader);
	}

	//option not found
	xmlFreeTextReader(Reader);
	throw std::logic_error("Option: " + (string)Option_Name + " Not Found In File: " + filename );

}
catch (std::exception &exc)
{
	throw std::logic_error(exc.what());
}
catch (...)
{
	throw std::logic_error("Unknow Error When Trying To Get Option: " + (string)Option_Name + " From File: " + filename );
}
}

//Get an option value from an xml file when the option is an int and throw an error when option not found
int XML_Manager::Get_Option_Value(const string &filename, const char* Option_Name, bool force_validation /*= 0*/)
{
try {
	int res = -1;
	string str_res = Get_Option_String(filename, Option_Name, force_validation);
	if ( str_res != "")
		std::stringstream( str_res ) >> res;
	

	return res; //return the option

}
catch (std::exception &exc)
{
	throw std::logic_error(exc.what());
}
catch (...)
{
	throw std::logic_error("Unknow Error When Trying To Get Option Value: " + (string)Option_Name + " From File: " + filename );
}
}

//Get an option value from an xml file when the option is a long and throw an error when option not found
long XML_Manager::Get_Option_Value_Long(const string &filename, const char* Option_Name, bool force_validation /*= 0*/)
{
try {

	long res = -1;
	string str_res = Get_Option_String(filename, Option_Name, force_validation);
	if ( str_res != "")
		std::stringstream( str_res ) >> res;

	return res;

}
catch (std::exception &exc)
{
	throw std::logic_error(exc.what());
}
catch (...)
{
	throw std::logic_error("Unknow Error When Trying To Get Option Value Long: " + (string)Option_Name + " From File: " + filename );
}
}
