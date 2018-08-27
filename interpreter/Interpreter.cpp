//
// Created by chan on 2018/8/19.
//

#include "Interpreter.h"
#include "../parser/ast/NumNode.h"
#include "../parser/ast/BinOpNode.h"
#include "../exception/ParseError.h"

int Interpreter::visit()
{
	ASTNode *node = mParser.exp();
	return visit(node);
}

int Interpreter::visit(ASTNode *root)
{
	if (root->token->type == TYPE_NUMBER) {
		NumNode *node = (NumNode *) root;
		return *((int*) node->token->value);
	}

	// bin op
	BinOpNode *binOpNode = (BinOpNode *) root;
	int lhs = visit(binOpNode->lhs);
	int rhs = visit(binOpNode->rhs);
	switch (binOpNode->token->type) {
		case TYPE_DIV: return lhs / rhs;
		case TYPE_MUL: return lhs * rhs;
		case TYPE_SUB: return lhs - rhs;
		case TYPE_PLUS: return lhs + rhs;
		default:break;
	}

	throw ParseError("invalid exp");
}
