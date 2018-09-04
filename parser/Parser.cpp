//
// Created by chan on 2018/8/22.
//

#include "Parser.h"
#include "../exception/ParseError.h"
#include "ast/BinOpNode.h"
#include "ast/NumNode.h"
#include "ast/UnaryNode.h"
#include "ast/CompoundStatementNode.h"
#include "ast/NoOpNode.h"
#include "ast/AssignStatementNode.h"
#include <exception>

Parser::Parser(Stream *stream)
	: mLexer(stream)
{
	mCurrentToken = mLexer.next();
}

ASTNode *Parser::exp()
{
	ASTNode *lhs = term();
	while (mCurrentToken->type == Token::TokenType::TYPE_SUB || mCurrentToken->type == Token::TokenType::TYPE_PLUS) {
		Token *token = mCurrentToken;
		eat(token->type);
		lhs = new BinOpNode(token, lhs, term());
	}
	return lhs;
}

ASTNode *Parser::term()
{
	ASTNode *lhs = factor();
	while (mCurrentToken->type == Token::TokenType::TYPE_DIV || mCurrentToken->type == Token::TokenType::TYPE_MUL) {
		Token *token = mCurrentToken;
		eat(token->type);
		lhs = new BinOpNode(token, lhs, factor());
	}
	return lhs;
}

ASTNode *Parser::factor()
{
	Token *token = mCurrentToken;
	if (token->type == Token::TokenType::TYPE_LEFT_BRACKET) {
		eat(Token::TokenType::TYPE_LEFT_BRACKET);
		ASTNode *result = exp();
		try {
			eat(Token::TokenType::TYPE_RIGHT_BRACKET, "missing )");
		}
		catch (std::exception e) {
			if (result != nullptr) {
				delete result;
			}
			delete token;
			throw e;
		}
		return result;
	}

	if (token->type == Token::TokenType::TYPE_NUMBER) {
		eat(Token::TokenType::TYPE_NUMBER);
		return new NumNode(token);
	}

	if (token->type == Token::TokenType::TYPE_PLUS) {
		eat(Token::TokenType::TYPE_PLUS);
		return new UnaryNode(token, factor());
	}

	if (token->type == Token::TokenType::TYPE_SUB) {
		eat(Token::TokenType::TYPE_SUB);
		return new UnaryNode(token, factor());
	}

	if (token->type == Token::TokenType::TYPE_ID) {
		return variable();
	}

	throw ParseError("invalid token");
}

void Parser::eat(int type)
{
	eat(type, "invalid state");
}

void Parser::eat(int type, const char *errorMsg)
{
	if (mCurrentToken->type == type) {
		mCurrentToken = mLexer.next();
		return;
	}

	throw ParseError(errorMsg);
}

ASTNode *Parser::program()
{
	ASTNode *root = compound();
	eat(Token::TokenType::TYPE_DOT);
	return root;
}

StatementNode *Parser::compound()
{
	eat(Token::TokenType::TYPE_BEGIN);
	std::vector<StatementNode *> statements;
	StatementNode *child = statement();
	statements.push_back(child);
	while (mCurrentToken->type == Token::TokenType::TYPE_SEMI) {
		eat(Token::TokenType::TYPE_SEMI);
		child = statement();
		statements.push_back(child);
	}

	eat(Token::TokenType::TYPE_END);
	return new CompoundStatementNode(statements);;
}

StatementNode *Parser::statement()
{
	if (mCurrentToken->type == Token::TokenType::TYPE_BEGIN) {
		return compound();
	}

	if (mCurrentToken->type == Token::TokenType::TYPE_ID) {
		return assignStatement();
	}

	return empty();
}

StatementNode *Parser::assignStatement()
{
	Var *lv = variable();
	Token *op = mCurrentToken;
	eat(Token::TYPE_ASSIGN);
	delete op;
	return new AssignStatementNode(lv, exp());
}

StatementNode *Parser::empty()
{
	return new NoOpNode();
}

Var *Parser::variable()
{
	Var *var = new Var(mCurrentToken);
	eat(Token::TokenType::TYPE_ID);
	return var;
}

ASTNode *Parser::parse()
{
	ASTNode *root = program();
	eat(EOF, "eof error");
	return root;
}
