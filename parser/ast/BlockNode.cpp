//
// Created by chan on 2018/9/9.
//

#include "BlockNode.h"

BlockNode::~BlockNode()
{
	if (compoundStatementNode != nullptr) {
		delete compoundStatementNode;
	}

	if (declarations != nullptr) {
		delete declarations;
	}
}

BlockNode::BlockNode(DeclarationsNode *declarations, StatementNode *statementNode)
	: ASTNode(NULL, ASTNode::Type::BLOCK), declarations(declarations), compoundStatementNode(statementNode)
{

}
