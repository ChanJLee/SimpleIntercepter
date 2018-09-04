//
// Created by chan on 2018/9/4.
//

#ifndef SIMPLEINTERPRETER_ASSIGNSTATEMENTNODE_H
#define SIMPLEINTERPRETER_ASSIGNSTATEMENTNODE_H


#include "StatementNode.h"
class AssignStatementNode: public StatementNode
{
public:
	Token *lhs;
	ASTNode *expr;
	AssignStatementNode(Token *lhs, ASTNode *expr);
	virtual ~AssignStatementNode();
};


#endif //SIMPLEINTERPRETER_ASSIGNSTATEMENTNODE_H
