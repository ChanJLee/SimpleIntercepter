//
// Created by chan on 2018/8/22.
//

#include "Lexer.h"
#include "../exception/ParseError.h"
#include <cstdlib>
#include <string>

Lexer::Lexer(Stream *stream)
	: mStream(stream)
{}

Token Lexer::next()
{
	// skip blank
	char ch;
	while (mStream->hasNext && (ch = mStream->next()) == ' ') {}
	if (!mStream->hasNext()) {
		return Token(TYPE_EOF);
	}

	if (ch == '(') {
		return Token(TYPE_LEFT_BRACKET);
	}

	if (ch == ')') {
		return Token(TYPE_RIGHT_BRACKET);
	}

	if (ch >= '0' && ch <= '9') {
		mStream->back();
		return nextNumber();
	}

	if (ch == '+') {
		return Token(TYPE_PLUS);
	}

	if (ch == '-') {
		return Token(TYPE_SUB);
	}

	if (ch == '/') {
		return Token(TYPE_DIV);
	}

	if (ch == '*') {
		return Token(TYPE_MUL);
	}

	throw ParseError("unknown char");
}

bool Lexer::hasNext()
{
	return mStream != nullptr && mStream->hasNext();
}

Token Lexer::nextNumber()
{
	char ch = mStream->next();
	std::string num;
	while (ch >= '0' && ch <= '9') {
		num += ch;
		ch = mStream->next();
	}
	mStream->back();
	return Token(TYPE_NUMBER, atoi(num.c_str()));
}
