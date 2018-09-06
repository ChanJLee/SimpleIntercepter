//
// Created by chan on 2018/8/22.
//

#ifndef SIMPLEINTERPRETER_LEXER_H
#define SIMPLEINTERPRETER_LEXER_H

#include <string>
#include "../stream/Stream.h"
#include "../token/Token.h"

class Lexer
{
private:
	static const std::string KEYWORD_BEGIN;
	static const std::string KEYWORD_END;
	static const std::string KEYWORD_PROGRAM;
	static const std::string KEYWORD_DIV;
	static const std::string KEYWORD_INTEGER;
	static const std::string KEYWORD_REAL;
private:
	Stream *mStream;
public:
	Lexer(Stream *stream);

	Token *next();
private:
	Token *nextNumber();

	Token *nextId();

	Token *nextColon();
};


#endif //SIMPLEINTERPRETER_LEXER_H
