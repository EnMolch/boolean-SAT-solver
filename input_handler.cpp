#include "input_handler.h"
#include "string_processing.h"
//implement the methods of the string-class
string_processing::string::string(char* address) : first_char(address){}

int string_processing::string::strlen()
{
	// iterate through the characters, counting up till a zero Byte
	int len = 0;
	int iterator = this.first_char;
	while (iterator != NULL)
	{
		len++;
		iterator = iterator[1];
	}
	return len;
}

int string_processing::string::stringcompare(string &comp_str)
{
	// compare current string with comp_str and return 1 if they are equal, else return 0
	int max_len = this.strlen()
	if (max_len != comp_str.strlen()) return 0; //check for equal length
	else
	{
		for (int i = 0; i<max_len;i++)
		{
			if(this.first_char[i] != comp_str.first_char[i])
				return 0;	
		}	
		return 1; //only if they have equal length and are equal in all spots, return true
	}
}

