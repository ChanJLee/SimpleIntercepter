//
// Created by chan on 2018/8/19.
//

#include "Interpreter.h"
#include "../exception/ParseError.h"
#ifdef DEBUG
#include <iostream>
#endif

double Interpreter::visitNode(ASTNode *node)
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
	else if (node->type == ASTNode::Type::REAL_NUM) {
		return visitRealNumNode((RealNumNode *) node);
	}

	std::string msg = "unknown ast node, type is: ";
	msg += node->token->type;
	throw ParseError(msg);
}

double Interpreter::visitIntNumNode(IntNumNode *node)
{
	IntNumToken *token = (IntNumToken *) node->token;
	return token->value;
}

double Interpreter::visitBinOpNode(BinOpNode *node)
{
	if (node->lhs == nullptr) {
		throw ParseError("missing left operand");
	}

	if (node->rhs == nullptr) {
		throw ParseError("missing right operand");
	}

	double lhs = visitNode(node->lhs);
	double rhs = visitNode(node->rhs);
	switch (node->token->type) {
		case Token::TokenType::TYPE_REAL_DIV: return lhs / rhs;
		case Token::TokenType::TYPE_MUL: return lhs * rhs;
		case Token::TokenType::TYPE_SUB: return lhs - rhs;
		case Token::TokenType::TYPE_PLUS: return lhs + rhs;
		case Token::TokenType::TYPE_INT_DIV: return (int) lhs / (int) rhs;
		default: std::string msg = "unknown bin op, type is: ";
			msg += node->token->type;
			throw ParseError("unknown bin op");
	}
}

double Interpreter::visitUnaryNode(UnaryNode *node)
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
	ProgramNode *root = mParser.parse();
	visitProgramNode(root);
}

void Interpreter::visitCompoundStatementNode(CompoundStatementNode *node)
{
	std::for_each(node->statements.cbegin(), node->statements.cend(), [this](StatementNode *child)
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

double Interpreter::visitVarNode(VarNode *node)
{
	IdToken *lv = (IdToken *) node->token;
	Iterator it = mSymbolTable.find(lv->value);
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

void Interpreter::visitProgramNode(ProgramNode *node)
{
#ifdef DEBUG
	IdToken *idToken = (IdToken *) node->token;
	std::cout << "current program: " << idToken->value << std::endl;
#endif
	visitBlockNode(node->block);
}

void Interpreter::visitBlockNode(BlockNode *node)
{
	visitDeclarationsNode(node->declarations);
	visitCompoundStatementNode((CompoundStatementNode *) node->compoundStatementNode);
}

void Interpreter::visitDeclarationsNode(DeclarationsNode *node)
{
	std::for_each(node->declarations.cbegin(),
				  node->declarations.cend(),
				  [this](DeclarationsNode::Declaration *declaration)
				  {
					  if (declaration != nullptr) {
						  IdToken *id = (IdToken *) declaration->id;
						  // TODO add type info
						  mSymbolTable[id->value] = 0;
					  }
				  });
}

#ifdef DEBUG
void Interpreter::dumpSymbolTable()
{
	for (Iterator it = mSymbolTable.begin(); it != mSymbolTable.end(); ++it) {
		std::cout << "key: " << it->first << " value: " << it->second << std::endl;
	}
}
#endif
