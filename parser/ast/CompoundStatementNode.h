//
// Created by chan on 2018/9/4.
//

#ifndef SIMPLEINTERPRETER_COMPOUNDNODE_H
#define SIMPLEINTERPRETER_COMPOUNDNODE_H


#include <vector>
#include "ASTNode.h"
#include "StatementNode.h"

class CompoundStatementNode: public StatementNode
{
public:
	const std::vector<StatementNode *> statements;
public:
	CompoundStatementNode(const std::vector<StatementNode *> &statements);
	virtual ~CompoundStatementNode();
};


#endif //SIMPLEINTERPRETER_COMPOUNDNODE_H
