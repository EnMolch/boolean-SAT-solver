#include "parser.h"

char parser::peek_non_blanc()
{
	int i = 1;
	while(input[index + i] == ' ')
	{
		i++;
	}
	return input [index + i];
}


char parser::peek()
{
	return input [index + 1];
}

char parser::get()
{
	char ret = input [index];
	this->index++;
	return ret;
}


