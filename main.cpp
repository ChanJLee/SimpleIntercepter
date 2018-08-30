#include "stream/char/CharStream.h"
#include "interpreter/Interpreter.h"

int main()
{
	CharStream charStream("(7 + 8) + 2");
	Interpreter interpreter(&charStream);
	interpreter.program();
	return 0;
}