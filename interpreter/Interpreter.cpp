//
// Created by chan on 2018/8/19.
//

#include "Interpreter.h"
#include "../st/SymbolTable.h"
#include "../parser/ast/ProceduresNode.h"
#ifdef DEBUG
#include <iostream>
#endif

Result Interpreter::INVALID_RESULT = {
	.type = Token::TokenType::TYPE_NONE
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
	else {
		return visitRealNumNode((RealNumNode *) node);
	}
}

Result Interpreter::visitIntNumNode(IntNumNode *node)
{
	auto *token = (IntNumToken *) node->token;
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
	const Result &lr = visitNode(node->lhs);
	const Result &rr = visitNode(node->rhs);

	Token::TokenType type = Token::TokenType::TYPE_INTEGER;
	if (lr.type == Token::TokenType::TYPE_REAL ||
		rr.type == Token::TokenType::TYPE_REAL ||
		node->token->type == Token::TokenType::TYPE_REAL_DIV) {
		type = Token::TokenType::TYPE_REAL;
	}

	switch (node->token->type) {
		case Token::TokenType::TYPE_INT_DIV: RETURN_BIN_OP(type, lr, rr, /)
		case Token::TokenType::TYPE_REAL_DIV: RETURN_BIN_OP(type, lr, rr, * 1.0 /)
		case Token::TokenType::TYPE_MUL: RETURN_BIN_OP(type, lr, rr, *)
		case Token::TokenType::TYPE_SUB: RETURN_BIN_OP(type, lr, rr, -)
		default: RETURN_BIN_OP(type, lr, rr, +)
	}
}

Result Interpreter::visitUnaryNode(UnaryNode *node)
{
	if (node->token->type == Token::TokenType::TYPE_SUB) {
		const Result &result = visitNode(node->child);
		return BUILD_IN_VALUE_TO_RESULT(result.type, -RESULT_TO_BUILD_IN_VALUE_(result));
	}

	return visitNode(node->child);
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
	});
}

void Interpreter::visitNoOpStatementNode(NoOpStatementNode *node)
{
	/* do nothing */
}

void Interpreter::visitAssignStatementNode(AssignStatementNode *node)
{
	auto *lv = (IdToken *) node->lv->token;
	Result &record = mCurrentTable->lookup(lv->value, INVALID_RESULT);
	const Result &rhs = visitNode(node->rv);
	if (record.type == Token::TokenType::TYPE_INTEGER) {
		record.value.i = RESULT_TO_BUILD_IN_VALUE(rhs);
	}
	else {
		record.value.r = RESULT_TO_BUILD_IN_VALUE(rhs);
	}
}

Result Interpreter::visitVarNode(VarNode *node)
{
	auto *lv = (IdToken *) node->token;
	const Result result = mCurrentTable->lookup(lv->value, INVALID_RESULT);
	return result;
}

Result Interpreter::visitRealNumNode(RealNumNode *node)
{
	auto *token = (RealNumToken *) node->token;
	return Result{
		.type = Token::TokenType::TYPE_REAL,
		.value.r = token->value
	};
}

void Interpreter::visitProgramNode(ProgramNode *node)
{
	auto *idToken = (IdToken *) node->token;
	mCurrentTable = new KVTable(idToken->value, nullptr);
	visitBlockNode(node->block);
#ifdef DEBUG
	std::cout << "current program: " << idToken->value << std::endl;
	dumpSymbolTable();
#endif
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
						  auto *id = (IdToken *) declaration->id;
						  mCurrentTable->insert(id->value, BUILD_IN_VALUE_TO_RESULT(declaration->type, 0));
					  }
				  });
}

#ifdef DEBUG
void Interpreter::dumpSymbolTable()
{
	if (mCurrentTable == nullptr) {
		return;
	}

	auto symbolTable = mCurrentTable->getMap();
	for (auto it = symbolTable.begin(); it != symbolTable.end(); ++it) {
		std::cout << "key: " << it->first << " value: " << RESULT_TO_BUILD_IN_VALUE(it->second) << std::endl;
	}
}
#endif

void Interpreter::visitProceduresNode(ProceduresNode *node)
{
	KVTable *context = mCurrentTable;
	std::for_each(node->procedures.cbegin(), node->procedures.cend(), [&](ProceduresNode::Procedure *procedure)
	{
		IdToken *idToken = procedure->id;
		auto *localTable = new KVTable(idToken->value, context);
		mCurrentTable = localTable;
		std::for_each(procedure->formalParameters->parameters.cbegin(),
					  procedure->formalParameters->parameters.cend(),
					  [this](FormalParametersNode::Parameter *parameter)
					  {
						  auto paramId = (IdToken *) parameter->id;
						  mCurrentTable->insert(paramId->value, BUILD_IN_VALUE_TO_RESULT(parameter->type, 0));
					  });
		visitBlockNode(procedure->block);
#ifdef DEBUG
		std::cout << "current procedure: " << idToken->value << std::endl;
		dumpSymbolTable();
#endif
		delete localTable;
		mCurrentTable = context;
	});
}

Interpreter::~Interpreter()
{
	delete mCurrentTable;
}
