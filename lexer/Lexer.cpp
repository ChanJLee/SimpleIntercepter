//
// Created by chan on 2018/8/22.
//

#include "Lexer.h"
#include "../exception/ParseError.h"
#include <string>

Lexer::Lexer(Stream *stream)
	: mStream(stream)
{}

Token *Lexer::next()
{
	// skip blank
	char ch = EOF;
	while ((ch = mStream->next()) == ' ') {}
	if (ch == EOF) {
		return new Token(Token::TokenType::TYPE_EOF, 0);
	}

	if (ch == '(') {
		return new Token(Token::TokenType::TYPE_LEFT_BRACKET);
	}

	if (ch == ')') {
		return new Token(Token::TokenType::TYPE_RIGHT_BRACKET);
	}

	if (ch >= '0' && ch <= '9') {
		mStream->back();
		return nextNumber();
	}

	if (ch == '+') {
		return new Token(Token::TokenType::TYPE_PLUS);
	}

	if (ch == '-') {
		return new Token(Token::TokenType::TYPE_SUB);
	}

	if (ch == '/') {
		return new Token(Token::TokenType::TYPE_DIV);
	}

	if (ch == '*') {
		return new Token(Token::TokenType::TYPE_MUL);
	}

	throw ParseError("unknown char: " + ch);
}

Token *Lexer::nextNumber()
{
	char ch = mStream->next();
	std::string num;
	while (ch >= '0' && ch <= '9') {
		num += ch;
		ch = mStream->next();
	}

	mStream->back();
	int *value = new int(atoi(num.c_str()));
	return new Token(Token::TokenType::TYPE_NUMBER, value);
}