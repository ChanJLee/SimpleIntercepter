//
// Created by chan on 2018/8/22.
//

#include "BinOpNode.h"
BinOpNode::BinOpNode(const Token &token, ASTNode *lhs, ASTNode *rhs)
	: token(token), lhs(lhs), rhs(rhs)
{}

BinOpNode::~BinOpNode()
{
	if (lhs != nullptr) {
		delete lhs;
	}

	if (rhs != nullptr) {
		delete rhs;
	}
}
