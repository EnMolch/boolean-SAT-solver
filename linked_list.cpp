#include "linked_list.h"
#include <iostream>
list *append(list* head, char data) //Anfügen an die verkettete Liste
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




