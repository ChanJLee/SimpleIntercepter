//
// Created by chan on 2018/9/16.
//

#ifndef SIMPLEINTERPRETER_PROCEDURENODE_H
#define SIMPLEINTERPRETER_PROCEDURENODE_H


#include "ASTNode.h"
#include "DeclarationsNode.h"
#include "FormalParametersNode.h"

class BlockNode;

class ProcedureNode: ASTNode
{
public:
	FormalParametersNode *formalParameters;
	BlockNode *block;
public:
	ProcedureNode(Token* token, FormalParametersNode *formalParameters, BlockNode *block);
	~ProcedureNode();
};


#endif //SIMPLEINTERPRETER_PROCEDURENODE_H
