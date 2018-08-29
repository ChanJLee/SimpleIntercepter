//
// Created by chan on 2018/8/19.
//

#ifndef SIMPLEINTERPRETER_INTERCEPTER_H
#define SIMPLEINTERPRETER_INTERCEPTER_H

#include "../stream/Stream.h"
#include "../parser/Parser.h"
#include "../parser/ast/NumNode.h"
#include "../parser/ast/BinOpNode.h"
#include "../parser/ast/UnaryNode.h"

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
	int visit(ASTNode *node);

	int visit(NumNode* node);

	int visit(BinOpNode* node);

	int visit(UnaryNode* node);
};

#endif //SIMPLEINTERPRETER_INTERCEPTER_H
