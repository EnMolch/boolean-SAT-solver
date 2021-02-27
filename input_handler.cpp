#include "string_processing.h"
#include<iostream>
#include<fstream>
#include "input_handler.h"
const char* USAGE_STRING = "Usage:  ./main Equation | -f filepath | -h";

using namespace string_processing;

int get_inputs(int count, char** values)
{
// handler für Kommandozeilenparameter

	// gibt Flags für die Inputs zurück
	if (count == 1 || count > 3)
	{
		std::cout << USAGE_STRING << std::endl;
		return NO_INPUT;
	}
	else
	{
		if (stringcompare(values[1], "-h"))
		{
			std::cout << USAGE_STRING << std::endl;	
		
		}
		else if(stringcompare(values[1], "-f"))	
		{
			return FILE_INPUT;
		}

		else if(count == 2) //return the direct input only if there is 1 parameter
		{
			return DIRECT_INPUT;
		}
		std::cout << "Falsche Eingabe, kein Input!"<<std::endl;
		return NO_INPUT;
	}
}

char* get_direct_input(char** values)
{
	return values[1];	
}

char* get_file_input(char** values)
{
	std::ifstream input_file;
	std::cout << "öffne Datei: " << values[2] << std::endl;
	input_file.open(values[2], std::ifstream::ate); // öffne die Datei am Ende um die Länge herauszufinden
	if(!input_file)
	{
		std::cout << "konnte Datei nicht öffnen!" << std::endl;
		return 0;
	}
	int file_size = input_file.tellg(); // länge der Datei bestimmen
	std::cout << "länge des Files " << file_size << std::endl;
	char* input_string = new char[file_size];
	input_file.close();
	input_file.open(values[2], std::ifstream::in);
	input_file.read(input_string, file_size);
	input_file.close();
	return  input_string;
}
