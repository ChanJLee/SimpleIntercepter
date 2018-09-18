//
// Created by chan on 2018/9/9.
//

#include "BlockNode.h"
#include "ProceduresNode.h"

BlockNode::~BlockNode()
{
	delete compoundStatementNode;
	delete declarations;
	delete procedures;
}

BlockNode::BlockNode(DeclarationsNode *declarations, ProceduresNode *procedures, StatementNode *statementNode)
	: ASTNode(nullptr, ASTNode::Type::BLOCK),
	  declarations(declarations),
	  compoundStatementNode(statementNode),
	  procedures(procedures)
{}
