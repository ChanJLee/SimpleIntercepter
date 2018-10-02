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
	enum IdTokenType
	{
		REAL,
		INT,
		NONE
	};
public:
	const std::string value;
	const IdToken::IdTokenType type;
public:
	IdToken(const std::string &value);

	IdToken(const std::string &value, IdToken::IdTokenType type);
};


#endif //SIMPLEINTERPRETER_IDTOKEN_H
