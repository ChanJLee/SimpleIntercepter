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

struct Token
{
	int type;
	void* value;
	int len;

	Token(int type, int len)
		: type(type), len(len)
	{}

	Token(int type, void *value, int len)
		: type(type), value(value), len(len)
	{}

	virtual ~Token()
	{
		if (!value) {
			return;
		}

		if (type == TYPE_NUMBER) {
			int* p = (int *) value;
			delete p;
		}
	}
};

#endif //SIMPLEINTERPRETER_TOKEN_H
