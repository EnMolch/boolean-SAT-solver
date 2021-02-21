#ifndef LEXER_H
#define LEXER_H

#include "parser.h"
#include "stack.h"
// status soll auch für das restliche Programm verständlich sein
enum lexer_status {
	
	error,
	correct,
	variable,
	operator_or,
	operator_and,
	operator_not,
	paren_open,
	paren_close
};

class lexer: public parser
{
/*
 * Prüfen der korrekten Syntax und aufbauen einer internen Darstellung
 * Als Algorithmus wird eine Art Kellerautomat verwendet, der einen Stack zur Prüfung verwendet.
 * Nach der Klammerprüfung wird der String übersetzt
 * */
	private:
		stack tracker; // stack struktur um die Klammern zu prüfen
		int* lexemes; // Abstrahiertes Layout der Formel
		

	public:
		lexer(const char* input);
		~lexer();
		//~checker(){~tracker();};
		int validate_parens();		// validieren der Klammersetzung 
		


};


#endif
