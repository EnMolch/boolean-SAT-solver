#ifndef PARSER_H
#define PARSER_H

class parser
{
	private:
		const char* input;	// input string 
		int index;  // index des Momentanen Chars 

	public:
		parser(const char* string) : input(string), index(0){}
		char peek(); 
		char get();
};

#endif
