#include <cstddef>
#include "string_processing.h"
#include <iostream>
#include "linked_list.h"
//implement the methods of the string-class
int string_processing::strlen(const char* first_char)
{
	// iterate through the characters, counting up till a zero Byte
	int len = 0;
	const char* iterator = first_char;
	while (iterator[len] != 0)
	{
		len++;
	}
	return len;
}

int string_processing::stringcompare(const char* string1, const char* string2)
{
	// return 0 wenn ungleich, sonst 1
	int max_len = strlen(string1);
	if (max_len != strlen(string2)) return 0; //geliche Länge prüfuen
	else
	{
		for (int i = 0; i<max_len;i++)
		{
			if(string1[i] != string2[i])
				return 0;	
		}	
		return 1; // Bei selber länge und glechen chars, gebe 1 zurück
	}
}


string::string()
{
	this->start = new list; 
	this->head = start;
}

string::string(const char* str)
{
	this->start = new list;
	this->head = start;
	string::append(str);
}

void string::append(const char* str)
{
	for(int i = 0; i<string_processing::strlen(str); i++) // Anhängen eines strings hängt nacheinader alle chars an
	{
		string::append(str[i]);
	}
}

void string::append(char c)
{
	head->data = c;
	head->next = new list;
	head = head->next;
}

string::~string()
{
	destruct_all(start); // aufruf mit start, da die Liste hier "Falsch herum" gebaut wird
}

char* string::convert()
{	
	int counter = 0; // Zähler für die Länge der Liste
	list* p = start;
	while (p != 0)
	{
		counter++;
		p = p->next;	
	}
	std::cout << counter << std::endl;
	char* ret = new char[counter];

	counter = 0;
	p = start;
	while (p!=0)
	{
		ret[counter] = p->data;
		counter++;
		p = p->next;
	}
	ret[counter] = 0; // abschließendes 0 - Byte
	return ret;
}
