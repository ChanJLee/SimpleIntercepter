#include <iostream>
#include "stream/char/CharStream.h"
#include "interpreter/Interpreter.h"

int main()
{
	CharStream charStream("7+8---+1");
	Interpreter interpreter(&charStream);
	std::cout << interpreter.visit() << std::endl;
	return 0;
}