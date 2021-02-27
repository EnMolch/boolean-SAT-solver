#include <iostream>
#include "lexer.h"
int main()
{
	const char* test = "(A&B|C&!(A|C))";
	// A && B || C && !(A || C)
	lexer lex(test);
	int* lexemes = lex.lex_completely();
	char** vars = lex.get_names();
}

// c++ prioritäten:
// größte (zuert ausgeführt):
// !
// &&
// ||
