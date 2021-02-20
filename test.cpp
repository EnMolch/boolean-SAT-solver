#include "checker.h"
#include <iostream>

int main(int argc, char** argv)
{
	const char* test = "()()((()))()(AAAA)1232())";
	checker check(test);
	int a = check.validate();
	std::cout << a << std::endl;
	return 0;
}
