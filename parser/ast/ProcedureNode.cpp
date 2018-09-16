//
// Created by chan on 2018/9/16.
//

#include "ProcedureNode.h"

ProcedureNode::ProcedureNode(Token *token, FormalParametersNode *formalParameters, BlockNode *block)
	: ASTNode(token, ASTNode::Type::PROCEDURE), formalParameters(formalParameters), block(block)
{

}

ProcedureNode::~ProcedureNode()
{
	if (formalParameters != nullptr) {
		delete formalParameters;
	}

	if (block != nullptr) {
		delete block;
	}
}
