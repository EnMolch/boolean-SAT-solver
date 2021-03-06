// Klasse Stack
// Tim Heckenberger

#ifndef STACK_H
#define STACK_H 
#include "linked_list.h"
class stack
{

// wrapper um die verkettete Liste um einen Stack darzustellen, so dass die verkettete Liste nie selbst verwaltet werden muss
	private:
		list* top; // zeiger auf den oberen Wert im Stack
		list* bottom; // zeiger auf den untersten Wert (das Stacksymbol in diesem Fall)
		int stack_size; // größe des stacks

	public:
		stack();  //konstruieren einer Stack - Struktur aus einer verketteten Liste
		~stack();
		char push(char value); 
		char pop();

};
#endif
