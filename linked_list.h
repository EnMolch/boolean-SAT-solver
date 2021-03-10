// simple verkettete Liste als Basis für weitere Datemstrukturen
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// listenstruktur
struct list
{
	list* next;
	char data;
};

// Elementare Funktionen für die Verwaltung der Liste

list* append(list* head,char data);

char get_data(list* head, int index);

void destruct_all(list* head);


#endif
