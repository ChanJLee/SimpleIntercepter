//
// Created by chan on 2018/8/21.
//

#ifndef SIMPLEINTERPRETER_RUNTIMEERROR_H
#define SIMPLEINTERPRETER_RUNTIMEERROR_H


#include "ParseError.h"

class RuntimeError: public ParseError
{
public:
	RuntimeError(const char *msg)
		: ParseError(msg)
	{}

};


#endif //SIMPLEINTERPRETER_RUNTIMEERROR_H
