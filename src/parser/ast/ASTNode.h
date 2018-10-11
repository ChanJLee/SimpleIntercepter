//
// Created by chan on 2018/8/23.
//

#ifndef SIMPLEINTERPRETER_ASTNODE_H
#define SIMPLEINTERPRETER_ASTNODE_H


#include "../../token/Token.h"
class ASTNode
{
public:
	enum Type
	{
		REAL_NUM,
		INT_NUM,
		BIN,
		UNARY,
		COMPOUND,
		NO_OP,
		ASSIGN,
		VAR,
		PROGRAM,
		BLOCK,
		DECLARATION,
		PROCEDURE,
		FORMAL_PARAMETER,
	};
public:
	Token *const token;
	ASTNode::Type type;
public:
	ASTNode(Token *token, ASTNode::Type type);
	virtual ~ASTNode();
};


#endif //SIMPLEINTERPRETER_ASTNODE_H
