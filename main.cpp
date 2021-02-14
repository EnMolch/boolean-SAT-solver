// main File, call the parser and be the entry point for the programm
// Here be code
//
#include "string_processing.h"
#include<stdio.h>
int main(int argc, char* argv[])
{
	string_processing::string test(argv[1]);
	int flag = test.stringcompare("test");
	if (flag == 1)
	{
	 printf("%d",flag);
	}
	return 0;
}
