//
// Created by chan on 2018/8/19.
//

#include "Interpreter.h"
#include "../exception/ParseError.h"

int Interpreter::visitNode(ASTNode *node)
{
	if (node->type == ASTNode::Type::INT_NUM) {
		return visitIntNumNode((IntNumNode *) node);
	}
	else if (node->type == ASTNode::Type::BIN) {
		return visitBinOpNode((BinOpNode *) node);
	}
	else if (node->type == ASTNode::Type::UNARY) {
		return visitUnaryNode((UnaryNode *) node);
	}
	else if (node->type == ASTNode::Type::VAR) {
		return visitVarNode((VarNode *) node);
	}

	std::string msg = "unknown ast node, type is: ";
	msg += node->token->type;
	throw ParseError(msg);
}

int Interpreter::visitIntNumNode(IntNumNode *node)
{
	IntNumToken *token = (IntNumToken *) node->token;
	return token->value;
}

int Interpreter::visitBinOpNode(BinOpNode *node)
{
	if (node->lhs == nullptr) {
		throw ParseError("missing left operand");
	}

	if (node->rhs == nullptr) {
		throw ParseError("missing right operand");
	}

	int lhs = visitNode(node->lhs);
	int rhs = visitNode(node->rhs);
	switch (node->token->type) {
		case Token::TokenType::TYPE_FLOAT_DIV: return lhs / rhs;
		case Token::TokenType::TYPE_MUL: return lhs * rhs;
		case Token::TokenType::TYPE_SUB: return lhs - rhs;
		case Token::TokenType::TYPE_PLUS: return lhs + rhs;
		default: std::string msg = "unknown bin op, type is: ";
			msg += node->token->type;
			throw ParseError("unknown bin op");
	}
}

int Interpreter::visitUnaryNode(UnaryNode *node)
{
	if (node->child == nullptr) {
		throw ParseError("missing unary operand");
	}

	if (node->token->type == Token::TokenType::TYPE_SUB) {
		return -visitNode(node->child);
	}

	if (node->token->type == Token::TokenType::TYPE_PLUS) {
		return visitNode(node->child);
	}

	std::string msg = "unknown unary op, type is: ";
	msg += node->token->type;
	throw ParseError(msg);
}

void Interpreter::interpret()
{
	ASTNode *root = mParser.parse();
	visitCompoundStatementNode((CompoundStatementNode *) root);
}

#ifdef DEBUG
#include <iostream>
void Interpreter::dumpSymbolTable()
{
	for (std::map<std::string, int>::iterator it = mSymbolTable.begin(); it != mSymbolTable.end(); ++it) {
		std::cout << "key: " << it->first << " value: " << it->second << std::endl;
	}
}
#endif

void Interpreter::visitCompoundStatementNode(CompoundStatementNode *root)
{
	std::for_each(root->statements.cbegin(), root->statements.cend(), [this](StatementNode *child)
	{
		if (child->type == ASTNode::Type::COMPOUND) {
			visitCompoundStatementNode((CompoundStatementNode *) child);
			return;
		}

		if (child->type == ASTNode::Type::ASSIGN) {
			visitAssignStatementNode((AssignStatementNode *) child);
			return;
		}

		if (child->type == ASTNode::Type::NO_OP) {
			visitNoOpStatementNode((NoOpStatementNode *) child);
			return;
		}

		std::string msg = "unknown ast node, type is: ";
		msg += child->type;
		throw ParseError(msg);
	});
}

void Interpreter::visitNoOpStatementNode(NoOpStatementNode *node)
{
	/* do nothing */
}

void Interpreter::visitAssignStatementNode(AssignStatementNode *node)
{
	IdToken *lv = (IdToken *) node->lv->token;
	mSymbolTable[lv->value] = visitNode(node->rv);
}

int Interpreter::visitVarNode(VarNode *node)
{
	IdToken *lv = (IdToken *) node->token;
	auto it = mSymbolTable.find(lv->value);
	if (it == mSymbolTable.end()) {
		std::string msg = "unknown symbol: ";
		msg += lv->value;
		throw ParseError(msg);
	}

	return it->second;
}

double Interpreter::visitRealNumNode(RealNumNode *node)
{
	RealNumToken *token = (RealNumToken *) node->token;
	return token->value;
}