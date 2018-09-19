//
// Created by chan on 2018/9/11.
//

#ifndef SIMPLEINTERPRETER_SYNTAXMACHINE_H
#define SIMPLEINTERPRETER_SYNTAXMACHINE_H

#include "../parser/ast/ProgramNode.h"
#include "ast/Symbol.h"
#include "../parser/ast/AssignStatementNode.h"
#include "../parser/ast/BinOpNode.h"
#include "../parser/ast/UnaryNode.h"
#include "../parser/ast/NoOpStatementNode.h"
#include <map>
#include "../st/SymbolTable.h"
#include <string>

class SemanticAnalyzer
{
	typedef std::string String;
	typedef SymbolTable<Symbol> SymbolTable;
	typedef SymbolTable::Iterator Iterator;
private:
	ProgramNode *mTree;
	SymbolTable *mCurrentTable;
public:
	explicit SemanticAnalyzer(ProgramNode *tree);
	void check();
private:
	void checkBlock(BlockNode *node);
	void checkDeclarations(DeclarationsNode *node);
	void checkCompoundStatement(CompoundStatementNode *node);
	void checkAssignStatement(AssignStatementNode *node);
	void checkNoOp(NoOpStatementNode *node);
	void checkProcedures(ProceduresNode *node);

	Symbol checkVar(VarNode *node);
	Symbol checkExp(ASTNode *node);
	Symbol checkBinOp(BinOpNode *node);
	Symbol visitUnaryNode(UnaryNode *node);

	void insert(const String &key, Token::TokenType value);
	Symbol lookup(const String &key);
};


#endif //SIMPLEINTERPRETER_SYNTAXMACHINE_H
