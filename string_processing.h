#ifndef STRING_PROCESSING_H
#define STRING_PROCESSING_H
// class to group some string comparison and processing stuff I'll need
// I know string.h exists, but it seems more fun to do it myself :D
// This defines functions acting on strings, no fancy heap stuff, I'll do that in the parser
namespace string_processing{
class string{

	private:
		const char* first_char; //pointer to the first character

	public:
		string(const char* address);
	        string(){first_char = 0;}	


		int stringcompare(string comp_str); //compare this to comp_str, return bool true/false

		int strlen();	//return length of the current string object
		
		
}; 
}
#endif
