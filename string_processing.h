#ifndef STRING_PROCESSING_H
#define STRING_PROCESSING_H
// I know string.h exists, but it seems more fun to do it myself
// This defines functions acting on strings, no fancy heap stuff, I'll do that in the parser
namespace string_processing
{
		int stringcompare(const char* string1, const char* string2); //compare this to comp_str, return bool true/false
		int strlen(const char* string);	//return length of the current string object
		 
}
#endif
