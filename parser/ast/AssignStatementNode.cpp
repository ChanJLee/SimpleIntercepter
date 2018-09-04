//
// Created by chan on 2018/9/4.
//

#include "AssignStatementNode.h"

AssignStatementNode::AssignStatementNode(Token *lhs, ASTNode *expr)
	: StatementNode(ASTNode::Type::ASSIGN), lhs(lhs), expr(expr)
{}

AssignStatementNode::~AssignStatementNode()
{
	if (lhs != nullptr) {
		delete lhs;
	}

	if (expr != nullptr) {
		delete expr;
	}
}
