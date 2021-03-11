/*	Klasse zum Evaluieren und Ausgeben der Formel
 *	Tim Heckenberger TIT19
 */

#include "evaluator.h"
#include "lexer.h"
#include <stdlib.h>
#include <iostream>
#include <iomanip>

evaluator::evaluator(tree* root, int distinct_vars, char** variable_names)
{
	this->variables = variable_names;
	this->root = root;
	this->number_distinct_variables = distinct_vars;
	truth_value_counter = 0;
}

void evaluator::print_current_eval(int result, std::bitset<64> truth_values)
{
	// Ausgabe für einen Durchlauf des Syntaxbaumes mit einer bestimmten Belegung
	
	// Der versuch eine Semi-verständliche Tabelle im Terminal zu konstruieren
	for(int i = 0; i<number_distinct_variables;i++)
	{
		std::cout << "---------";
	}
	std::cout<<"-"<<std::endl;
	std::cout<<"| "<<std::setw(8)<< truth_values[0];
	for(int i = 1; i<number_distinct_variables-1;i++)
	{
		std::cout<<std::setw(9) << truth_values[i];
	}
	std::cout<<" " << std::setw(8)<<truth_values[number_distinct_variables-1] << "|";
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
	if(number_distinct_variables > 64)	// ausnahmebehandlung zu viele Variablen
	{
		std::cout<<"es sind nur 64 Variablen maximal erlaubt!"<< std::endl;
		exit(1);
	}

	int maximum_counter_value = 1 << number_distinct_variables;
	
	for (int i = 0; i<number_distinct_variables;i++)
	{
		std::cout<<std::setw(8) <<variables[i]<<"|";
	}

	std::cout<<std::endl;
	if(number_distinct_variables < 10)
	{
		while(truth_value_counter < maximum_counter_value)
		{
			this->truth_values = std::bitset <64>(truth_value_counter);
			print_current_eval(eval_node(root), truth_values);
			truth_value_counter++;	// hochzählen geht nacheinander alle möglichen Kombinationen der Variablen durch
		}
		std::cout << "- ";
		for(int i = 0; i<number_distinct_variables;i++)
		{
			std::cout << "---------";
		}
	}
	else
	{
		int false_flag = 0;	// flags und belegungen für bestimmte Ergebnisse
		std::bitset<64> false_vars;

		int true_flag = 0;
		std::bitset<64> true_vars;

		while(truth_value_counter < maximum_counter_value && ((false_flag && true_flag) == 0))
		{
			this->truth_values = std::bitset<64>(truth_value_counter);
			if(eval_node(root) == 1)
			{
				true_flag = 1;
				true_vars = std::bitset<64>(truth_value_counter);
			}
			else
			{
				false_flag = 1;
				false_vars = std::bitset<64>(truth_value_counter);
			}
			truth_value_counter++;
		}
		// Gebe jeweils eine Belegung aus , falls für etwas keine Belegung existiert, gebe diesen Fakt aus
		
		if(true_flag == 0)
		{
			std::cout<<"keine Belegung für Wahr gefunden! Wiederspruch" <<std::endl;
			print_current_eval(0, false_vars);
		}
		else if(false_flag == 0)
		{
			std::cout<<"Keine Belegung für Falsch gefunden! Tautologie" << std::endl;
			print_current_eval(1, true_vars);
		}

		
		else	// sonst gebe beide Belegungen aus
		{
			print_current_eval(0,false_vars);
			print_current_eval(1,true_vars);
		}
		

	}
	
}
