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
#include "../parser/ast/CompoundStatementNode.h"
#include "../parser/ast/NoOpStatementNode.h"
#include "../parser/ast/AssignStatementNode.h"
#include <map>

class Interpreter
{
private:
	Parser mParser;
	std::map<std::string, int> mSymbolTable;
public:
	Interpreter(Stream *stream)
		: mParser(stream)
	{}

	void interpret();

#ifdef DEBUG
	void dumpSymbolTable();
#endif
private:
	void visitCompoundStatementNode(CompoundStatementNode *root);

	void visitAssignStatementNode(AssignStatementNode *node);

	void visitNoOpStatementNode(NoOpStatementNode *node);

	int visit(ASTNode *node);

	int visit(NumNode *node);

	int visit(BinOpNode *node);

	int visit(UnaryNode *node);

	int visit(VarNode* node);
};

#endif //SIMPLEINTERPRETER_INTERCEPTER_H
