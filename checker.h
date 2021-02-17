#ifndef CHECKER_H
#define CHECKER_H
#include "parser.h"

class checker : public parser
{
/*
 * Parser, der die korrekte verwendung von Klammern prüft, dadurch wird das nachfolgende Lexen erheblich vereinfacht
 *
 * Als Algorithmus wird eine Art Kellerautomat verwendet, der einen Stack zur Prüfung verwendet
 * */
	private:
		Stack tracker; // stack struktur um die Klammern zu prüfen


	public:


};

#endif
