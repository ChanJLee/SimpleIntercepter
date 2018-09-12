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
#include <string>

class SyntaxChecker
{
	typedef std::string String;
	typedef std::map<String, Symbol> SymbolTable;
	typedef SymbolTable::iterator Iterator;
private:
	ProgramNode *mTree;
	SymbolTable mGlobalSymbolTable;
public:
	SyntaxChecker(ProgramNode *tree);
	void check();
private:
	void checkBlock(BlockNode *node);
	void checkDeclarations(DeclarationsNode *node);
	void checkCompoundStatement(CompoundStatementNode *node);
	void checkAssignStatement(AssignStatementNode *node);
	void checkNoOp(NoOpStatementNode *node);

	Symbol checkVar(VarNode *node);
	Symbol checkExp(ASTNode *node);
	Symbol checkBinOp(BinOpNode *node);
	Symbol visitUnaryNode(UnaryNode *node);

	void putSymbol(const String &key, Token::TokenType value);
	Symbol getSymbol(const String &key);
};


#endif //SIMPLEINTERPRETER_SYNTAXMACHINE_H
