//
// Created by chan on 2018/8/22.
//

#include "Parser.h"
#include "../exception/ParseError.h"
#include "ast/BinOpNode.h"
#include "ast/NumNode.h"
#include "ast/UnaryNode.h"
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

ASTNode *Parser::compound()
{
	return nullptr;
}
