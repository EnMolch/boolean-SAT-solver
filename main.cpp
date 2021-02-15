// main File, call the parser and be the entry point for the programm
// Here be code
//
#include "string_processing.h"
#include "input_handler.h"
#include <stdio.h>

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
			return 0;
	}
	return 0;
}
