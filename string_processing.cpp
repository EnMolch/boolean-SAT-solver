// eine eigene Implementierung gewählter Funktionen der Standard-Bibliothek strings.
// Grund ist einerseits das Interesse an der Implementierung and andererseits die Effizienz des Codes
// Tim Heckenberger

#include <cstddef>
#include <iostream>
#include "string_processing.h"
#include "linked_list.h"

// Methoden für C-Strings , also char*

int string_processing::strlen(const char* first_char)
{
	// iteriere bis zum abschließenden 0-Byte
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
	if (max_len != strlen(string2)) return 0; //gleiche Länge prüfen
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

// dynamischer String, für den beispielsweise eine append() - Methode definiert ist. Er kann also dynamisch wachsen

string::string()
{
	// Basisstruktur ist die verkettete Liste
	this->start = new list {0,0}; 
	this->head = start;	// neben dem "Kopf" muss auch das erste Element bekannt sein
}

string::string(const char* str)
{
	// kann auch aus einem existierenden C-String erzeugt werden
	this->start = new list {0,0};
	this->head = start;
	string::append(str);
}

void string::reset()
{
	// leeren des Strings
	destruct_all(start);
	this->start = new list{0,0};
	this->head = start;
}

void string::append(const char* str)
{
	// Anfügen eines C-strings
	for(int i = 0; i<string_processing::strlen(str); i++) // Anhängen eines strings hängt nacheinader alle chars an
	{
		string::append(str[i]);
	}
}

void string::append(char c)
{
	// Anfügen eines einzelnen Zeichens
	head->data = c;
	head->next = new list {0,0};
	head = head->next;
}

string::~string()
{
	if (start!=0) destruct_all(start); // aufruf mit start, da die Liste hier "Falsch herum" gebaut wird
}

char* string::convert() // Umwandlung der verketteten Liste in ein char Array auf dem Heap (einen C-String)
{	
	int list_len = 0; // Zähler für die Länge der Liste
	list* p = start;
	while (p != head) // iteriere bis zum Kopf der Liste
	{
		list_len++;
		p = p->next;	
	}
	char* ret = new char[list_len+1];
	p = start;
	for(int counter = 0; counter < list_len; counter++) // durchiterieren und das heap-array füllen
	{
		ret[counter] = p->data;
		p = p->next;
	}
	ret[list_len] = 0; // abschließendes 0 - Byte
	return ret; // pointer auf das Heap- array zurückgeben, Speicher muss manuell freigegeben werden
}
