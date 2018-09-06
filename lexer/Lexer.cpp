//
// Created by chan on 2018/8/22.
//

#include "Lexer.h"
#include "../exception/ParseError.h"
#include "../utils/CharUtils.h"
#include "../token/IdToken.h"
#include "../token/NumToken.h"
#include <string>

const std::string Lexer::KEYWORD_BEGIN = "BEGIN";

const std::string Lexer::KEYWORD_END = "END";

const std::string Lexer::KEYWORD_PROGRAM = "PROGRAM";

const std::string Lexer::KEYWORD_DIV = "DIV";

const std::string Lexer::KEYWORD_INTEGER = "INTEGER";

const std::string Lexer::KEYWORD_REAL = "REAL";

Lexer::Lexer(Stream *stream)
	: mStream(stream)
{}

Token *Lexer::next()
{
	char ch = EOF;

	// skip blank
	while (is_blank(ch = mStream->next())) {}

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
		return new Token(Token::TokenType::TYPE_FLOAT_DIV);
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

	if (ch == ',') {
		return new Token(Token::TokenType::TYPE_COMMA);
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
		return nextId();
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

	if (ch != EOF) {
		mStream->back();
	}

	return new NumToken(atoi(num.c_str()));
}

Token *Lexer::nextId()
{
	char ch = mStream->next();
	std::string id;
	do {
		(id) += ch;
		ch = mStream->next();
	}
	while (is_alpha(ch) || is_num(ch) || ch == '_');

	if (ch != EOF) {
		mStream->back();
	}

	if (id == KEYWORD_BEGIN) {
		return new Token(Token::TokenType::TYPE_BEGIN);
	}

	if (id == KEYWORD_END) {
		return new Token(Token::TokenType::TYPE_END);
	}

	if (id == KEYWORD_PROGRAM) {
		return new Token(Token::TokenType::TYPE_PROGRAM);
	}

	if (id == KEYWORD_DIV) {
		return new Token(Token::TokenType::TYPE_INT_DIV);
	}

	if (id == KEYWORD_REAL) {
		return new Token(Token::TokenType::TYPE_REAL);
	}

	if (id == KEYWORD_INTEGER) {
		return new Token(Token::TokenType::TYPE_INTEGER);
	}

	return new IdToken(id);
}

Token *Lexer::nextColon()
{
	// ignore ':'
	mStream->next();
	char ch = mStream->next();
	if (ch != '=') {
		if (ch != EOF) {
			mStream->back();
		}
		return new Token(Token::TokenType::TYPE_COLON);
	}

	return new Token(Token::TokenType::TYPE_ASSIGN);
}
