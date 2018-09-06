//
// Created by chan on 2018/8/19.
//

#ifndef SIMPLEINTERPRETER_TOKEN_H
#define SIMPLEINTERPRETER_TOKEN_H

struct Token
{
	enum TokenType
	{
		TYPE_PLUS,
		TYPE_SUB,
		TYPE_MUL,
		TYPE_FLOAT_DIV,
		TYPE_INT_DIV,
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
		TYPE_COMMA, // ,
		TYPE_PROGRAM,
		TYPE_REAL,
		TYPE_INTEGER,
	};

	TokenType type;
	Token(TokenType type)
		: type(type)
	{}
	virtual ~Token()
	{}
};

#endif //SIMPLEINTERPRETER_TOKEN_H
