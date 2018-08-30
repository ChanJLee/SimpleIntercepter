//
// Created by chan on 2018/8/19.
//

#ifndef SIMPLEINTERPRETER_TOKEN_H
#define SIMPLEINTERPRETER_TOKEN_H

#include <string>

struct Token
{
	enum TokenType {
		TYPE_PLUS,
		TYPE_SUB,
		TYPE_MUL,
		TYPE_DIV,
		TYPE_LEFT_BRACKET,
		TYPE_RIGHT_BRACKET,
		TYPE_NUMBER,
		TYPE_EOF,
		TYPE_BEGIN, // BEGIN
		TYPE_END, // END
		TYPE_DOT, // .
		TYPE_COLON, // :
		TYPE_ASSIGN,// :=
		TYPE_SEMI, // ;
		TYPE_ID,
	};

	TokenType type;
	const void* value;

	Token(TokenType type)
		: type(type)
	{}

	Token(TokenType type, const int *value)
		: type(type), value(value)
	{}

	Token(TokenType type, const std::string *value)
		: type(type), value(value)
	{}

	// TODO refactor
	virtual ~Token()
	{
		if (!value) {
			return;
		}

		if (type == TokenType::TYPE_NUMBER) {
			const int* p = (const int *) value;
			delete p;
		}

		if (type == TokenType::TYPE_ID) {
			const std::string* p = (const std::string *) value;
			delete p;
		}
	}
};

#endif //SIMPLEINTERPRETER_TOKEN_H
