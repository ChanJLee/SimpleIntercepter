//
// Created by chan on 2018/9/5.
//

#ifndef SIMPLEINTERPRETER_IDTOKEN_H
#define SIMPLEINTERPRETER_IDTOKEN_H


#include "Token.h"
#include <string>

class IdToken: public Token
{
public:
	const std::string value;
public:
	IdToken(const std::string& value);
};


#endif //SIMPLEINTERPRETER_IDTOKEN_H
