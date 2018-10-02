//
// Created by chan on 2018/9/16.
//

#include "ProceduresNode.h"
#include "../ast/BlockNode.h"

ProceduresNode::~ProceduresNode()
{
	std::for_each(procedures.cbegin(), procedures.cend(), [](Procedure *procedure)
	{
		if (procedure != nullptr) {
			delete procedure;
		}
	});
}

ProceduresNode::ProceduresNode()
	: ASTNode(nullptr, ASTNode::Type::PROCEDURE)
{}

ProceduresNode::ProceduresNode(const std::vector<Procedure *> &procedures)
	: ASTNode(nullptr, ASTNode::Type::PROCEDURE), procedures(procedures)
{

}

ProceduresNode::Procedure::Procedure(IdToken *id, FormalParametersNode *formalParameters, BlockNode *block)
	: formalParameters(formalParameters), block(block), id(id)
{}

ProceduresNode::Procedure::~Procedure()
{
	delete formalParameters;
	delete block;
}
