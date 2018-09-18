//
// Created by chan on 2018/9/9.
//

#ifndef SIMPLEINTERPRETER_BLOCKNODE_H
#define SIMPLEINTERPRETER_BLOCKNODE_H


#include <vector>
#include "ASTNode.h"
#include "CompoundStatementNode.h"
#include "DeclarationsNode.h"

class ProceduresNode;

class BlockNode: public ASTNode
{
public:
	DeclarationsNode *declarations;
	StatementNode *compoundStatementNode;
	ProceduresNode *procedures;
public:
	BlockNode(DeclarationsNode *declarations, ProceduresNode *procedures, StatementNode *statementNode);
	virtual ~BlockNode();
};


#endif //SIMPLEINTERPRETER_BLOCKNODE_H
