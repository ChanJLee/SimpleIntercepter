//
// Created by chan on 2018/8/19.
//

#ifndef SIMPLEINTERPRETER_INTERCEPTER_H
#define SIMPLEINTERPRETER_INTERCEPTER_H

#include "Stream.h"

class Interpreter
{
private:
	Stream* const mStream;
public:
	Interpreter(Stream* stream): mStream(stream) {}
	int exp();
private:
	int term();
	int factor();
};


#endif //SIMPLEINTERPRETER_INTERCEPTER_H
