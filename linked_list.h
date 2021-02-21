// simple verkettete Liste als Basis für weitere Datemstrukturen
#ifndef LINKED_LIST_H
#define LINKED_LIST_H
struct list
{
	list* next;
	char data;
};

list* append(list* head,char data);

char get_data(list* head, int index);

void destruct_all(list* head);


#endif
