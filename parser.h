#ifndef PARSER_H
#define PARSER_H

class parser
{
	protected:
		const char* input;	// input string 
		int index;  // index des Momentanen Chars 

	public:
		parser(const char* string) : input(string), index(0){}
		char peek(); 
		char peek_non_blanc();
		char get();
};

#endif
