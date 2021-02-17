#include "stack.h"
list *insert(list* head, char data)
{
	list* next = head;
	list* append = new list{next, data};
	return append;
}

void destruct_all(list* head)
{
	list* current = 0;
	list* p = head;
	while (p != 0)
	{
		current = p;
		p = current->next;
		delete [] current; 
	}
}



stack::stack()
{
	// anlegen des ersten Elements und initialisierung des Stacksymbols
	this->stack_size = 0;
	this->top = new list;
	top->data = '@'; // @ als Stacksymbol um den passenden Zustand zu prüfen
}

stack::~stack()
{
	destruct_all(this->top);
}

char stack::push(char value)
{
	this->top = insert(this->top, value);
	this->stack_size++;
	return value;
}

char stack::pop()
{
	list* upper = this->top;
	this->top = (this->top)->next;
	char ret = upper->data;
	delete upper;
	this->stack_size--;
	return ret;
}
