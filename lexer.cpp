// Das ist ein Lexer. Er rekonstruiert eine programminterne Darstellung der eingegebenen Formel. Diese wird zur Evaluirung benutzt
#include "lexer.h"
#include "stack.h"
#include "string_processing.h"
#include <iostream>

lexer::lexer(const char* string):parser(string)
{
	stack tracker();
	int max_size = string_processing::strlen(string);
	//lexemes = new int[max_size];
}

lexer::~lexer()
{
	//delete [] lexemes;
}


int lexer::validate_parens()
{
	// TODO wäre vielleicht effizienter eine Variable zu inc/decrementieren statt nen ganzen Stack aufzubauen
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
	if (test == '@') return correct; // return für den Fall, dass klammern passen
	return error;		//return für den Fall, dass Klammern nicht passen
}

int lexer::is_binary_op(char test)
{

	return ((test == '|')||(test == '&'));
}

int lexer::validate_op(char test)
{
	// auf Operatoren muss eine Variable folgen
	return ((!is_binary_op(test)) && (test != ')'));
}

int lexer::validate_var(char test)
{
	return ( (test == ')') || (test == '&') || (test == '|'));
}

int lexer::is_ascii_letter(char test)
{
	// reichweite für die Groß- und Kleinbuchstaben in Ascii prüfen
	return ( ((test >= 0x41) && (test <= 0x5a)) || ((test>= 0x61) && (test <= 0x7a)) );
}

int lexer::lex() // gebe einen Code zurück und verfolständige gegebenenfalls das Variablenverzeichniss
{
/*	Iteriert einen Character nacheinander den String, außer bei variablen, diese werden direkt konsumiert.
 *	alles andere kann durch den Status - Code identifiziert werden.
 * */
	char next_value = peek();
	char current_value = get();
	
	// Alle Fälle durchgehen und passende Codes zurückgeben
	if (next_value != 0)
	{	
		switch (current_value)
		{
			// TODO eventuell schönere Error codes, also Syntax, illegal char, ...

			case '(':  // danach darf alles außer ein binärer Operator stehen
				// konstrukte wie () () () (!1 & A) müsse später entfernt werden
				if ( (! is_binary_op (next_value)) && next_value != ')' ) return paren_open;
				return error;

			case ')': // danach darf alles stehen
				return paren_close;

			case '!': // danach darf kein ) oder ein binärer Operator stehen
				if (validate_op(next_value)) return operator_not;
				return error;

			case '|':
				if (validate_op(next_value)) return operator_or;
				return error;
			
			case '&':
				if (validate_op(next_value)) return operator_and;
				return error;

			case '1':
				if (validate_var(next_value)) return var_true;
				return error;

			case '0':
				if (validate_var(next_value)) return var_false;
				return error;

			case ' ':
				return (lex()); // leerzeichen werden übersprungen

			default:
				// erlaubt sind nur Buchstaben in Ascii, daher wird dies hier geprüft
				if ( is_ascii_letter(current_value) && validate_var(next_value) ) return variable;
				return error;  // keine der oberen Chars oder kein Ascii Buchstabe ist ein Fehler
		}
	}
	return end_of_string;

}
