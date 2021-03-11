// Das ist ein Lexer. Er rekonstruiert eine programminterne Darstellung der eingegebenen Formel. Diese wird zur Evaluirung benutzt
// Tim Heckenberger
#include "lexer.h"
#include "stack.h"
#include "string_processing.h"
#include <iostream>

lexer::lexer(const char* str):reader(str)	// der Lexer ist ein reader mit Logik für jedes Zeichen
{
	var_counter = 0;
	max_size = string_processing::strlen(str);
	name_of_vars = new char* [max_size]; 
	lexemes = new int [max_size]; // tokens sind mit integern codiert
}

lexer::~lexer()
{
	int i = 0;
	char* current_var  = name_of_vars[0];
	while (current_var != 0) // freigeben der in "name_of_vars" referenzierten strings
	{
		i++;
		delete [] current_var;
		current_var = name_of_vars[i];
	}
	delete [] name_of_vars;
}

char** lexer::get_names(){return name_of_vars;}

int lexer::validate_parens()
{
	// benutzt einen Stack für das Prüfen der Klammersetzung
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
	index = 0; 	// index muss am Ende zurückgesetzt werden
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
	// Zeichen, die auf eine Variable folgen
	return ( (test == ')') || (test == '&') || (test == '|') | (test == '\0') | (test == 10));
}

int lexer::is_ascii_letter(char test)
{
	// reichweite für die Groß- und Kleinbuchstaben in Ascii prüfen
	return ( ((test >= 0x41) && (test <= 0x5a)) || ((test>= 0x61) && (test <= 0x7a)) );
}

int lexer::validate_start(char test)
{
	// Zeichen, die am Anfang stehen dürfen
	return (is_ascii_letter(test) || test == '!' || test =='(' || test == '0' || test == '1');
}


int lexer::lex() // gebe einen Code zurück und verfolständige gegebenenfalls das Variablenverzeichniss
{
/*	Iteriert chracter für character den String, außer bei variablen, diese werden direkt konsumiert.
 *	alles andere kann durch den Status - Code identifiziert werden.
 * */	
	char next_char = peek(); // nächstes Zeichen auf dem Input
	char next_value = peek_non_blanc(); // nächstes nicht whitespace- Zeichen
	char current_value = get(); 	// jetziges Zeichen

	// Alle Fälle durchgehen und passende Codes zurückgeben
	

	if(this->index == 1)	// sonderfall Anfang
	{
		if (!(validate_start(current_value))) return error;
	}

	if(next_value == 0 || next_value == 10)	//sonderfall Ende
	{
		if(!(is_ascii_letter(current_value) || current_value == ')' || current_value == '1' || current_value == '0'|| current_value==10)) return error;
	}

	if (current_value != 0 && current_value != 10) // 0 und 10 sind ascii-codes für das Ende von Strings
	{	
		switch (current_value)
		{

			case '(':  // danach darf alles außer ein binärer Operator stehen
				// konstrukte wie () () () (!1 & A) müssen entfernt werden
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
			
			case 9:
				return (lex()); // Tablulator wird auch übersprungen

			default:
				// erlaubt sind nur Buchstaben in Ascii, daher wird dies hier geprüft
				if ( is_ascii_letter(current_value))
				{
					var.append(current_value);
					while (is_ascii_letter(next_char)) // setze die Variable zusammen
					{
						next_char = peek(); 	// whitespace berücksichtigen um zu trennen
						next_value = peek_non_blanc(); // syntaxregeln beachten
						char following_char = get();
						var.append(following_char);
					}

					if (validate_var(next_value)) // darf nur konsumieren, wenn die Grammatik stimmt
					{
						name_of_vars[var_counter] = var.convert(); 
						var_counter++; // index für die nächste Variable
						var.reset();
						return variable;
					}	
					var.reset();
					return error;

				}
				return error;  // keine der oberen Chars oder kein Ascii Buchstabe ist ein Fehler
		}
	}
	return end_of_string;

}

int lexer::get_number_of_variables() {return var_counter;}

int* lexer::lex_completely()
{
	// iteriere durch alle Zeichen und appliziere den Lexer
	int status = 1;
	int position = 0;	// position der Tokens im array
	while (status != error && status != end_of_string)
	{
		status = lex();
		lexemes[position] = status;
		position++;
	}

	if(status == error) 
	{
		// räume im Fehlerfall auf und beende das Programm
		delete [] lexemes;
		std::cout << "Syntaxfehler!" << std::endl;
		exit(1);
		return 0;
	}

	else
	{
		return lexemes;
	}
}
