#include "syntax_tree.h"
#include "lexer.h"
#include "string_processing.h"
#include <iostream>

syntax_tree::syntax_tree(int* all_tokens, char** all_variables, int num_var)
{
	// initialisierung der Klassenattribute
	tokens = all_tokens;
	variables = all_variables;
	root = new tree {0,0,0};
	number_of_variables = num_var;
	number_distinct_variables = 0;
	int increment=1;
	for(int i = 0; i<number_of_variables;i++)
	{
		char* current_var = variables[i];
		for(int j=i+1; j<number_of_variables;j++) // schleife bis zum Arrayende
		{
			if(string_processing::stringcompare(current_var,variables[j]))
			{
				increment = 0;
			}
		}
		number_distinct_variables += increment;
		increment = 1;
	}
	std::cout <<"Anzahl einzigartiger Variablen: " << number_distinct_variables << " von 64" << std::endl;
	convert_variable_to_name(); // dictionary für index der Variable in tokens zum index in namen
	convert_name_to_value(); // dictionary für den index in namen zu Arrayposition
	int i = 0;
	int iterator = tokens[i];
	while (iterator != end_of_string)
	{
		if(iterator == variable)
		{
		std::cout << name_to_value.find(variable_to_name.find(i)->second)->second << std::endl;
		}
		i++;
		iterator = tokens[i];
	}
}

syntax_tree::~syntax_tree()
{	
	// fange bei der Wurzel an zu löschen
	remove_branch(root);
}

void syntax_tree::convert_variable_to_name()
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

void syntax_tree::convert_name_to_value()
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
int syntax_tree::find_first_entry(int index)
{
	int index_in_name_of_first = first_instance(variables[index]); //ermittle die index der ersten instanz in name
	return name_to_value.find(index_in_name_of_first)->second; // gib den beim Name stehenden bitset index 
}

int syntax_tree::first_instance(char* variable_name)
{
	// gib den index der ersten instanz zurück, falls nicht vorhanden gib -1 zurück
	for (int i = 0; i<number_of_variables; i++)
	{
		if(string_processing::stringcompare(variables[i], variable_name)) return i;
	}
	return -1; 	// hierzu wird es nie kommen, falls aber ein fehler auftritt, lässt er sich hier erkennen
}

int syntax_tree::find_matching_paren(int index)
{
	// gibt den index der passenden öffnenden / schließenden Klammer oder -1 zurück
	// könnte durch andere Datenstrukturen effizienter werden, für maximal 64 variablen aber ausreichend

	int paren_tracker = 0;
	int first_flag = 1;
	if(tokens[index] == paren_open)
	{
		while (paren_tracker != 0 || first_flag == 1)	
		{
			if (tokens[index] == paren_open)
			{
				paren_tracker++;
				first_flag = 0;
			}

			else if(tokens[index] == paren_close)
			{
				paren_tracker--;
				first_flag = 0;
			}
			index++;
		}
		return index-1;
	}
	
	else if(tokens[index] == paren_close)
	{
		while (paren_tracker != 0 || first_flag == 1)	
		{
			if (tokens[index] == paren_open)
			{
				paren_tracker++;
				first_flag = 0;
			}

			else if(tokens[index] == paren_close)
			{
				paren_tracker--;
				first_flag = 0;
			}
			index--;
		}
		return index+1;

	}
	else return -1;
	index++;
}

int syntax_tree::remove_branch(tree* node)
{
	// rekursives löschen aller Kind-Knoten um den ganzen Ast zu löschen
	if (node->left != 0)
	{
		std::cout << "removing left branch" << std::endl;
		remove_branch(node->left);
	}
	
	if(node->right != 0)
	{
		std::cout << "removing right branch" << std::endl;
		remove_branch(node->right);
	}
	std::cout << "deleting a father node" << std::endl;
	delete [] node;
	return 0;
}

tree* syntax_tree::append_node(tree* node, int direction, int data)
{
	// Anfügen eines Elementes an einen bekannten Knoten
	tree* ret = new tree {0, 0, 0};
	if(direction == DIR_LEFT) node->left = ret;
	else if (direction == DIR_RIGHT) node->right = ret;
	ret->data = data;
	return ret;
}

tree* syntax_tree::get_root(){return root;}

