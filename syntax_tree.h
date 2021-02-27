// Klasse, die von Lexertokens zu boolscher Gleichug übrsetzt
#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

class syntax_tree
{
	private:
		int* tokens;
		char** variables;


	public: 
		syntax_tree(); // nimm tokens und variablen
		~syntax_tree();
		int find_matching_paren(); // gibt index der passenden schließenden Klammer zurück, nötig für den Baum

		// z.B A&(B|C)&D  muss der Baum nach oben weitergebaut werden, da innerhalb der Klammer beide Möglichkeiten ausgeschöpft sind. zusätzlich wird "!" einfach so reingeschrieben.
};

#endif
