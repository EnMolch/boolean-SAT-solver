#ifndef STRING_PROCESSING_H
#define STRING_PROCESSING_H
// Ich weiss, dass string.h existiert, zum lernen mache ich es hier aber slebst

#include "linked_list.h" //für die verkettete Liste

// Funktionen, die auch auf char* angewendet werden sollen
namespace string_processing
{
		int stringcompare(const char* string1, const char* string2); // verlgeiche 2 zeichenketten, return 1 oder 0
		int strlen(const char* string);	//länge des Strings zurückgeben
		 
}

// Klasse um effizient mit variablennamen und ähnlichem hantieren zu können,
// eigentlich nur ein wrapper um die Verkettete Liste aus chars
class string 
{
	private:
		list* start; // start des Strings
		list* head; // kopf der verketteten Liste

	public:	
		string();
		string(const char* str); // aus bestehendem char- pointer erstellen
		~string();
		void append(const char* str); // an bestehenden String anfügen
		void append(char c);
		char* convert();  // in ein  char[] auf dem Heap convertieren
};
#endif


