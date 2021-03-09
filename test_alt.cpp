#include "syntax_tree.h"
#include "lexer.h"
#include "evaluator.h"
#include <iostream>

int main()
{
	const char* test = "A|B&C&!(A&B)";
	//const char* test = "((A&(B|C)))";
	lexer lex (test);
	int correctness = lex.validate_parens();
	std::cout << "Klammersetzung: " << correctness << std::endl;
	int* all_tokens;
	all_tokens = lex.lex_completely();
	char** variables = lex.get_names();
	std::cout << "Anzahl variablen: " << lex.get_number_of_variables() << std::endl;
	interpreter bomm(all_tokens, variables, lex.get_number_of_variables());
	tree* root = bomm.parse_tokens();
	evaluator eval(root, bomm.get_distinct_vars());
	eval.fully_evaluate_tree(root);
}
