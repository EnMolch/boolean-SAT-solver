// Handlerfunktionen für die Kommandozeilenparameter
// Tim Heckenberger

#include "string_processing.h"
#include<iostream>
#include<fstream>
#include <stdlib.h>
#include "input_handler.h"
const char* USAGE_STRING = "Usage:  ./main Equation | -f filepath | -h";

using namespace string_processing;

int get_inputs(int count, char** values)
{
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

		else if(count == 2) // bei einem Parameter liegt ein direkter Input vor
		{
			return DIRECT_INPUT;
		}
		std::cout << "Falsche Eingabe, kein Input!"<<std::endl;
		return NO_INPUT;
	}
}

char* get_file_input(char** values)
{
	// Bei Dateieingabe wiird der String in der Datei zurückgegeben
	std::ifstream input_file;
	input_file.open(values[2], std::ifstream::ate); // öffne die Datei am Ende um die Länge herauszufinden
	if(!input_file)
	{
		std::cout << "konnte Datei nicht öffnen!" << std::endl;
		exit(1);
		return 0;
	}
	int file_size = input_file.tellg(); // länge der Datei bestimmen
	char* input_string = new char[file_size];
	input_file.close();
	input_file.open(values[2], std::ifstream::in);
	input_file.read(input_string, file_size);
	input_file.close();
	return  input_string;
}
