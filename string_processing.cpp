#include <cstddef>
#include "string_processing.h"
//implement the methods of the string-class
int string_processing::strlen(const char* first_char)
{
	// iterate through the characters, counting up till a zero Byte
	int len = 0;
	const char* iterator = first_char;
	while (iterator[len] != 0)
	{
		len++;
	}
	return len;
}

int string_processing::stringcompare(const char* string1, const char* string2)
{
	// compare current string with comp_str and return 1 if they are equal, else return 0
	int max_len = strlen(string1);
	if (max_len != strlen(string2)) return 0; //check for equal length
	else
	{
		for (int i = 0; i<max_len;i++)
		{
			if(string1[i] != string2[i])
				return 0;	
		}	
		return 1; //only if they have equal length and are equal in all spots, return true
	}
}

