// Der eigentliche Parser für die Sprache boolescher Ausdrücke, Endprodukt ist ein Syntaxbaum auf dem Heap
// Tim Heckenberger

#include "syntax_tree.h"
#include "string_processing.h"
#include <stdlib.h>	// für den Exit -call
#include <iostream>

interpreter::interpreter(int * all_tokens, char** all_variables, int number)
{

	tokens = all_tokens;	// benötigt vorarbeit des Lexers
	variables = all_variables;
	number_of_variables = number;	
	global_index =0;
	number_distinct_variables = 0;


	// berechnet wie viele verschiedene Variablen existieren
	int increment=1;
	for(int i = 0; i<number_of_variables;i++)
	{
		char* current_var = variables[i];
		for(int j=i+1; j<number_of_variables;j++)
		{
			if(string_processing::stringcompare(current_var,variables[j])) increment = 0;
		}
		number_distinct_variables += increment;
		increment = 1;
	}

	convert_variable_to_name();	// setze den index im Token-Array mit dem Namen in Verbindung
	convert_name_to_value(); 	// Verbinde den Namen mit dem Index im Bitset
}

void interpreter::step_foreward()
{
	if(tokens[global_index] != end_of_string)
	{
	global_index++;		// inkrementiere den Index des momemtanen Tokens
	}
}

tree* interpreter::elementary_truth_val()
{
	// Terminal der Grammatik -> 1, 0 oder eine Variable
	// eine Variable, 0, oder 1
	tree* ret;
	switch(tokens[global_index])
	{
		// Konstriere die Passenden Bäume
		// Baumstruktur: (Data, links, rechts), Data ist ein Terminal der Grammatik
		case variable:
			ret = new tree{get_bitset_index(global_index), 0, 0};
			break;

		case var_true:
			ret = new tree{var_true, 0, 0};
			break;

		case var_false:
			ret = new tree{var_false, 0, 0};
			break;

		case paren_open:
			step_foreward();	// in einer Klammer steht der allgemeinste Ausdruck
			ret = or_expression();
			if (tokens[global_index] != paren_close)
			{
				std::cout<< "Error Klammersetzung" << std::endl;
			}

			else 
			{
				step_foreward();
				return ret;
			}

		default:
			std::cout << "error" << std::endl;
			exit(1);
	}

	step_foreward();
	return ret;
}


tree* interpreter::truth_val()
{
	// ein Wahrheitswert ist ein elementarer Wert mit optionalen ! vorne
	int count = 0;
	while(tokens[global_index] == operator_not)
	{
		count++;	
		step_foreward();
	}
	
	if(!((count % 2) == 0))
	{
		tree* ret = new tree {operator_not, 0,0};
		ret->right = elementary_truth_val(); // sollte später expr callen
		return ret;
	}
	return elementary_truth_val();	
}


tree* interpreter::and_term()
{
	// ein and_term ist eine konjunktive verknüpfung von wahrheitswerten
	tree* left = truth_val();
	while(tokens[global_index] == operator_and)
	{
		int center = operator_and;
		step_foreward();
		tree* right = truth_val();
		// ((A&B)&C) würde hier aus A&B&C
		left = new tree{center, left, right};	
		// der Trick, dass das alte "und" das linke Kind des neuen wird erlaubt das beliebige verschachteln
	}
	return left;
}

tree* interpreter::or_expression()
{
	// die Or-Expression ist das allgemeinste Konstrukt, da or die geringste Priorität hat
	// demnach ruft or_expression auch alle nichtterminale mit höherer Priorität auf
	tree* left = and_term();
	while(tokens[global_index] == operator_or)
	{
		int center = operator_or;
		step_foreward();
		tree* right = and_term();
		left = new tree{center, left, right};
	}
	return left;
}

interpreter::~interpreter()
{	
	// fange bei der Wurzel an zu löschen
	remove_branch(root);
}

tree* interpreter::parse_tokens()
{
	// Startsymbol ist die allgmeinste Form in der Grammatik: ein oder - Knoten
	root = or_expression();
	return root;
}

void interpreter::convert_variable_to_name()
{
	// in den Lexer Tokens steht lediglich ob das Token eine Variable ist, der Name steht separat, daher müssen diese verknüpft werden	
	if (number_of_variables > 0) // bei 0 variablen muss nichts getan werden
	{

		int iterator = 0; // für das Iterieren durch alle Tokens
		int variable_counter = 0; // für das speichern des indexes in namen
		int element  = tokens[iterator];
		while(element != end_of_string) // iterieren durch alle Tokens um die indezes der variablennamen zu finden
		{
			if(element == variable)
			{
				this->variable_to_name.insert(std::pair <int,int>(iterator, variable_counter));
				variable_counter++;
			}
			iterator++;
			element = tokens[iterator];
		}
	}
}

void interpreter::convert_name_to_value()
{
	if(number_of_variables > 0)
	{
		int bitset_positions[64];
		int track_uniqueness = 0; // nachvollziehen der ausgelassenen Indizes
		for (int i = 0; i<number_of_variables;i++)
		{
			if (first_instance(variables[i]) == i)
			{
				this->name_to_value.insert(std::pair <int,int>(i, track_uniqueness));
				track_uniqueness++;
			}
			else
			{
				this->name_to_value.insert(std::pair <int,int>(i, find_first_entry(i)));
			}
		}	
	}
}


int interpreter::remove_branch(tree* node)
{
	// rekursives löschen aller Kind-Knoten um den ganzen Ast zu löschen
	if (node->left != 0)
	{
		remove_branch(node->left);
	}
	
	if(node->right != 0)
	{
		remove_branch(node->right);
	}
	delete [] node;
	return 0;
}

int interpreter::get_bitset_index(int index)
{
	// ordne erst den Variablenindex zum Namen zu und dann den Namen zum Wert.
	return this->name_to_value.find(this->variable_to_name.find(index)->second)->second;
}

int interpreter::get_distinct_vars()
{
	return number_distinct_variables;
}

int interpreter::find_first_entry(int index)
{
	int index_in_name_of_first = first_instance(variables[index]); //ermittle die index der ersten instanz in name
	return name_to_value.find(index_in_name_of_first)->second; // gib den beim Name stehenden bitset index 
}

int interpreter::first_instance(char* variable_name)
{
	// gib den index der ersten instanz einer Variable zurück, falls nicht vorhanden gib -1 zurück
	for (int i = 0; i<number_of_variables; i++)
	{
		if(string_processing::stringcompare(variables[i], variable_name)) return i;
	}
	return -1; 	// Compilerwarnung unterdrücken, hierzu wird es aber aufgrund des Aufbaus nie kommen
}


