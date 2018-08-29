//
// Created by chan on 2018/8/19.
//

#include "Interpreter.h"
#include "../exception/ParseError.h"

int Interpreter::visit()
{
	ASTNode *node = mParser.exp();
	int result = 0;

	try {
		result = visit(node);
	}
	catch (std::exception e) {
		delete node;
		throw e;
	}

	delete node;
	return result;
}

int Interpreter::visit(ASTNode *root)
{
	if (root->type == ASTNode::Type::NUM) {
		return visit((NumNode *) root);
	}
	else if (root->type == ASTNode::Type::BIN) {
		return visit((BinOpNode *) root);
	}

	throw ParseError("invalid exp");
}

int Interpreter::visit(NumNode *node)
{
	return *((int *) node->token->value);
}

int Interpreter::visit(BinOpNode *node)
{
	int lhs = visit(node->lhs);
	int rhs = visit(node->rhs);
	switch (node->token->type) {
		case Token::TokenType::TYPE_DIV: return lhs / rhs;
		case Token::TokenType::TYPE_MUL: return lhs * rhs;
		case Token::TokenType::TYPE_SUB: return lhs - rhs;
		case Token::TokenType::TYPE_PLUS: return lhs + rhs;
		default: throw ParseError("unknown bin op");
	}
}
