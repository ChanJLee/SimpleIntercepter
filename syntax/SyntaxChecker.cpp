//
// Created by chan on 2018/9/11.
//

#include <term.h>
#include "SyntaxChecker.h"
#include "../token/IdToken.h"
#include "../exception/ParseError.h"
#include "../parser/ast/AssignStatementNode.h"
#include "../parser/ast/BinOpNode.h"
#include "../parser/ast/UnaryNode.h"

SyntaxChecker::SyntaxChecker(ProgramNode *tree)
	: mTree(tree)
{

}

void SyntaxChecker::check()
{
	checkBlock(mTree->block);
}

void SyntaxChecker::checkBlock(BlockNode *node)
{
	checkDeclarations(node->declarations);
	checkCompoundStatement((CompoundStatementNode *) node->compoundStatementNode);
}

void SyntaxChecker::checkDeclarations(DeclarationsNode *node)
{
	std::for_each(
		node->declarations.cbegin(),
		node->declarations.cend(),
		[this](DeclarationsNode::Declaration *declaration)
		{
			if (declaration != nullptr) {
				IdToken *id = (IdToken *) declaration->id;
				putSymbol(id->value, declaration->type);
			}
		});
}

void SyntaxChecker::checkCompoundStatement(CompoundStatementNode *node)
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
		msg += statement->type;
		throw ParseError(msg);
	});
}

void SyntaxChecker::putSymbol(const SyntaxChecker::String &key, Token::TokenType value)
{
	Iterator it = mGlobalSymbolTable.find(key);
	if (it != mGlobalSymbolTable.end()) {
		String msg = "define " + key + " twice";
		throw ParseError(msg);
	}

	if (value == Token::TokenType::TYPE_REAL) {
		mGlobalSymbolTable[key] = Symbol::REAL;
	}
	else if (value == Token::TokenType::TYPE_INTEGER) {
		mGlobalSymbolTable[key] = Symbol::INT;
	}

	String msg = "unknown type: ";
	msg += value;
	throw ParseError(msg);
}

Symbol SyntaxChecker::getSymbol(const SyntaxChecker::String &key)
{

	Iterator it = mGlobalSymbolTable.find(key);
	if (it == mGlobalSymbolTable.end()) {
		return Symbol::UNDEFINED;
	}

	return it->second;
}

void SyntaxChecker::checkAssignStatement(AssignStatementNode *node)
{
	VarNode *lv = node->lv;
	Symbol lhs = checkVar(lv);
	Symbol rhs = checkExp(node->rv);
	if (lhs == Symbol::INT && rhs == Symbol::REAL) {
		IdToken *id = (IdToken *) node->token;
		String msg = "can not assign REAL to " + id->value + ", it's type is INT";
		throw ParseError(msg);
	}
}

Symbol SyntaxChecker::checkVar(VarNode *node)
{
	IdToken *id = (IdToken *) node->token;
	Symbol type = getSymbol(id->value);
	if (type == Symbol::UNDEFINED) {
		String msg = "undefined symbol " + id->value;
		throw ParseError(msg);
	}
	return type;
}

Symbol SyntaxChecker::checkExp(ASTNode *node)
{
	if (node->type == ASTNode::Type::INT_NUM) {
		return Symbol::INT;
	}
	else if (node->type == ASTNode::Type::BIN) {
		return checkBinOp((BinOpNode *) node);
	}
	else if (node->type == ASTNode::Type::UNARY) {
		return visitUnaryNode((UnaryNode *) node);
	}
	else if (node->type == ASTNode::Type::VAR) {
		return checkVar((VarNode *) node);
	}
	else if (node->type == ASTNode::Type::REAL_NUM) {
		return Symbol::REAL;
	}

	std::string msg = "unknown ast node, type is: ";
	msg += node->token->type;
	throw ParseError(msg);
}

Symbol SyntaxChecker::checkBinOp(BinOpNode *node)
{
	Symbol lhs = checkExp(node->lhs);
	Symbol rhs = checkExp(node->rhs);
	Symbol result = (lhs == Symbol::REAL || rhs == Symbol::REAL) ? Symbol::REAL : Symbol::INT;

	if (Token::TokenType::TYPE_INT_DIV == node->token->type &&
		result == Symbol::REAL) {
		throw ParseError("DIV only can be used for INT");
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

Symbol SyntaxChecker::visitUnaryNode(UnaryNode *node)
{
	return checkExp(node->child);
}

void SyntaxChecker::checkNoOp(NoOpStatementNode *node)
{
	/* do nothing */
}
