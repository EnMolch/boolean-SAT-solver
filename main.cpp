// main File, call the parser and be the entry point for the programm
// Here be code
//
#include "string_processing.h"
#include "input_handler.h"
#include <iostream>

int main(int argc, char* argv[])
{
	int status_code = get_inputs(argc, argv);
	switch (status_code)
	{
		case NO_INPUT:
			return 0;

		case DIRECT_INPUT:
			return 0;

		case FILE_INPUT:
			// TODO nicht vergessen, am Ende den input zu DELETEN!
			char* input = get_file_input(argv);
			std::cout << "input contents: " << input << std::endl;
			delete [] input;
			return 0;
	}
	return 0;
}
