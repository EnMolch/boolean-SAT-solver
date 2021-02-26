#ifndef LEXER_H
#define LEXER_H

#include "parser.h"
#include "stack.h"
#include "string_processing.h"
// status soll auch für das restliche Programm verständlich sein
enum lexer_status {
	
	error,
	correct,
	variable,
	operator_or,
	operator_and,
	operator_not,
	paren_open,
	paren_close,
	var_true,
	var_false,
	end_of_string
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
		int max_size; 	// länge des Eingabestrings
		char** name_of_vars;
		int var_counter; // Zähler für Variablen
		string var;	// container für das Zusammenbauen von Variablen
			

	public:
		lexer(const char* input);
		~lexer();
		int validate_parens();		// validieren der Klammersetzung 
		int lex();			// konsumeiere einige Chars des Inputs und gebe ein Token zurück
		int* lex_completely();		// den Lexer auf den ganzen Input anwendeun



		// helferfunktionen für die Übersichtlichkeit des Lexers
		int is_binary_op(char test);
		int validate_op (char test); // testet Bedingungen für das korrekte Verwenden von Operatoren
		int validate_var (char test); // testet Bedingungen für das korrekte Verwenden von Variablen
		int is_ascii_letter (char test);	

		//getter
		char** get_names();
/*Grammatik-Regeln des Lexers:
 * Nach einer ')' darf alles stehen -> kein lookahead nötig
 * Nach einer '(' darf alles außer ein binärer Operator oder eine ’)’ stehen
 * Nach einer variable darf nur ein binärer Operator oder eine ')' 
 * Nach einem '!' darf alles außer ein binärer Operator oder eine ')' stehen.
 * nach einem binären Operator darf kein anderer binärer Operator stehen und keine ')'
 * Wahrheitswerte sind äquivalent zu variablen
 *
 * Diese Regeln werden bereits im lexer verifiziert und werfen bei falscher Verwendung einen Fehler
 * konventionell würde dies erst danach geschehen, die Grammatik hier ist aber simpel genug um mit einen char
 * lookahead direkt die syntax prüfen zu können.
 * */

};


#endif
