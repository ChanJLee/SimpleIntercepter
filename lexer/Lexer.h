//
// Created by chan on 2018/8/22.
//

#ifndef SIMPLEINTERPRETER_LEXER_H
#define SIMPLEINTERPRETER_LEXER_H

#include <string>
#include "../stream/Stream.h"
#include "../token/Token.h"
#include <map>

class Lexer
{
private:
	typedef std::map<std::string, Token::TokenType> KeywordsMap;
	typedef KeywordsMap::iterator Iterator;
private:
	Stream *mStream;
	KeywordsMap mKeywordMap;
public:
	explicit Lexer(Stream *stream);

	virtual ~Lexer();

	Token *next();
private:
	Token *nextNumber();

	Token *nextId();

	Token *nextColon();

	char skipBlankChar();

	char skipComment();
};


#endif //SIMPLEINTERPRETER_LEXER_H
