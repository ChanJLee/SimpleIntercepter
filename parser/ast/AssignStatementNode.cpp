//
// Created by chan on 2018/9/4.
//

#include "AssignStatementNode.h"

AssignStatementNode::AssignStatementNode(Var *lv, ASTNode *expr)
	: StatementNode(ASTNode::Type::ASSIGN), lv(lv), expr(expr)
{}

AssignStatementNode::~AssignStatementNode()
{
	if (lv != nullptr) {
		delete lv;
	}

	if (expr != nullptr) {
		delete expr;
	}
}
