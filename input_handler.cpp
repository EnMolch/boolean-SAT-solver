#include "string_processing.h"
#include<iostream>
#include "input_handler.h"

const char* USAGE_STRING = "Usage:  ./main Equation | -f filepath | -h";

using namespace string_processing;
int get_inputs(int count, char** values)
{
// function to handle the command line parameters

	// return flags for which opt was used
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
		return NO_INPUT;
	}
}

