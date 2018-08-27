//
// Created by chan on 2018/8/22.
//

#include "Parser.h"
#include "../exception/ParseError.h"
#include "ast/BinOpNode.h"
#include "../exception/EOFError.h"
#include "ast/NumNode.h"

Parser::Parser(Stream *stream)
	: mLexer(stream)
{
}

ASTNode *Parser::exp()
{
	ASTNode *lhs = term();
	while (mLexer.hasNext()) {
		Token* token = mLexer.next();
		if (token->type != TYPE_SUB && token->type != TYPE_PLUS) {
			if (lhs != nullptr) {
				delete lhs;
			}
			delete token;
			delete lhs;
			throw ParseError("invalid token in exp");
		}

		// memory leak
		lhs = new BinOpNode(token, lhs, term());
	}

	return lhs;
}

ASTNode *Parser::term()
{
	ASTNode *lhs = factor();
	while (mLexer.hasNext()) {
		Token* token = mLexer.next();
		if (token->type != TYPE_DIV && token->type != TYPE_MUL) {
			mLexer.back(token);
			delete token;
			break;
		}
		lhs = new BinOpNode(token, lhs, factor());
	}
	return lhs;
}

ASTNode *Parser::factor()
{
	if (!mLexer.hasNext()) {
		throw EOFError("factor error");
	}

	Token* token = mLexer.next();
	if (token->type == TYPE_LEFT_BRACKET) {
		ASTNode *result = exp();
		if (!mLexer.hasNext() || mLexer.next()->type != TYPE_RIGHT_BRACKET) {
			if (result != nullptr) {
				delete result;
			}

			delete token;
			throw EOFError("need right bracket");
		}
		return result;
	}

	if (token->type == TYPE_NUMBER) {
		return new NumNode(token);
	}

	throw ParseError("invalid token");
}