#ifndef READER_H 
#define READER_H

// nützliche Basisfunktionen für den Lexer, welche Entkoppelt von der Lexer - Logik sein sollen

class reader
{
	protected:
		const char* input;	// input string 
		int index;  // index des Momentanen Chars 

	public:
		reader(const char* string) : input(string), index(0){}
		char peek(); 
		char peek_non_blanc();
		char get();
};

#endif
