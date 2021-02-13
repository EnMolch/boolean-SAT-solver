#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
class handler{

	// Class to handle the initial calling of the programm, should be able to give me the Data in the end
	private:
		int count;
		char* values[];


	public:
		handler(int argc, char* argv[]) : count(argc), values(argv){}
		char* getopts(); // return the parameter of -X or print "usage..."
		char* get_indata() // probably some heap stuff since Arrays die at the end of the function
		
	}
#endif
