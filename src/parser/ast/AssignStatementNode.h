//
// Created by chan on 2018/9/4.
//

#ifndef SIMPLEINTERPRETER_ASSIGNSTATEMENTNODE_H
#define SIMPLEINTERPRETER_ASSIGNSTATEMENTNODE_H


#include "StatementNode.h"
#include "VarNode.h"

class AssignStatementNode: public StatementNode
{
public:
	VarNode *lv;
	ASTNode *rv;
	Token *op;

	AssignStatementNode(VarNode *lv, Token *op, ASTNode *rv);

	virtual ~AssignStatementNode();
};


#endif //SIMPLEINTERPRETER_ASSIGNSTATEMENTNODE_H
