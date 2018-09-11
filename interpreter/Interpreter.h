//
// Created by chan on 2018/8/19.
//

#ifndef SIMPLEINTERPRETER_INTERCEPTER_H
#define SIMPLEINTERPRETER_INTERCEPTER_H

#include "../stream/Stream.h"
#include "../parser/Parser.h"
#include "../parser/ast/IntNumNode.h"
#include "../parser/ast/BinOpNode.h"
#include "../parser/ast/UnaryNode.h"
#include "../parser/ast/CompoundStatementNode.h"
#include "../parser/ast/NoOpStatementNode.h"
#include "../parser/ast/AssignStatementNode.h"
#include "../parser/ast/RealNumNode.h"
#include "../parser/ast/ProgramNode.h"
#include <map>

class Interpreter
{
private:
	Parser mParser;
	std::map<std::string, double> mSymbolTable;
public:
	Interpreter(Stream *stream)
		: mParser(stream)
	{}

	void interpret();

#ifdef DEBUG
	void dumpSymbolTable();
#endif
private:
	void visitProgramNode(ProgramNode* node);

	void visitDeclarationsNode(DeclarationsNode* node);

	void visitBlockNode(BlockNode* node);

	void visitCompoundStatementNode(CompoundStatementNode *node);

	void visitAssignStatementNode(AssignStatementNode *node);

	void visitNoOpStatementNode(NoOpStatementNode *node);

	// TODO add NodeValue
	double visitNode(ASTNode *node);

	double visitIntNumNode(IntNumNode *node);

	double visitRealNumNode(RealNumNode *node);

	double visitBinOpNode(BinOpNode *node);

	double visitUnaryNode(UnaryNode *node);

	double visitVarNode(VarNode *node);
};

#endif //SIMPLEINTERPRETER_INTERCEPTER_H
