//
// Created by chan on 2018/8/19.
//

#ifndef SIMPLEINTERPRETER_INTERCEPTER_H
#define SIMPLEINTERPRETER_INTERCEPTER_H

#include "../stream/Stream.h"
#include "../parser/Parser.h"

class Interpreter
{
private:
	Parser mParser;
public:
	Interpreter(Stream *stream)
		: mParser(stream)
	{}

	int visit();
private:
	int visit(ASTNode *root);
};

#endif //SIMPLEINTERPRETER_INTERCEPTER_H
