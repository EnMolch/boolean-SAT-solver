#ifndef __SYNTAX__TREE_H
#define __SYNTAX__TREE_H

// Baumstruktur und Interpreter-Klasse für das Implementieren der Grammatik und Konstruktion des Syntaxbaumes

#include "lexer.h"
#include <map>

// elemntare Baumstruktur
struct tree
{
	int data;
	tree* left;
	tree* right;
};

// Ansatz des Implementierens einer Grammatik
class interpreter
{
	private:
		int* tokens;
		char** variables;
		int number_of_variables;
		int number_distinct_variables;
		int global_index;	// index des momentanen Tokens
		std::map<int, int> variable_to_name; // index der variable zum index in namen
		std::map<int, int> name_to_value; // index in namen zu position im bitset
		tree* root;

	public:
		interpreter(int * all_tokens, char** all_variables, int number); // nimm tokens und variablen
		~interpreter();


		// Grammatik-Methoden

		tree* elementary_truth_val();
		tree* truth_val();
		tree* and_term();
		tree* or_expression();
		tree* parse_tokens();
		void step_foreward();
		
		// variablen-Namensauflösung
		void convert_variable_to_name();
		void convert_name_to_value();
		int get_distinct_vars();
		int find_first_entry(int index);
		int first_instance(char* variable_name);
		int get_bitset_index(int index);

		// entfernen ab einem bestimmten Knoten
		int remove_branch(tree* node);
};


#endif
