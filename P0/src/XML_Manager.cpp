#include "XML_Manager.hh"

//clean everything related to libxml2
void XML_Manager::Clean_Up()
{
	xmlCleanupParser(); //Cleanup function for the XML library.
	xmlMemoryDump(); //Debug memory for regression tests
}

//parse a file and validate it: check file exist, validate file vs is dtd, check pedantic error
bool XML_Manager::Validate_File(const string &filename)
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

	return true; //file validated

} catch (std::exception &exc) {
	cout << exc.what() << endl;
    return false; //file is not valid
} catch (...) {
	cout << "Unknown Exception" << endl;
    return false; //eror occured
}
}

std::string XML_Manager::Get_Option_String(const string &filename, const char* Option_Name, bool force_validation /*=0*/)
{
try {
	//result
	string res;

	if (force_validation) //the user ask for file validation
	{
		if (! Validate_File(filename) )//validate the file
		{
			cout << "Error when reading file: " << filename << endl;
			return res; //invalid file
		}
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
	cout << "Option " << Option_Name << " Not Found In File " << filename << endl;
	return res;


} catch (...) {
	cout << "Error when reading file: " << filename << endl;
	return ""; //error occured
}
}

int XML_Manager::Get_Option_Value(const string &filename, const char* Option_Name, bool force_validation /*= 0*/)
{
	int res = -1;
	string str_res = Get_Option_String(filename, Option_Name, force_validation);
	if ( str_res != "")
		std::stringstream( str_res ) >> res;
	

	return res;
}

long XML_Manager::Get_Option_Value_Long(const string &filename, const char* Option_Name, bool force_validation /*= 0*/)
{
	long res = -1;
	string str_res = Get_Option_String(filename, Option_Name, force_validation);
	if ( str_res != "")
		std::stringstream( str_res ) >> res;

	return res;
}
