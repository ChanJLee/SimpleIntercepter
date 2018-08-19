//
// Created by chan on 2018/8/19.
//

#ifndef SIMPLEINTERPRETER_TOKEN_H
#define SIMPLEINTERPRETER_TOKEN_H

#include <memory>

const int TYPE_EOF = 0;
const int TYPE_NUMBER = 1;
const int TYPE_OPERATOR = 2;

struct Token {
	int type;
	std::shared_ptr<void*> value;
};

#endif //SIMPLEINTERPRETER_TOKEN_H
