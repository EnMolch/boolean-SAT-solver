#include "reader.h"

char reader::peek_non_blanc()
{
	int i = 1;
	while(input[index + i] == ' ')
	{
		i++;
	}
	return input [index + i];
}


char reader::peek()
{
	return input [index + 1];
}

char reader::get()
{
	char ret = input [index];
	this->index++;
	return ret;
}


