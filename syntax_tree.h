// Klasse, die von Lexertokens zu boolscher Gleichug übrsetzt
#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#define DIR_LEFT 0
#define DIR_RIGHT 1

#include "lexer.h"

struct tree
{
	int data;
	tree* left;
	tree* right;
};


class syntax_tree
{
	private:
		int* tokens;
		char** variables;
		tree* root;
		int bin_operators[2] = {operator_or, operator_and};  // Sammlung der binären Operatoren

	public: 
		
		syntax_tree(int * all_tokens, char** all_variables); // nimm tokens und variablen
		~syntax_tree();
		int find_matching_paren(int index); // gibt index der passenden schließenden Klammer zurück, nötig für den Baum
		
		tree* append_node(tree* node, int direction, int data); // Anfügen eines Elements
		int remove_branch(tree* node);
		tree* chroot(int direction, int data); // wurzel ändern, also "oben" anfügen

		void convert_to_tree(); // tokens in den Syntaxbaum umwandeln und variablen mit array-indezes ersetzen
		tree* convert_expression(); // simple fälle für die Konvertierung 
		tree* get_root();

		// z.B A&(B|C)&D  muss der Baum nach oben weitergebaut werden, da innerhalb der Klammer beide Möglichkeiten ausgeschöpft sind. zusätzlich wird "!" einfach so reingeschrieben.
};

#endif
