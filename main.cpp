// main File, call the parser and be the entry point for the programm
#include "string_processing.h"
#include "input_handler.h"
#include "lexer.h"
#include "evaluator.h"
#include "syntax_tree.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int handle_equation(char* equation)
{
	lexer lex(equation);
	int paren_status = lex.validate_parens();
	if(paren_status == error)
	{
		std::cout << "Fehler in der Klammersetzung! " << std::endl;
		exit(1);
	}
	else
	{
		int* all_tokens = lex.lex_completely();
		char** variables = lex.get_names();
		interpreter interpret(all_tokens, variables, lex.get_number_of_variables());
		tree* root = interpret.parse_tokens();
		evaluator eval(root, interpret.get_distinct_vars(),variables);
		eval.fully_evaluate_tree(root);
		return 0;
	}
}

int main(int argc, char* argv[])
{
	int status_code = get_inputs(argc, argv);
	switch (status_code)
	{
		case NO_INPUT:
			return 0;

		case DIRECT_INPUT:
			return handle_equation(argv[1]);

		case FILE_INPUT:
			// TODO nicht vergessen, am Ende den input zu DELETEN!
			char* input = get_file_input(argv);
			int status = handle_equation(input);
			delete [] input;
			return status;
	}
	return 0;
}
