#include "syntax_tree.h"
#include "lexer.h"
#include <iostream>

syntax_tree::syntax_tree(int* all_tokens, char** all_variables)
{
	tokens = all_tokens;
	variables = all_variables;
	root = new tree {0,0,0};
}

syntax_tree::~syntax_tree()
{	
	// fange bei der Wurzel an zu löschen
	remove_branch(root);
}

int syntax_tree::find_matching_paren(int index)
{
	// gibt den index der passenden öffnenden / schließenden Klammer oder -1 zurück
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

void syntax_tree::convert_to_tree()
{
// von Unten bauen, in der größten verschachtetlungstiefe der Klammern anfagen, rest sollte relativ simpel sein

}

tree* syntax_tree::convert_leaf_expression(int operator_type, int left, int right)
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
}
