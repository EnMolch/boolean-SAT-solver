#include "stack.h"
#include "linked_list.h"
#include <iostream>
stack::stack()
{
	// anlegen des ersten Elements und initialisierung des Stacksymbols
	this->stack_size = 0;
	this->top = new list{0,0};
	top->data = '@'; // @ als Stacksymbol um den passenden Zustand zu prüfen
}

stack::~stack()
{
	destruct_all(this->top);
}

char stack::push(char value)
{
	this->top = append(this->top, value);
	this->stack_size++;
	return value;
}

char stack::pop()
{
	if (this->stack_size >0)
	{
		list* upper = this->top;
		this->top = (this->top)->next;
		char ret = upper->data;
		delete upper;
		this->stack_size--;
		return ret;
	}
	else if(this->stack_size == 0)
	{
		this->stack_size--;
		return '@';
	}
	else return '#'; //für den Fall, dass ein pop bei leerem stack versucht wird, wird ein bestimmtes Zeichenzurückgegeben
}
