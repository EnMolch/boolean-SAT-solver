// Das ist ein Lexer. Er rekonstruiert eine programminterne Darstellung der eingegebenen Formel. Diese wird zur Evaluirung benutzt
#include "lexer.h"
#include "stack.h"
#include "string_processing.h"
#include <iostream>

lexer::lexer(const char* string):parser(string)
{
	stack tracker();
	int max_size = string_processing::strlen(string);
	lexemes = new int[max_size];
}

lexer::~lexer()
{
	delete [] lexemes;
}


int lexer::validate_parens()
{
	char current = 'A'; // inititalisierung kann alles außer 0 sein
	char stop_flag = 1;
	while (current != 0 && stop_flag == 1 )// iteriere durch die ganze Eingabe
	{
		current = get(); // Nach jetzigem Zeichen handeln und den Stack modifizieren
		switch (current)
		{
			case '(':
				tracker.push(1);				
				break;

			case ')':
				stop_flag = tracker.pop();
				break;
		}
	}
	char test = tracker.pop();
	//std::cout << test << std::endl;
	if (test == '@') return correct; // return für den Fall, dass klammern passen
	return error;		//return für den Fall, dass Klammern nich passen
}
