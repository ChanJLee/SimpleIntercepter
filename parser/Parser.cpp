//
// Created by chan on 2018/8/22.
//

#include "Parser.h"
#include "../exception/ParseError.h"
#include "ast/BinOpNode.h"
#include "ast/NumNode.h"
#include <exception>

Parser::Parser(Stream *stream)
	: mLexer(stream)
{
	mCurrentToken = mLexer.next();
}

ASTNode *Parser::exp()
{
	ASTNode *lhs = term();
	while (mCurrentToken->type == TYPE_SUB || mCurrentToken->type == TYPE_PLUS) {
		Token* token = mCurrentToken;
		lhs = new BinOpNode(token, lhs, term());
		eat(token->type);
	}
	return lhs;
}

ASTNode *Parser::term()
{
	ASTNode *lhs = factor();
	while (mCurrentToken->type == TYPE_DIV || mCurrentToken->type == TYPE_MUL) {
		Token* token = mCurrentToken;
		lhs = new BinOpNode(token, lhs, factor());
		eat(token->type);
	}
	return lhs;
}

ASTNode *Parser::factor()
{
	Token* token = mCurrentToken;
	if (token->type == TYPE_LEFT_BRACKET) {
		eat(TYPE_LEFT_BRACKET);
		ASTNode *result = exp();
		try {
			eat(TYPE_RIGHT_BRACKET, "missing )");
		} catch (std::exception e) {
			if (result != nullptr) {
				delete result;
			}

			delete token;
			throw e;
		}
		return result;
	}

	if (token->type == TYPE_NUMBER) {
		return new NumNode(token);
	}

	throw ParseError("invalid token");
}

void Parser::eat(int type)
{
	eat(type, "invalid state");
}

void Parser::eat(int type, const char *errorMsg)
{
	if (!mLexer.hasNext()) {
		throw ParseError(errorMsg);
	}

	if (mCurrentToken->type == type) {
		mCurrentToken = mLexer.next();
	}

	throw ParseError(errorMsg);
}
