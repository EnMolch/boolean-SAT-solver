#include "parser.h"

char parser::peek()
{
	int i = 1;
	while(input[index + i] == ' ')
	{
		i++;
	}
	return input [index + i];
}

char parser::get()
{
	char ret = input [index];
	this->index++;
	return ret;
}


