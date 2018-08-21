#include <iostream>
#include "CharStream.h"
#include "Interpreter.h"

int main()
{
	CharStream charStream("7+8-1");
	Interpreter interpreter(&charStream);
	std::cout << interpreter.exp() << std::endl;
	return 0;
}