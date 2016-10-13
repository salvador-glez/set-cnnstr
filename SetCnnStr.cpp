#include "pugixml.hpp"
#include <iostream>
#include <fstream>
#include <ctime>

int main(int argc, char *argv[])
{
    std::ofstream logFile;
	logFile.open("ConfiguradorCadenaConexion.log", std::ofstream::out | std::ofstream::app);

	// current date/time based on current system
	time_t now = time(0);
	
	// convert now to string form
	char* dt = ctime(&now);
	logFile << dt;

    pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(argv[2], pugi::parse_default | pugi::parse_comments);
	pugi::xml_node connectionsStrings = doc.child("configuration").child("connectionStrings");

	for (pugi::xml_node connectionString = connectionsStrings.first_child(); connectionString; connectionString = connectionString.next_sibling())
    {
		std::string t = connectionString.attribute("name").value();
		if (t.compare(argv[1]) == 0)
		{
			logFile << "WebConfig: " << argv[2] << ", Valor: " << connectionString.attribute("connectionString").value() << ", Nuevo valor: " << argv[3] << std::endl;
			logFile << std::endl;
			connectionString.attribute("connectionString").set_value(argv[3]);
		}
	}
	doc.save_file(argv[2]);
	logFile.close();
	return 0;
}