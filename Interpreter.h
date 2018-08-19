//
// Created by chan on 2018/8/19.
//

#ifndef SIMPLEINTERPRETER_INTERCEPTER_H
#define SIMPLEINTERPRETER_INTERCEPTER_H

#include "Stream.h"

class Interpreter
{
private:
	const Stream* mStream;
public:
	Interpreter(const Stream* stream): mStream(stream) {}
	int exp();
};


#endif //SIMPLEINTERPRETER_INTERCEPTER_H
