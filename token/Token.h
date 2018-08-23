//
// Created by chan on 2018/8/19.
//

#ifndef SIMPLEINTERPRETER_TOKEN_H
#define SIMPLEINTERPRETER_TOKEN_H

const int TYPE_EOF = 0;

const int TYPE_NUMBER = 1;

const int TYPE_LEFT_BRACKET = 2;

const int TYPE_RIGHT_BRACKET = 3;

const int TYPE_MUL = 4;

const int TYPE_PLUS = 5;

const int TYPE_DIV = 6;

const int TYPE_SUB = 7;

template<typename T>
struct Token
{
	int type;
	T value;
	Token(int type)
		: type(type)
	{}

	Token(int type, T value)
		: type(type), value(value)
	{}
};

#endif //SIMPLEINTERPRETER_TOKEN_H
