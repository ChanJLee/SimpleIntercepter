//
// Created by chan on 2018/8/19.
//

#include "Interpreter.h"
#include "../exception/ParseError.h"
#include "../st/SymbolTable.h"
#ifdef DEBUG
#include <iostream>
#endif

const Result Interpreter::NO_VALUE = {
	.type = Token::TokenType::TYPE_NO_MEANING
};

Result Interpreter::visitNode(ASTNode *node)
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

Result Interpreter::visitIntNumNode(IntNumNode *node)
{
	IntNumToken *token = (IntNumToken *) node->token;
	return Result{
		.type = Token::TokenType::TYPE_INTEGER,
		.value.i = token->value
	};
}

#ifndef RETURN_BIN_OP_
#define RETURN_BIN_OP_(type, lr, rr, op) \
    if (lr.type == Token::TokenType::TYPE_REAL && rr.type == Token::TokenType::TYPE_REAL) { \
        return BUILD_IN_VALUE_TO_RESULT(type, lr.value.r op rr.value.r); \
    } else if (lr.type == Token::TokenType::TYPE_INTEGER && rr.type == Token::TokenType::TYPE_INTEGER) { \
        return BUILD_IN_VALUE_TO_RESULT(type, lr.value.i op rr.value.i); \
    } else if (lr.type == Token::TokenType::TYPE_INTEGER && rr.type == Token::TokenType::TYPE_REAL) { \
        return BUILD_IN_VALUE_TO_RESULT(type, lr.value.i op rr.value.r); \
    } else { \
        return BUILD_IN_VALUE_TO_RESULT(type, lr.value.r op rr.value.i); \
    }
#define RETURN_BIN_OP RETURN_BIN_OP_
#endif

Result Interpreter::visitBinOpNode(BinOpNode *node)
{
	if (node->lhs == nullptr) {
		throw ParseError("missing left operand");
	}

	if (node->rhs == nullptr) {
		throw ParseError("missing right operand");
	}

	const Result &lr = visitNode(node->lhs);
	const Result &rr = visitNode(node->rhs);

	Token::TokenType type = Token::TokenType::TYPE_INTEGER;
	if (lr.type == Token::TokenType::TYPE_REAL || rr.type == Token::TokenType::TYPE_REAL) {
		type = Token::TokenType::TYPE_REAL;
	}

	switch (node->token->type) {
		case Token::TokenType::TYPE_REAL_DIV:
		case Token::TokenType::TYPE_INT_DIV: RETURN_BIN_OP(type, lr, rr, /)
		case Token::TokenType::TYPE_MUL: RETURN_BIN_OP(type, lr, rr, *)
		case Token::TokenType::TYPE_SUB: RETURN_BIN_OP(type, lr, rr, -)
		case Token::TokenType::TYPE_PLUS: RETURN_BIN_OP(type, lr, rr, +)
		default: {
			std::string msg = "unknown bin op, type is: ";
			msg += node->token->type;
			throw ParseError("unknown bin op");
		}
	}
}

Result Interpreter::visitUnaryNode(UnaryNode *node)
{
	if (node->child == nullptr) {
		throw ParseError("missing unary operand");
	}

	if (node->token->type == Token::TokenType::TYPE_SUB) {
		const Result &result = visitNode(node->child);
		return BUILD_IN_VALUE_TO_RESULT(result.type, -RESULT_TO_BUILD_IN_VALUE_(result));
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
	visitProgramNode(mRoot);
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
	mCurrentTable->insert(lv->value, visitNode(node->rv));
}

Result Interpreter::visitVarNode(VarNode *node)
{
	IdToken *lv = (IdToken *) node->token;
	const Result result = mCurrentTable->lookup(lv->value, NO_VALUE);
	if (result.type == Token::TokenType::TYPE_NO_MEANING) {
		std::string msg = "unknown symbol: ";
		msg += lv->value;
		throw ParseError(msg);
	}

	return result;
}

Result Interpreter::visitRealNumNode(RealNumNode *node)
{
	RealNumToken *token = (RealNumToken *) node->token;
	return Result{
		.type = Token::TokenType::TYPE_REAL,
		.value.r = token->value
	};
}

void Interpreter::visitProgramNode(ProgramNode *node)
{
	IdToken *idToken = nullptr;
#ifdef DEBUG
	if (node->token != nullptr) {
		idToken = (IdToken *) node->token;
		std::cout << "current program: " << idToken->value << std::endl;
	}
	else {
		std::cout << "current program: <no id>" << std::endl;
	}
#endif
	mCurrentTable = new KVTable(idToken == nullptr ? "unknown" : idToken->value, nullptr);
	visitBlockNode(node->block);
}

void Interpreter::visitBlockNode(BlockNode *node)
{
	visitDeclarationsNode(node->declarations);
	visitProceduresNode(node->procedures);
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
						  mCurrentTable->insert(id->value, BUILD_IN_VALUE_TO_RESULT(declaration->type, 0));
					  }
				  });
}

#ifdef DEBUG
void Interpreter::dumpSymbolTable()
{
	auto symbolTable = mCurrentTable->getMap();
	for (Iterator it = symbolTable.begin(); it != symbolTable.end(); ++it) {
		std::cout << "key: " << it->first << " value: " << RESULT_TO_BUILD_IN_VALUE(it->second) << std::endl;
	}
}

void Interpreter::visitProceduresNode(ProceduresNode *pNode)
{

}

Interpreter::~Interpreter()
{
	delete mCurrentTable;
}
#endif
