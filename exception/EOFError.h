//
// Created by chan on 2018/8/21.
//

#ifndef SIMPLEINTERPRETER_EOFERROR_H
#define SIMPLEINTERPRETER_EOFERROR_H


#include "ParseError.h"


class EOFError: public ParseError
{
public:
	EOFError(const char *msg)
		: ParseError(msg)
	{}
};


#endif //SIMPLEINTERPRETER_EOFERROR_H
