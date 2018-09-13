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
#include "result/Result.h"
#include <map>

class Interpreter
{
	typedef std::string String;
	typedef std::map<String, Result> KVTable;
	typedef KVTable::iterator Iterator;
private:
	ProgramNode * mRoot;
	KVTable mSymbolTable;
public:
	Interpreter(ProgramNode *root)
		: mRoot(root)
	{}

	void interpret();

#ifdef DEBUG
	void dumpSymbolTable();
#endif
private:
	void visitProgramNode(ProgramNode *node);

	void visitDeclarationsNode(DeclarationsNode *node);

	void visitBlockNode(BlockNode *node);

	void visitCompoundStatementNode(CompoundStatementNode *node);

	void visitAssignStatementNode(AssignStatementNode *node);

	void visitNoOpStatementNode(NoOpStatementNode *node);

	Result visitNode(ASTNode *node);

	Result visitIntNumNode(IntNumNode *node);

	Result visitRealNumNode(RealNumNode *node);

	Result visitBinOpNode(BinOpNode *node);

	Result visitUnaryNode(UnaryNode *node);

	Result visitVarNode(VarNode *node);
};

#endif //SIMPLEINTERPRETER_INTERCEPTER_H
