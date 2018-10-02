//
// Created by chan on 2018/9/16.
//

#ifndef SIMPLEINTERPRETER_PROCEDURENODE_H
#define SIMPLEINTERPRETER_PROCEDURENODE_H


#include "ASTNode.h"
#include "DeclarationsNode.h"
#include "FormalParametersNode.h"
#include "../../token/IdToken.h"

class BlockNode;

class ProceduresNode: ASTNode
{
public:

	struct Procedure {
		FormalParametersNode *formalParameters;
		BlockNode *block;
		IdToken *id;
		Procedure(IdToken *id, FormalParametersNode *formalParameters, BlockNode *block);
		~Procedure();
	};

	std::vector<Procedure*> procedures;
public:
	ProceduresNode();
	explicit ProceduresNode(const std::vector<Procedure*> &procedures);
	virtual ~ProceduresNode();
};


#endif //SIMPLEINTERPRETER_PROCEDURENODE_H
