//
// Created by chan on 2018/8/22.
//

#include "Lexer.h"
#include "../exception/ParseError.h"
#include <string>
#include "../utils/CharUtils.h"

Lexer::Lexer(Stream *stream)
	: mStream(stream)
{}

Token *Lexer::next()
{
	// skip blank
	char ch = EOF;
	while ((ch = mStream->next()) == ' ') {}
	if (ch == EOF) {
		return new Token(Token::TokenType::TYPE_EOF);
	}

	if (ch == '(') {
		return new Token(Token::TokenType::TYPE_LEFT_BRACKET);
	}

	if (ch == ')') {
		return new Token(Token::TokenType::TYPE_RIGHT_BRACKET);
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

	if (ch == '.') {
		return new Token(Token::TokenType::TYPE_DOT);
	}

	if (ch == ';') {
		return new Token(Token::TokenType::TYPE_SEMI);
	}

	if (ch == ':') {
		mStream->back();
		return nextColon();
	}

	if (is_num(ch)) {
		mStream->back();
		return nextNumber();
	}

	if (is_alpha(ch)) {
		mStream->back();
		return nextID();
	}

	throw ParseError("unknown char");
}

Token *Lexer::nextNumber()
{
	char ch = mStream->next();
	std::string num;
	while (is_num(ch)) {
		num += ch;
		ch = mStream->next();
	}

	mStream->back();
	int *value = new int(atoi(num.c_str()));
	return new Token(Token::TokenType::TYPE_NUMBER, value);
}

Token *Lexer::nextID()
{
	char ch = mStream->next();
	std::string *id = new std::string();
	do {
		(*id) += ch;
		ch = mStream->next();
	}
	while (is_alpha(ch) || is_num(ch));
	mStream->back();

	if ((*id) == "BEGIN") {
		delete id;
		return new Token(Token::TokenType::TYPE_BEGIN);
	}

	if ((*id) == "END") {
		delete id;
		return new Token(Token::TokenType::TYPE_END);
	}

	return new Token(Token::TokenType::TYPE_ID, id);
}

Token *Lexer::nextColon()
{
	// ignore ':'
	mStream->next();
	char ch = mStream->next();
	if (ch != '=') {
		mStream->back();
		return new Token(Token::TokenType::TYPE_COLON);
	}

	return new Token(Token::TokenType::TYPE_ASSIGN);
}
