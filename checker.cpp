#include "checker.h"
#include "stack.h"
#include "string_processing.h"
#include <iostream>

checker::checker(const char* string):parser(string)
{
	stack tracker();
}


int checker::validate()
{
	char current = 'A'; // inititalisierung kann alles außer 0 sein
	char stop_flag = 1;
	while (current != 0 && stop_flag == 1 )// iteriere durch die ganze Eingabe
	{
		char next = peek(); // Nächstes Zeichen vormerken
		current = get(); // Nach jetzigem Zeichen Handeln und den Stack modifizieren
		switch (current)
		{
			case '(':
				tracker.push(1);				
				break;

			case ')':
				stop_flag = tracker.pop();
				break;
		}
	}
	if (tracker.pop() == '@') return 0; // return für den Fall, dass klammern passen
	return 1;		//return für den Fall, dass Klammern nich passen
}
