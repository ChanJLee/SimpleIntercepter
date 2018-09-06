//
// Created by chan on 2018/8/22.
//

#include "Parser.h"
#include "../exception/ParseError.h"
#include "ast/BinOpNode.h"
#include "ast/NumNode.h"
#include "ast/UnaryNode.h"
#include "ast/CompoundStatementNode.h"
#include "ast/NoOpStatementNode.h"
#include "ast/AssignStatementNode.h"

Parser::Parser(Stream *stream)
	: mLexer(stream)
{
	mCurrentToken = mLexer.next();
}

ASTNode *Parser::exp()
{
	ASTNode *lhs = term();
	while (mCurrentToken->type == Token::TokenType::TYPE_SUB ||
		mCurrentToken->type == Token::TokenType::TYPE_PLUS) {
		Token *token = mCurrentToken;
		eat(token->type);
		lhs = new BinOpNode(token, lhs, term());
	}
	return lhs;
}

ASTNode *Parser::term()
{
	ASTNode *lhs = factor();
	while (mCurrentToken->type == Token::TokenType::TYPE_FLOAT_DIV ||
		mCurrentToken->type == Token::TokenType::TYPE_MUL) {
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
		eat(Token::TokenType::TYPE_RIGHT_BRACKET, "missing )");
		return result;
	}

	if (token->type == Token::TokenType::TYPE_NUMBER) {
		eat(Token::TokenType::TYPE_NUMBER);
		return new NumNode((NumToken *const) token);
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

	std::string msg = "invalid token, type is";
	msg += token->type;
	throw ParseError(msg);
}

void Parser::eat(int type)
{
	try {
		eat(type, "");
	}
	catch (const ParseError error) {
		std::string msg = "invalid state, need is: ";
		msg += type;
		msg += ", and current is ";
		msg += mCurrentToken->type;
		throw ParseError(msg);
	}
}

void Parser::eat(int type, const std::string &msg)
{
	if (mCurrentToken->type == type) {
		mCurrentToken = mLexer.next();
		return;
	}

	throw ParseError(msg);
}

ASTNode *Parser::program()
{
	ASTNode *root = compound();
	eat(Token::TokenType::TYPE_DOT, "missing .");
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
	VarNode *lv = variable();
	Token *op = mCurrentToken;
	eat(op->type);
	return new AssignStatementNode(lv, op, exp());
}

StatementNode *Parser::empty()
{
	return new NoOpStatementNode();
}

VarNode *Parser::variable()
{
	VarNode *var = new VarNode((IdToken *const) mCurrentToken);
	eat(Token::TokenType::TYPE_ID);
	return var;
}

ASTNode *Parser::parse()
{
	ASTNode *root = program();
	eat(Token::TokenType::TYPE_EOF, "eof error");
	return root;
}
