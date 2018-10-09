//
// Created by chan on 2018/8/22.
//

#include "BinOpNode.h"

BinOpNode::~BinOpNode()
{
	delete lhs;
	delete rhs;
}

BinOpNode::BinOpNode(Token *const token, ASTNode *lhs, ASTNode *rhs)
	: ASTNode(token, ASTNode::Type::BIN), lhs(lhs), rhs(rhs)
{
}
