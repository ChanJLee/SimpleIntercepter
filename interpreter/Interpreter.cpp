//
// Created by chan on 2018/8/19.
//

#include "Interpreter.h"
#include "../exception/ParseError.h"

int Interpreter::visit()
{
	ASTNode *node = mParser.parse();
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

int Interpreter::visit(ASTNode *node)
{
	if (node->type == ASTNode::Type::NUM) {
		return visit((NumNode *) node);
	}
	else if (node->type == ASTNode::Type::BIN) {
		return visit((BinOpNode *) node);
	}
	else if (node->type == ASTNode::Type::UNARY) {
		return visit((UnaryNode *) node);
	}

	throw ParseError("invalid exp");
}

int Interpreter::visit(NumNode *node)
{
	return *((int *) node->token->value);
}

int Interpreter::visit(BinOpNode *node)
{
	if (node->lhs == nullptr) {
		throw ParseError("missing left operand");
	}

	if (node->rhs == nullptr) {
		throw ParseError("missing right operand");
	}

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

int Interpreter::visit(UnaryNode *node)
{
	if (node->child == nullptr) {
		throw ParseError("missing unary operand");
	}

	if (node->token->type == Token::TokenType::TYPE_SUB) {
		return -visit(node->child);
	}

	if (node->token->type == Token::TokenType::TYPE_PLUS) {
		return visit(node->child);
	}

	throw ParseError("unknown unary op");
}

void Interpreter::program()
{
	// do something
}
