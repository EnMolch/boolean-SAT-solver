#ifndef LINKED_LIST_H
#define LINKED_LIST_H


//verkettete Liste zur implementierung eines Stacks

struct list
{
	list* next;
	char data;
};

list* append(list* head,char data);

void* get_data(list* head, int index);

void destruct_all(list* head);


class stack
{

// wrapper um die verkettete Liste um einen Stack darzustellen, so dass die verkettete Liste nie selbst verwaltet werden muss
	private:
		list* top; // zeiger auf den oberen Wert im Stack
		list* bottom; // zeiger auf den unteren Wert (das Stacksymbol in diesem Fall)
		int stack_size; // größe des stacks, eigentlich nicht wirklich zum Prüfen der Klammersetzung nötig aber könnte interessant sein	

	public:
		stack();  //konstruieren einer Stack - Struktur aus einer verketteten Liste
		~stack();
		char push(char value); 
		char pop();

};
#endif
