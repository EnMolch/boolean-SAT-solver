#include "stack.h"
#include <iostream>

int main(int argc, char** argv)
{
	stack test;
	test.push('a');
	std::cout << test.pop() << std::endl;
	std::cout << test.pop() << std::endl;
	return 0;
}