void syntax_tree::print_tree(tree* branch)
{
	std::cout<< "data: "<<branch->data << std::endl;
	if(branch->left != 0)print_tree(branch->left);
	if(branch->right != 0)print_tree(branch->right);
}

tree* syntax_tree::chroot(int direction, int data)
{
	// direction -> in welche Richtung die alte Wurzel soll
	// data: datenpart der neuen Wurzel
	tree* ret = new tree {0,0,0};
	if(direction == DIR_LEFT) ret->left = root;
	else if (direction == DIR_RIGHT) ret->right = root;
	ret->data = data;
	root = ret;
	return ret;
}

int syntax_tree::get_bitset_index(int index)
{
	return this->name_to_value.find(this->variable_to_name.find(index)->second)->second;
}

int syntax_tree::find_next_binary_operator(int index)
	{
		int iterator = index +1;
		int current_token = tokens[iterator];
		while(current_token != operator_or && current_token != operator_and)
		{
			if (current_token == end_of_string) return -1; // falls keiner folgt return -1
			iterator++;
			current_token = tokens[iterator];
		}
		return iterator;	// return den Index des nächsten binären Operators
	}

tree* syntax_tree::convert_no_parens(int index, tree* previous)
{
	// darauf ausgelegt, durch Operatoren zu iterieren beim callen
	tree* ret;
	switch(tokens[index])
	{
		case variable:

			if(tokens[index-1] == operator_not)
			{
				// baue den Baum von "unten" -> erst die variable ,dann das Not
				tree* var_tree = new tree {get_bitset_index(index), 0, 0};
				ret = new tree{operator_not,0,var_tree};
				return ret;	  
			}

			else
			{
				ret = new tree {get_bitset_index(index),0,0};
				return ret;
			}


		case operator_or:

			ret = new tree{operator_or,previous,convert_no_parens(find_next_binary_operator(index),0)};
			return ret;


		case operator_and:
			
			if (previous == 0)
			{
				ret = new tree{operator_and, convert_no_parens(index-1, 0), convert_no_parens(index+1,0)};
			}	
			ret = new tree{operator_and, previous, convert_no_parens(index+1,0)};
			return ret;

		case operator_not:
			return convert_no_parens(index+1,0);
			 
	}
	return 0;
}

tree* syntax_tree::do_first_tokens()
{
	int first_token = tokens[0];

	if(first_token == variable) return new tree{get_bitset_index(0),0,0};
	else if (first_token == operator_not)
	{
		tree* var = new tree{get_bitset_index(1), 0, 0};
		tree* ret = new tree{operator_not, 0, var};
		return ret;
	}
	return 0;
}

tree* syntax_tree::do_stuff(int start)
{
	tree* new_root = convert_no_parens(start, do_first_tokens());
	remove_branch(root);
	root = new_root;
	return root;
}
/*
void syntax_tree::convert_to_tree()
{
	tree* start = handle_first_expr(0);
}

tree* handle_first_expr(int index)
{	
	int token = tokens[index];
	switch (token)
	{
		case variable:
			// prüfen des folgenden Operators
			if (tonkens[index+1] == operator_or) ret = new tree {operator_or,0,0};
			else ret = new tree {operator_and,0,0};

			// zuordnung variable zu name bzw array - index
	}
}
*/



/*tree* syntax_tree::convert_leaf_expression(int operator_type, int left, int right)
{
	// Parameter: Operator für den Typ des binären Operators
	// 	      left für die linke Seite des Operators 
	// 	      right für die rechte Seite bzw den nicht - operator
	// 	      left und right müssen "expresssions", also variablen oder wahrheitswerte
	switch (operator_type)
	{
		ret = new tree {0,0,0};
		case operator_or:
			ret->data = operator_or;
			ret->left = new tree {left, 0,0};
			ret->right = new tree {right,0,0};
			return ret;
	
		case operator_and:
			ret->data = operator_and;
			ret->left = new tree {left,0,0};
			ret->right = new tree {right,0,0};
			return ret;

		case operator_not:
			ret->data = operator_not;// Im falle einer Negation wird nur der rechte Ast weiter geführt
			ret->right = new tree {right,0,0};
			return ret;
	}
// Der hier zurückgegebene Zeiger kann an bestehende Bäume angehängt werden, um sie zu beenden.	
}*/
