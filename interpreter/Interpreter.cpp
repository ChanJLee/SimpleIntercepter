//
// Created by chan on 2018/8/19.
//

#include "Interpreter.h"
#include "../exception/ParseError.h"

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
	else if (node->type == ASTNode::Type::VAR) {
		return visit((VarNode *) node);
	}

	throw ParseError("invalid exp");
}

int Interpreter::visit(NumNode *node)
{
	NumToken *token = (NumToken *) node->token;
	return token->value;
}

int Interpreter::visit(BinOpNode *node)
{
	// TODO error msg
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

	// TODO error msg
	throw ParseError("unknown unary op");
}

void Interpreter::interpret()
{
	ASTNode *root = mParser.parse();
	visitCompoundStatementNode((CompoundStatementNode *) root);
}

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

		throw ParseError("invalid ast node");
	});
}

void Interpreter::visitNoOpStatementNode(NoOpStatementNode *node)
{
	/* do nothing */
}

void Interpreter::visitAssignStatementNode(AssignStatementNode *node)
{
	IdToken *lv = (IdToken *) node->lv->token;
	mSymbolTable[lv->value] = visit(node->rv);
}

int Interpreter::visit(VarNode *node)
{
	IdToken *lv = (IdToken *) node->token;
	auto it = mSymbolTable.find(lv->value);
	if (it == mSymbolTable.end()) {
		throw ParseError("unknown symbol");
	}

	return it->second;
}

