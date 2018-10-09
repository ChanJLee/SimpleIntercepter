//
// Created by chan on 2018/9/4.
//

#ifndef SIMPLEINTERPRETER_STATEMENTNODE_H
#define SIMPLEINTERPRETER_STATEMENTNODE_H


#include "ASTNode.h"
class StatementNode: public ASTNode
{
public:
	explicit StatementNode(ASTNode::Type type);
	~StatementNode() override = default;
};


#endif //SIMPLEINTERPRETER_STATEMENTNODE_H
