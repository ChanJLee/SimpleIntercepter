//
// Created by chan on 2018/9/4.
//

#include "AssignStatementNode.h"

AssignStatementNode::AssignStatementNode(VarNode *lv, Token *op, ASTNode *rv)
	: StatementNode(ASTNode::Type::ASSIGN), lv(lv), rv(rv), op(op)
{}

AssignStatementNode::~AssignStatementNode()
{
	if (lv != nullptr) {
		delete lv;
	}

	if (rv != nullptr) {
		delete rv;
	}

	if (op != nullptr) {
		delete op;
	}
}
