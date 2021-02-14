// main File, call the parser and be the entry point for the programm
// Here be code
//
#include "string_processing.h"
#include<stdio.h>
int main(int argc, char* argv[])
{
	int a = string_processing::strlen(argv[0]);
	a = string_processing::stringcompare("test" , "test");
	printf("%d",a);
	return 0;
}
