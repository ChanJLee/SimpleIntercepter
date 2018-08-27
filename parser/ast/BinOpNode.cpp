//
// Created by chan on 2018/8/22.
//

#include "BinOpNode.h"

BinOpNode::~BinOpNode()
{
	if (lhs != nullptr) {
		delete lhs;
	}

	if (rhs != nullptr) {
		delete rhs;
	}
}
BinOpNode::BinOpNode(Token *const token, ASTNode *lhs, ASTNode *rhs)
	: ASTNode(token), lhs(lhs), rhs(rhs)
{
}
