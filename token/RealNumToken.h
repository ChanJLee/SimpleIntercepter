//
// Created by chan on 2018/9/6.
//

#ifndef SIMPLEINTERPRETER_REALNUMTOKEN_H
#define SIMPLEINTERPRETER_REALNUMTOKEN_H


#include "Token.h"
class RealNumToken: public Token
{
public:
	double value;
public:
	RealNumToken(double value);
};


#endif //SIMPLEINTERPRETER_REALNUMTOKEN_H
