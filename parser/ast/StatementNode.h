//
// Created by chan on 2018/9/4.
//

#ifndef SIMPLEINTERPRETER_STATEMENTNODE_H
#define SIMPLEINTERPRETER_STATEMENTNODE_H


#include "ASTNode.h"
class StatementNode: public ASTNode
{
public:
	StatementNode(ASTNode::Type type);
	virtual ~StatementNode();
};


#endif //SIMPLEINTERPRETER_STATEMENTNODE_H
