#ifndef __SYNTAX__TREE_H
#define __SYNTAX__TREE_H


#define DIR_LEFT 0
#define DIR_RIGHT 1

#include "lexer.h"
#include <map>
struct tree
{
	int data;
	tree* left;
	tree* right;
};

enum exceptions
{
	variable_exception,
	term_exception,
	expression_exception
};
// Ansatz des Implementierens einer Grammatik
class interpreter
{
	private:
		int* tokens;
		char** variables;
		int number_of_variables;
		int number_distinct_variables;
		int last_relevant_token;
		int global_index;
		std::map<int, int> variable_to_name; // index der variable zum index in namen
		std::map<int, int> name_to_value; // index in namen zu position im bitset
		tree* root;

	public:
		interpreter(int * all_tokens, char** all_variables, int number); // nimm tokens und variablen
		~interpreter();

		tree* elementary_truth_val();
		tree* truth_val();
		tree* term();
		tree* expression();
		tree* parse_tokens();

		void convert_variable_to_name();
		void convert_name_to_value();

		int remove_branch(tree* node);
		int get_bitset_index(int index);
		int get_distinct_vars();
		int find_first_entry(int index);
		int first_instance(char* variable_name);

		void advance();
};


#endif
