#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <bitset>
#include "syntax_tree.h"

class evaluator
{
	private: 
		tree* root;
		int number_distinct_variables;
		std::bitset <64> truth_values;
		char** variables;
		long int truth_value_counter;

	public:
		evaluator(tree* , int, char**);
		int eval_node(tree* );
		void fully_evaluate_tree(tree* node);
		void print_current_eval(int result);

};

#endif
