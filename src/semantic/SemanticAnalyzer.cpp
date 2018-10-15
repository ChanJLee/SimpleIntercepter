//
// Created by chan on 2018/9/11.
//

#include <term.h>
#include "SemanticAnalyzer.h"
#include "../token/IdToken.h"
#include "../exception/ParseError.h"
#include "../parser/ast/AssignStatementNode.h"
#include "../parser/ast/BinOpNode.h"
#include "../parser/ast/UnaryNode.h"
#include "../parser/ast/ProceduresNode.h"
#include "../log/log.h"

SemanticAnalyzer::SemanticAnalyzer(ProgramNode *tree)
	: mTree(tree)
{

}

void SemanticAnalyzer::check()
{
	auto idToken = (IdToken *) mTree->token;
	LOG("semantic, check program, id: %s\n", idToken->value.c_str());
	mCurrentTable = new SymbolTable(idToken->value, nullptr);
	checkBlock(mTree->block);
	delete mCurrentTable;
}

void SemanticAnalyzer::checkBlock(BlockNode *node)
{
	checkDeclarations(node->declarations);
	checkProcedures(node->procedures);
	checkCompoundStatement((CompoundStatementNode *) node->compoundStatementNode);
}

void SemanticAnalyzer::checkDeclarations(DeclarationsNode *node)
{
	std::for_each(
		node->declarations.cbegin(),
		node->declarations.cend(),
		[this](DeclarationsNode::Declaration *declaration)
		{
			if (declaration != nullptr) {
				auto id = (IdToken *) declaration->id;
				LOG("semantic: insert decl, id %s type %d\n", id->value.c_str(), declaration->type);
				insert(id->value, declaration->type);
			}
		});
}

void SemanticAnalyzer::checkCompoundStatement(CompoundStatementNode *node)
{
	std::for_each(node->statements.cbegin(), node->statements.cend(), [this](StatementNode *statement)
	{
		if (statement->type == ASTNode::Type::COMPOUND) {
			checkCompoundStatement((CompoundStatementNode *) statement);
			return;
		}

		if (statement->type == ASTNode::Type::ASSIGN) {
			checkAssignStatement((AssignStatementNode *) statement);
			return;
		}

		if (statement->type == ASTNode::Type::NO_OP) {
			checkNoOp((NoOpStatementNode *) statement);
			return;
		}

		String msg = "unknown statement, type is";
		msg += std::to_string(statement->type);
		throw ParseError(msg);
	});
}

void SemanticAnalyzer::insert(const SemanticAnalyzer::String &key, Token::TokenType value)
{
	if (value == Token::TokenType::TYPE_REAL) {
		if (!mCurrentTable->insert(key, Symbol::REAL)) {
			String msg = "define " + key + " twice";
			throw ParseError(msg);
		}
		return;
	}

	if (value == Token::TokenType::TYPE_INTEGER) {
		if (!mCurrentTable->insert(key, Symbol::INT)) {
			String msg = "define " + key + " twice";
			throw ParseError(msg);
		}
		return;
	}

	String msg = "unknown type: ";
	msg += std::to_string(value);
	throw ParseError(msg);
}

Symbol &SemanticAnalyzer::lookup(const SemanticAnalyzer::String &key)
{
	Symbol undefined = Symbol::UNDEFINED;
	Symbol &result = mCurrentTable->lookup(key, undefined);
	if (result == undefined) {
		throw ParseError("can not find symbol: " + key);
	}
	return result;
}

void SemanticAnalyzer::checkAssignStatement(AssignStatementNode *node)
{
	VarNode *lv = node->lv;
	LOG("semantic, check assign\n");
	Symbol lhs = checkVar(lv);
	Symbol rhs = checkExp(node->rv);
	if (lhs == Symbol::INT && rhs == Symbol::REAL) {
		auto id = (IdToken *) node->lv->token;
		String msg = "can not assign REAL to " + id->value + ", it's type is INT";
		throw ParseError(msg);
	}
}

Symbol SemanticAnalyzer::checkVar(VarNode *node)
{
	auto id = (IdToken *) node->token;
	LOG("semantic, lookup var: %s\n", id->value.c_str());
	Symbol type = lookup(id->value);
	if (type == Symbol::UNDEFINED) {
		String msg = "undefined symbol " + id->value;
		throw ParseError(msg);
	}
	return type;
}

Symbol SemanticAnalyzer::checkExp(ASTNode *node)
{
	if (node->type == ASTNode::Type::INT_NUM) {
		LOG("semantic, check exp int\n");
		return Symbol::INT;
	}
	else if (node->type == ASTNode::Type::BIN) {
		LOG("semantic, check exp bin op\n");
		return checkBinOp((BinOpNode *) node);
	}
	else if (node->type == ASTNode::Type::UNARY) {
		LOG("semantic, check exp unary\n");
		return visitUnaryNode((UnaryNode *) node);
	}
	else if (node->type == ASTNode::Type::VAR) {
		LOG("semantic, check exp var\n");
		return checkVar((VarNode *) node);
	}
	else if (node->type == ASTNode::Type::REAL_NUM) {
		LOG("semantic, check exp real\n");
		return Symbol::REAL;
	}

	std::string msg = "unknown ast node, type is: ";
	msg += std::to_string(node->token->type);
	throw ParseError(msg);
}

Symbol SemanticAnalyzer::checkBinOp(BinOpNode *node)
{
	Symbol lhs = checkExp(node->lhs);
	Symbol rhs = checkExp(node->rhs);
	Symbol result = (lhs == Symbol::REAL || rhs == Symbol::REAL) ? Symbol::REAL : Symbol::INT;

	if (Token::TokenType::TYPE_INT_DIV == node->token->type &&
		result == Symbol::REAL) {
		throw ParseError("DIV can be used for INT only");
	}

	if (node->token->type != Token::TokenType::TYPE_INT_DIV &&
		node->token->type != Token::TokenType::TYPE_REAL_DIV &&
		node->token->type != Token::TokenType::TYPE_PLUS &&
		node->token->type != Token::TokenType::TYPE_MUL &&
		node->token->type != Token::TokenType::TYPE_SUB) {
		throw ParseError("unknown binary op");
	}

	return result;
}

Symbol SemanticAnalyzer::visitUnaryNode(UnaryNode *node)
{
	return checkExp(node->child);
}

void SemanticAnalyzer::checkNoOp(NoOpStatementNode *node)
{
	/* do nothing */
}

void SemanticAnalyzer::checkProcedures(ProceduresNode *node)
{
	SymbolTable *context = mCurrentTable;
	std::for_each(node->procedures.cbegin(), node->procedures.cend(), [&](ProceduresNode::Procedure *procedure)
	{
		IdToken *idToken = procedure->id;
		auto localTable = new SymbolTable(idToken->value, context);
		mCurrentTable = localTable;
		std::for_each(procedure->formalParameters->parameters.cbegin(),
					  procedure->formalParameters->parameters.cend(),
					  [&](FormalParametersNode::Parameter *parameter)
					  {
						  auto id = (IdToken *) parameter->id;
						  LOG("semantic, insert procedures parameters, id: %s, type: %d\n",
							  id->value.c_str(),
							  parameter->type);
						  insert(id->value, parameter->type);
					  });
		checkBlock(procedure->block);
		delete localTable;
		mCurrentTable = context;
	});
}

SemanticAnalyzer::~SemanticAnalyzer()
{
	delete mCurrentTable;
}