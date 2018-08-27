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
	if (!mLexer.hasNext()) {
		return lhs;
	}

	Token* token = mLexer.next();
	if (token->type != TYPE_SUB && token->type != TYPE_PLUS) {
		if (lhs != nullptr) {
			delete lhs;
		}
		throw ParseError("invalid token in exp");
	}

	if (!mLexer.hasNext()) {
		if (lhs != nullptr) {
			delete lhs;
		}
		throw ParseError("need rhs op");
	}

	return new BinOpNode(token, lhs, term());
}

ASTNode *Parser::term()
{
	ASTNode *lhs = factor();
	if (!mLexer.hasNext()) {
		return lhs;
	}

	Token* token = mLexer.next();
	if (token->type != TYPE_DIV && token->type != TYPE_MUL) {
		if (lhs != nullptr) {
			delete lhs;
		}
		throw ParseError("invalid token in exp");
	}

	if (!mLexer.hasNext()) {
		if (lhs != nullptr) {
			delete lhs;
		}
		throw ParseError("need rhs op");
	}

	return new BinOpNode(token, lhs, factor());
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
			throw EOFError("need right bracket");
		}
		return result;
	}

	if (token->type == TYPE_NUMBER) {
		return new NumNode(token);
	}

	throw ParseError("invalid token");
}