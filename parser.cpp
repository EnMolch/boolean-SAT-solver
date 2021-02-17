#include "parser.h"

char parser::peek()
{
	return input [index+1];
}

char parser::get()
{
	char ret = input [index];
	this->index++;
	return ret;
}


