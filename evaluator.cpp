#include "evaluator.h"
#include "lexer.h"
#include <iostream>

evaluator::evaluator(tree* root, int distinct_vars)
{
	this->root = root;
	this->number_distinct_variables = distinct_vars;
	truth_value_counter = 0;
}

void evaluator::print_current_eval(int result)
{
	// Ausgabe für einen Durchlauf des Syntaxbaumes mit einer bestimmten Belegung
	std::cout << "- ";
	for(int i = 0; i<number_distinct_variables;i++)
	{
		std::cout << "- ";
	}
	std::cout<<"-"<<std::endl;
	std::cout<<"| "<< truth_values[0];
	for(int i = 1; i<number_distinct_variables-1;i++)
	{
		std::cout << " " << truth_values[i];
	}
	std::cout<<" " << truth_values[number_distinct_variables-1] << " |";
	std::cout<<" " << "->" << result << std::endl;
}

int evaluator::eval_node(tree* node) // rückgabewert ist der evaluierte Ausdruck ab dem Node
{
	// Evaluiere den Baum ab einem Knoten
	int left;
	int right;
	if(node->left != 0) 
	{
		left = eval_node(node->left);
	}

	if(node->right != 0)
	{
		right = eval_node(node->right);
	}


	switch(node->data)
	{
		case operator_or:
			return (left or right);

		case operator_and:
			return (left and right);

		case operator_not:
			return (not right);

		case var_true:
			return 1;

		case var_false:
			return 0;

		default:
			return truth_values[node->data]; // Alles andere ist eine variable / wahrheitswert
	}
	
}

void evaluator::fully_evaluate_tree(tree* node)
{
	int maximum_counter_value = 1 << number_distinct_variables;
	while(truth_value_counter < maximum_counter_value)
	{
		this->truth_values = std::bitset <64>(truth_value_counter);
		print_current_eval(eval_node(root));
		truth_value_counter++;	// hochzählen geht nacheinander alle möglichen Kombinationen der Variablen durch
	}
}
