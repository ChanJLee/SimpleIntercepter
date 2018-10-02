//
// Created by chan on 2018/9/5.
//

#ifndef SIMPLEINTERPRETER_NUMBERTOKEN_H
#define SIMPLEINTERPRETER_NUMBERTOKEN_H


#include "Token.h"
class IntNumToken: public Token
{
public:
	int value;
public:
	IntNumToken(int value);
};


#endif //SIMPLEINTERPRETER_NUMBERTOKEN_H
