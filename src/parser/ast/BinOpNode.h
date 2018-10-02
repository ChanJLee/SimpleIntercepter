//
// Created by chan on 2018/8/22.
//

#ifndef SIMPLEINTERPRETER_BINOP_H
#define SIMPLEINTERPRETER_BINOP_H


#include "ASTNode.h"
#include "../../token/Token.h"

struct BinOpNode: public ASTNode
{
	ASTNode *lhs;
	ASTNode *rhs;
	BinOpNode(Token *const token, ASTNode *lhs, ASTNode *rhs);
	virtual ~BinOpNode();
};


#endif //SIMPLEINTERPRETER_BINOP_H
